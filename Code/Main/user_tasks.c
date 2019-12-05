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
		
	/*init coef of regulator*/
	pid_current_out.Kp = 0.8;
	pid_current_out.Ki = 0.001;
	pid_current_out.Kd = 0.5;
	
	pid_current_out.out_Max = 1000; 
	pid_current_out.out_Min = 0;
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
		/*функция только для выполнения в прерывании*/
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
				/*обратная связь - датчик тока в нагрузке*/
				/*установка значения ШИМ ключей от регулятора и обновления состояния объекта*/
				this_obj(IND_obj_PWM_ON)->obj_value = pd_regulator(this_obj(IND_obj_PID_ON)->obj_value,
				this_obj(IND_obj_aOUTC)->obj_value,ChargerConfig.MaxDutyCycle,ChargerConfig.MinDutyCycle,1,0);
				obj_update(IND_obj_PWM_ON);
			}
			else
			{
				this_obj(IND_obj_PWM_ON)->obj_value = pd_regulator(this_obj(IND_obj_PID_ON)->obj_value,
				this_obj(IND_obj_aOUTC)->obj_value,ChargerConfig.MaxDutyCycle,ChargerConfig.MinDutyCycle,1,1);
				obj_update(IND_obj_PWM_ON);
			}
		}
		vTaskDelay(1);
		//vTaskDelay(10);
	}
}


uint16_t pd_regulator(uint16_t set_value,uint16_t feedback,int max_value,int min_value,uint16_t gisteresis,uint8_t reset)
{
/***********************************************************************************
Регулятор параметра по заданной ОС с программируемым гистерезисом и триггером сброса 
***********************************************************************************/
	
	/*минимальное и максимальное выходное значение */
//	const int max_control_value = 900,min_control_value = 100;
	/*минимальный инкремент аргумента функции управления*/
	const int minimal_point = 1;
	/* приращение аргумента функции (n) для (n+1) */
	static int point = minimal_point;
	/*начальное значение выходного сигнала*/
	static uint16_t control = 0;
	/*предыдущее и текущее значение функции*/
	static uint16_t last_feedback = 0,current_feedback = 0;
	/*приращение значения функции от ее аргумента df/dt = f(n+1) - f(n) */
	int function_increment = 0;
	
	/****************************************************************/
	/*************************АЛГОРИТМ*******************************/
	/****************************************************************/
	/*установка значения обратной связи f(n) для сравнения с f(n-1) */
	current_feedback = feedback;
	
	if(control < min_value)
	{
		control = min_value;
	}
	
	if(set_value <= gisteresis)/*ошибка ввода прараметра в функцию */
	{
		return min_value;
	}
	
	if(reset == 1)/*Триггер сброса регулятора в начальное положение*/
	{
		current_feedback = last_feedback;
		control = min_value;
		return control;
	}
	
	/*вычисление приращения функции f(n+1) от f(n)*/
	function_increment = fabs_function(current_feedback,last_feedback);
	
	/*увеличить значение приращения аргумента в случае минимальной разницы*/
	if((function_increment < gisteresis)&&(point > minimal_point))
	{
		point ++;
	}
	/*уменьшить значение значение приращения при превышении значения гистерезиса*/
	if((function_increment > gisteresis)&&(point > minimal_point))
	{
		point --;
	}
	/*ошибка - переходной процесс не устойчив, возврат минимального значения*/
	else if(point == minimal_point)
	{
		return min_value;	
	}
	/*сохранение значения обратной связи для следующей итерации*/
	last_feedback = current_feedback;
	
	/*увеличение значения f(n) при ОС меньше чем заданное число*/
	if((feedback < (set_value - gisteresis))&&(control <= max_value))
	{
		control += point;
		return control;
	}
	/*уменьшение значения f(n) при ОС больше чем заданное число*/
	if((feedback > (set_value + gisteresis))&&(control > min_value))
	{
		control -= point;
		return control;
	}
	/*устойчивое значение,погрешность задана гистерезисом*/
	if((feedback > (set_value - gisteresis))&&(feedback < (set_value + gisteresis)))
	{
		return control;
	}
	/*в нормальном режиме эта точка недостижима*/
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
