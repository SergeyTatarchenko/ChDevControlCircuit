#include "obj_ID.h"

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

/*показания ацп*/
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

/*тик с каждым ивентом*/
void TICK_Handler(OBJ_STRUCT *obj){
	
	obj->obj_value++;
}

/*управление светодиодом*/
void LED_Control_Handler(OBJ_STRUCT *obj){
	
		if(GPIOC->ODR&=GPIO_ODR_ODR13){
				LED_ON;
			}else{
				LED_OFF;
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

/*пустой обработчик*/
void Dummy_Handler(OBJ_STRUCT *obj){
	
}
