
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
		
		obj_state_off(IND_obj_PWM1);
		obj_state_off(IND_obj_PWM2);
		obj_state_off(IND_obj_PWM_FREQ);
		obj_state_off(IND_obj_PWM_ON);
		
		obj_state_off(IND_obj_ADC_CONV);
		
		obj_state_off(IND_obj_OUT6);
		obj_state_off(IND_obj_OUT7);
	}
}

/*показания ацп*/
void ADC_Handler(OBJ_STRUCT *obj){
	
		/* sensors load 82 Omh*/
		//	static const int load = 10;
		//	static int indication;
	
	this_obj(IND_obj_aINV)->obj_value = adc_val->CH1_ADC;
	this_obj(IND_obj_aINC)->obj_value = adc_val->CH2_ADC;
	this_obj(IND_obj_aOUTV)->obj_value = adc_val->CH3_ADC;
	this_obj(IND_obj_aOUTC)->obj_value = adc_val->CH4_ADC;
	this_obj(IND_obj_aDRV)->obj_value = adc_val->CH5_ADC;
	this_obj(IND_obj_aDRC)->obj_value = adc_val->CH6_ADC;

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

/*контроль канала ШИМ 1*/
void PWM1_Handler(OBJ_STRUCT *obj){
	
	if(obj->obj_state == 1){
		obj_state_off(IND_obj_PWM2);
		PWMSetActiveChannel(CH3);
	}
}

/*контроль канала ШИМ 2*/
void PWM2_Handler(OBJ_STRUCT *obj){
	if(obj->obj_state == 1){
		obj_state_off(IND_obj_PWM1);
		PWMSetActiveChannel(CH4);
	}
}

/*контроль частоты ШИМ*/
void PWM_freq_config_Handler(OBJ_STRUCT *obj){
	if(obj->obj_state){
		PWMSetFrequency(obj->obj_value);
	}else{
		obj_state_off(IND_obj_PWM_ON);
	}
}

/*Включение и выключение ШИМ в микросхеме*/
void PWM_Control_Handler(OBJ_STRUCT *obj){
	if(obj->obj_state){
		if(this_obj(IND_obj_PWM1)->obj_state == 1){
			PWMSetValue(CH3,obj->obj_value);
			PWM_ON;	
		}
		if(this_obj(IND_obj_PWM2)->obj_state == 1){
			PWMSetValue(CH4,obj->obj_value);
			PWM_ON;
		}
	}else{
		PWM_OFF;
		PWMSetValue(CH3,0);
		PWMSetValue(CH4,0);
	}
}
