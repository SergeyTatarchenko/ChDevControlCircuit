
#include "global.h"

/************************************************************************************/
/* 									 object snapping		 						*/
/************************************************************************************/
void obj_snap(void){
	
	/*obj_handlers[object name] = name of object handler;*/
	
	/*test */
	obj_handlers[IND_obj_SetPWM] = SetPWM_Handler;
	
}


/************************************************************************************/
/* 									 OBJ_Handlers									*/
/************************************************************************************/

void SetPWM_Handler(OBJ_STRUCT *obj){
	
	if(obj->obj_field.d8b[0] == 0){
		obj->obj_field.d8b[0] = 0xff;
		LED_ON;
	}else{
		obj->obj_field.d8b[0] = 0x00;
		LED_OFF;
	}
}

