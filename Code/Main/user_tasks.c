/*************************************************
* File Name          : user_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : all code here
**************************************************/
#include "user_tasks.h"
/*************************************************/

void board_task(){
	/*test obj upd*/
	
	Upd_All_OBJ();
	Obj_MCP23017_upd();
	
	OBJ_Event(IND_obj_TICK);
	adc_calc_value();
	OBJ_Event(IND_obj_ADC1);

}
