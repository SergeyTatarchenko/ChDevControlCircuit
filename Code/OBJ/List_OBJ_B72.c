
#include "B72.h"
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

/*��������� ���*/
void ADC_Handler(OBJ_STRUCT *obj){
	
	uint16_t *pointer = (uint16_t*)adc_val;
	
	this_obj(obj_STATUS)->obj_value = adc_val->TEMP_SENSOR;
	for(int counter = adc_0;counter <= adc_5;counter++){
		if(HW_OBJ[counter]->obj_hardware != 0){
			pU16(HW_OBJ[counter]->obj_value) = *pointer;
		}
		pointer++;
	}
}

/*��� � ������ �������*/
void TICK_Handler(OBJ_STRUCT *obj){
	
	obj->obj_value++;
}

/*���������� �����������*/
void LED_Control_Handler(OBJ_STRUCT *obj){
	
		if(GPIOC->ODR&=GPIO_ODR_ODR13){
				LED_ON;
			}else{
				LED_OFF;
			}
	if(obj->obj_state == TRUE){
		obj_state_on(IND_obj_OUT7);
	}else{
		obj_state_off(IND_obj_OUT7);	
	}		
}
void PWM_Handler(OBJ_STRUCT *obj){
	
	if(obj->obj_state == 1){
		PWM_ON
		PWMSetValue(obj->obj_value);
	
	}else{
		PWM_OFF
		PWMSetValue(0);
	}
} 
