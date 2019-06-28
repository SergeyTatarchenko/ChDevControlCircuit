
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

/*показания ацп*/
void ADC_Handler(OBJ_STRUCT *obj){
	
	/* sensors load 10 Omh*/
	static const int load = 10;
	static int indication;
	
	this_obj(IND_obj_aINV)->obj_value = adc_val->CH1_ADC;
	this_obj(IND_obj_aINC)->obj_value = adc_val->CH2_ADC;
	this_obj(IND_obj_aOUTV)->obj_value = adc_val->CH3_ADC;
	this_obj(IND_obj_aOUTC)->obj_value = adc_val->CH4_ADC;
	this_obj(IND_obj_aDRV)->obj_value = adc_val->CH5_ADC;
	this_obj(IND_obj_aDRC)->obj_value = adc_val->CH6_ADC;

	//	/*input voltage DVL 1000 - 50uA/V */
//	indication =((3300 - adc_val->CH1_ADC)/load)*20;
//	if(indication > 0){
//		this_obj(IND_obj_aINV)->obj_value = indication;
//	}else{
//		this_obj(IND_obj_aINV)->obj_value = 0;
//	}
//	
//	/*input current LAC 300 - 33uA/A */
//	indication =((3300 - adc_val->CH2_ADC)/load)*30;
//	if(indication > 0){
//		this_obj(IND_obj_aINC)->obj_value = indication;
//	}else{
//		this_obj(IND_obj_aINC)->obj_value = 0;
//	}
//	
//	/*output voltage DVL 1000 - 50uA/V */
//	indication =((3300 - adc_val->CH3_ADC)/load)*20;
//	if(indication > 0){
//		this_obj(IND_obj_aOUTV)->obj_value = indication;
//	}else{
//		this_obj(IND_obj_aOUTV)->obj_value = 0;
//	}
//	
//	/*output current LAC 300 - 33uA/A */
//	indication =((3300 - adc_val->CH4_ADC)/load)*30;
//	if(indication > 0){
//		this_obj(IND_obj_aOUTC)->obj_value = indication;
//	}else{
//		this_obj(IND_obj_aOUTC)->obj_value = 0;
//	}
//	
//	/*inductor voltage DVL 1000 - 50uA/V */
//	indication =((3300 - adc_val->CH5_ADC)/load)*20;
//	if(indication > 0){
//		this_obj(IND_obj_aDRV)->obj_value = indication;
//	}else{
//		this_obj(IND_obj_aDRV)->obj_value = 0;
//	}
	
//	/*inductor current LAC 300 - 33uA/A */
//	indication =((3300 - adc_val->CH4_ADC)/load)*30;
//	if(indication > 0){
//		this_obj(IND_obj_aDRC)->obj_value = indication;
//	}else{
//		this_obj(IND_obj_aDRC)->obj_value = 0;
//	}
//	
	
}

/*тик с каждым ивентом*/
void TICK_Handler(OBJ_STRUCT *obj){
	obj->obj_value++;
	if(GPIOC->ODR&=GPIO_ODR_ODR13){
		LED_ON;
	}else{
	LED_OFF;
	}
}

/*управление светодиодом*/
void LED_Control_Handler(OBJ_STRUCT *obj){
	if(obj->obj_state != 0){
		if(GPIOC->ODR&=GPIO_ODR_ODR13){
			LED_ON;
			}
		else{
			LED_OFF;
		}		
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
