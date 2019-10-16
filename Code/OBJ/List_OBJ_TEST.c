#include "TEST.h"
/************************************************************************************/
/* 									 OBJ_Handlers									*/
/************************************************************************************/

void board_START(OBJ_STRUCT *obj){
	/*board start*/
	if(obj->obj_state == 1){
		board_state.bit.power = 1;
	}else{
		board_state.bit.power = 0;
	}
}

/*��� � ������ �������*/
void TICK_Handler(OBJ_STRUCT *obj){
	
	obj->obj_value++;
}

/*���������� �����������*/
void LED_Control_Handler(OBJ_STRUCT *obj){
	
		if(GPIOC->ODR&=GPIO_ODR_ODR13){
				SYNC_LED_ON;
			}else{
				SYNC_LED_OFF;
			}
}
