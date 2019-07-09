/*************************************************
* File Name          : user_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : all code here
**************************************************/
#include "user_tasks.h"
/*************************************************/

xSemaphoreHandle FilterReady;


void board_pr_init(){
	
	//filter_enable();
	
	obj_state_on(IND_obj_ADC_CONV);
	obj_state_off(IND_obj_OUT6);
	obj_state_off(IND_obj_OUT7);
	
	
	obj_state_off(IND_obj_PWM1);
	obj_state_off(IND_obj_PWM2);
	obj_state_off(IND_obj_PWM_FREQ);
	obj_state_off(IND_obj_PWM_ON);
	
	/*adc init*/
	ADC1_On
	
}

void filter_enable(void){
	
	NVIC_SetPriority (DMA1_Channel1_IRQn, 2);
	
	/*DMA transfer complete interrupt on NVIC*/
	NVIC_EnableIRQ (DMA1_Channel1_IRQn);

}

void board_task(int task_tick){

#ifdef TARGET	
	/*get value in mV of all sensors*/
	adc_calc_value();
	/*obj snap*/
	OBJ_Event(IND_obj_ADC_CONV);
	
	
	if(task_tick%1000 == 0){
		OBJ_Event(IND_obj_TICK_1S);
	}
	
#endif
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
