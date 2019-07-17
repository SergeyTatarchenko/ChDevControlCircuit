/*************************************************
* File Name          : user_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : all code here
**************************************************/
#include "user_tasks.h"
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
	task_priority.stack_user  = 256; 
	task_priority.stack_tx_rx = 256;
	
	task_priority.tick_update_rate = 50;
	
	obj_state_on(IND_obj_ADC_CONV);
	obj_state_off(IND_obj_PredZar);
	obj_state_off(IND_obj_KM1);
	obj_state_off(IND_obj_PWM1);
	obj_state_off(IND_obj_PWM2);
	obj_state_off(IND_obj_PWM_FREQ);
	obj_state_off(IND_obj_PWM_ON);
	
	filter_enable();
	/*adc init*/
	ADC1_On
	/*usart interrupt enable*/
	NVIC_EnableIRQ (USART1_IRQn);
	
}

/*1 ms loop after setup*/
void obj_model_task(int tick)
{
	IWDG_RELOAD;
	if(board_power){
	OBJ_Event(IND_obj_ADC_CONV);
	
	if(tick%1000 == 0){
		OBJ_Event(IND_obj_TICK_1S);
		}		
	}
}

void filter_enable(void){
	
	NVIC_SetPriority (DMA1_Channel1_IRQn, 2);
	
	/*DMA transfer complete interrupt on NVIC*/
	NVIC_EnableIRQ (DMA1_Channel1_IRQn);

}

void vTask_PID_regulator(void *pvParameters)
{
	//		/*one init or handler*/
	pid_current_out.Kp = 0.8;
	pid_current_out.Kp = 0.001;
	pid_current_out.Kd = 0.5;
	
	for(;;){
    if(this_obj_state(IND_obj_PID_ON) == 1){
		/* cycle */
//		pid_current_out.feedback = ADC_Current;
//		pwm_val = PID_controller(pid_current_out);
		}
		vTaskDelay(10);
	}
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
