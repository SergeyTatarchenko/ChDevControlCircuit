/*************************************************
* File Name          : user_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : all code here
**************************************************/
#include "user_tasks.h"
/*************************************************/

void board_pr_init(){
	
	obj_state_on(IND_obj_ADC_CONV);
	
	obj_state_off(IND_obj_OUT6);
	obj_state_off(IND_obj_OUT7);
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
