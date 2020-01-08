/*************************************************
* File Name          : user_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : all code here
**************************************************/
#include "user_tasks.h"
#include "stm32f10x.h"
/*************************************************/

xSemaphoreHandle FilterReady;

/*setup before loop*/
void obj_model_setup()
{
	task_priority.system_priority = configMAX_PRIORITIES-1;
	task_priority.rx_priority     = configMAX_PRIORITIES-2;
	task_priority.tx_priority     = configMAX_PRIORITIES-3;
	task_priority.user_priority   = configMAX_PRIORITIES-4;
	
	/*256*2 byte block */
	task_priority.stack_user  = 512; 
	task_priority.stack_tx_rx = 256;
	task_priority.tick_update_rate = 50;
	
	/*adc init*/
	ADC1_On
	/*usart interrupt enable*/
//	obj_state_on(IND_obj_KM1);
	/* USART1_IRQ = 37 */
	NVIC_EnableIRQ (USART1_IRQn);
	
	load_configuration(&ChargerConfig);
	value_of_obj(IND_obj_PWM_FREQ) = ChargerConfig.Frequency; 

	/*init coef of regulator*/
	pid_current_out.Kp = 0.8;
	pid_current_out.Ki = 0.1;
	pid_current_out.Kd = 0.5;
	
	pid_current_out.out_Max = ChargerConfig.MaxDutyCycle;
	pid_current_out.out_Min = ChargerConfig.MinDutyCycle;
	
	this_obj(IND_obj_PID1_KP)->dWordL = (uint32_t)(pid_current_out.Kp*10000);
	this_obj(IND_obj_PID1_KI)->dWordL = (uint32_t)(pid_current_out.Ki*10000);
	this_obj(IND_obj_PID1_KD)->dWordL = (uint32_t)(pid_current_out.Kd*10000);
}

/*1 ms loop after setup*/
void obj_model_task(int tick)
{
	IWDG_RELOAD;
	/*while power enable adc conversions*/
	if(board_power)
	{
	//obj_input_driver(&(IO_STATE.INPUTS),1,8,in_0);
	obj_adc_driver(ADC1_DataArray);
	}	
}

void filter_enable(void){
	
	NVIC_SetPriority (DMA1_Channel1_IRQn, 2);
	
	/*DMA transfer complete interrupt on NVIC*/
	NVIC_EnableIRQ (DMA1_Channel1_IRQn);

}

void vTask_led_driver(void *pvParameters)
{
static int tick = 0, tick_reload = 1000000;
	
	for(;;)
	{
		switch(device_state)
		{
			case IDLE:
				FAULT_LED_OFF;
				if(tick%1000 == 0)
				{
				state_led_invertor();
				}
			break;				
			case CHARGING:
				STATE_LED_ON;
				FAULT_LED_ON;
				break;
			case FAULT:
				STATE_LED_OFF;
				FAULT_LED_ON;	
				break;
			case PROGRAMMING:
				if(tick%100 == 0)
				{
					state_led_invertor();
					fault_led_invertor();
				}
				break;
		}
		/*tick update*/
		if(tick <= tick_reload)
		{
			tick++;
		}
		else
		{
			tick = 0;
		}	
		vTaskDelay(1);
	}
}
void vTask_regulator(void *pvParameters)
{		
	for(;;){
		if(state_of_obj(IND_obj_M_BUCK_MODE) == 1)
		{
			
			if(state_of_obj(IND_obj_PID_ON) == 1)
			{
				pid_current_out.setpoint_val = value_of_obj(IND_obj_PID_ON);
				pid_current_out.feedback = value_of_obj(IND_obj_aOUTC);
				value_of_obj(IND_obj_PWM_ON) = pid_regulator(&pid_current_out,0);
				pwm_control(BUCK_MODE,value_of_obj(IND_obj_PWM_ON),NULL,&ChargerConfig);
			}
			else
			{
				value_of_obj(IND_obj_PWM_ON) = pid_regulator(&pid_current_out,1);
				pwm_control(BUCK_MODE,value_of_obj(IND_obj_PWM_ON),NULL,&ChargerConfig);
			}
		}else{
			PWM_OFF;
			pwm_control(OFF,NULL,NULL,&ChargerConfig);
			this_obj(IND_obj_PWM_ON)->obj_value = 0;
		}
		vTaskDelay(10);
	}
}

