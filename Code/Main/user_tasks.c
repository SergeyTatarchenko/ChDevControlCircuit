/*************************************************
* File Name          : user_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : all code here
**************************************************/
#include "user_tasks.h"
/*************************************************/

void board_task(int task_tick){
	
	adc_calc_value();
	//OBJ_Event(IND_obj_ADC1);

	if(task_tick%1000 == 0){
		OBJ_Event(IND_obj_TICK_1S);
	}
	if(task_tick%100 == 0){
		OBJ_Event(IND_obj_TICK_100_ms);
	}
	
}   
