/*************************************************
* File Name          : user_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : all code here
**************************************************/
#include "user_tasks.h"
/*************************************************/

void board_task(int task_tick){
	
	/*heavy function !!!*/
	//Upd_All_OBJ_USART();
	
	FAST_Upd_All_OBJ_USART();
	
	if(task_tick%1 == 0){
		OBJ_Event(IND_obj_TICK);
		adc_calc_value();
		OBJ_Event(IND_obj_ADC1);
	}
}   