/*test  P regulator*/
uint16_t pd_regulator(uint16_t set_value,uint16_t feedback,uint16_t gisteresis,uint8_t reset)
{
/*
	F(PWM,feedback value of current) = set value of current
	*/
	
	/*минимальное и максимальное значение скважности зависит от драйвера*/
	const int max_control_value = (PWM_MAX_VALUE - PWM_MAX_VALUE/10),min_control_value = PWM_MAX_VALUE/10;
	/*минимальный инкремент аргумента функции управления*/
	const int minimal_point = 1;
	/* приращение аргумента функции управления при переходном процессе */
	static int point = minimal_point;
	/*значение аргумента функции управления*/
	static uint16_t control = min_control_value;
	/*предыдущее значение функции,текущее значение функции*/
	static uint16_t last_feedback = 0,current_feedback = 0;
	/*приращение значения функции от ее аргумента */
	int function_increment = 0;
	/*установка текущего значения функции*/
	current_feedback = feedback;
	
	/*PI reg disable*/
	if(reset == 1)
	{
		current_feedback = last_feedback;
		control = min_control_value;
		return control;
	}
	
	/****************************************************************************** */
	/*дифференциальное звено, изменение значения функции от приращения ее аргумента */
	function_increment = fabs_function(current_feedback,last_feedback);
	
	/*увеличить значение значение приращения */
	if((function_increment < gisteresis)&&(point >minimal_point))
	{
		point ++;
	}
	/*уменьшить значение значение приращения при превышении значения гистерезиса*/
	if((function_increment > gisteresis)&&(point >minimal_point))
	{
		point --;
	}
	/*ошибка - переходной процесс не устойчив*/
	else if(point == minimal_point)
	{
	
	}
	/*сохранение значения обратной связи для следующей итерации*/
	last_feedback = current_feedback;
	/*ошибка ввода прараметра в функцию */
	if(set_value <= gisteresis){
		return min_control_value;
	}
	/****************************************************************************** */
	
	/*пропорциональное звено*/
	/* feedback is << that set value */
	if((feedback < (set_value - gisteresis))&&(control <= max_control_value))
	{
		control += point;
		return control;
	}
	/* feedback is >> that set value */
	if((feedback > (set_value + gisteresis))&&(control > min_control_value))
	{
		control -= point;
		return control;
	}
	/*working area*/
	if((feedback > (set_value - gisteresis))&&(feedback < (set_value + gisteresis)))
	{
		return control;
		/*устойчивое значение,добавить алгоритм сужения области в центр гистерезиса*/
	}
	/****************************************************************************** */
	//return (uint16_t)min_control_value;
	return control;
}

void vTask_ADC_filter(void *pvParameters){
	
	for(;;){
		/*выдача семафора в прерывании DMA ch1*/
		xSemaphoreTake(FilterReady,portMAX_DELAY);
		
		adc_val->adc1_value = adc_moving_average_filter(adc_ch1_buffer,adc_filter_size);
		adc_val->adc2_value = adc_moving_average_filter(adc_ch2_buffer,adc_filter_size);
		adc_val->adc3_value = adc_moving_average_filter(adc_ch3_buffer,adc_filter_size);
		adc_val->adc4_value = adc_moving_average_filter(adc_ch4_buffer,adc_filter_size);
		adc_val->adc5_value = adc_moving_average_filter(adc_ch5_buffer,adc_filter_size);
		adc_val->adc6_value = adc_moving_average_filter(adc_ch6_buffer,adc_filter_size);
		
		adc_calc_value();
		vTaskDelay(10);
	}
}
