
#include "global.h"

/************************************************************************************/
/* 									 object snapping		 						*/
/************************************************************************************/
void obj_snap(void){
	
	/*---------------------------------------------------*/
	/*           object type assignment                  */
	/*---------------------------------------------------*/
	
	/*---------------------------------------------------*/
	/*       Obj_Create(obj id,obj type);                */
	/*---------------------------------------------------*/
	Obj_Create(obj_STATUS,IND_obj_CAS);
	
	Obj_Create(IND_obj_IN0,IND_obj_CAS);
	Obj_Create(IND_obj_IN1,IND_obj_CAS);
	Obj_Create(IND_obj_IN2,IND_obj_CAS);
	Obj_Create(IND_obj_IN3,IND_obj_CAS);
	Obj_Create(IND_obj_IN4,IND_obj_CAS);
	Obj_Create(IND_obj_IN5,IND_obj_CAS);
	Obj_Create(IND_obj_IN6,IND_obj_CAS);
	Obj_Create(IND_obj_IN7,IND_obj_CAS);
	/*---------------------------------------------------*/
	Obj_Create(IND_obj_OUT0,IND_obj_CAS);
	Obj_Create(IND_obj_OUT1,IND_obj_CAS);
	Obj_Create(IND_obj_OUT2,IND_obj_CAS);
	Obj_Create(IND_obj_OUT3,IND_obj_CAS);
	Obj_Create(IND_obj_OUT4,IND_obj_CAS);
	Obj_Create(IND_obj_OUT5,IND_obj_CAS);
	Obj_Create(IND_obj_OUT6,IND_obj_CAS);
	Obj_Create(IND_obj_OUT7,IND_obj_CAS);
	/*---------------------------------------------------*/
	Obj_Create(IND_obj_ADC1,IND_obj_SWC);
	Obj_Create(IND_obj_ADC2,IND_obj_SWC);
	Obj_Create(IND_obj_ADC3,IND_obj_SWC);
	Obj_Create(IND_obj_ADC4,IND_obj_SWC);
	Obj_Create(IND_obj_ADC5,IND_obj_SWC);
	Obj_Create(IND_obj_ADC6,IND_obj_SWC);
	/*---------------------------------------------------*/
	Obj_Create(IND_obj_TICK,IND_obj_SWC);
	Obj_Create(IND_obj_LED, IND_obj_CWS);
	Obj_Create(IND_obj_PWM, IND_obj_CWS);
	Obj_Create(IND_obj_TEST,IND_obj_SWC);
	
	
	/*---------------------------------------------------*/
	/*obj_handlers[object name] = name of object handler;*/
	/*---------------------------------------------------*/	
	
	obj_handlers[obj_STATUS] = board_START;
	
	obj_handlers[IND_obj_ADC1] = ADC_Handler;
	obj_handlers[IND_obj_ADC2] = ADC_Handler;
	obj_handlers[IND_obj_ADC3] = ADC_Handler;
	obj_handlers[IND_obj_ADC4] = ADC_Handler;
	obj_handlers[IND_obj_ADC5] = ADC_Handler;
	obj_handlers[IND_obj_ADC6] = ADC_Handler;
	/*---------------------------------------------------*/
	obj_handlers[IND_obj_TICK] = TICK_Handler;
	obj_handlers[IND_obj_LED] = LED_Control_Handler;
	/*---------------------------------------------------*/	
}


/************************************************************************************/
/* 									 OBJ_Handlers									*/
/************************************************************************************/


void board_START(OBJ_STRUCT *obj){
	/*board start*/
	if(obj->obj_state == 1){
		power_on = 1;
	}else{
		power_on =0;
	}
}

/*показания ацп*/
void ADC_Handler(OBJ_STRUCT *obj){
	
	this_obj(IND_obj_ADC1)->obj_data[0] = adc_val->CH1_ADC;
	this_obj(IND_obj_ADC2)->obj_data[0] = adc_val->CH2_ADC;
	this_obj(IND_obj_ADC3)->obj_data[0] = adc_val->CH3_ADC;
	this_obj(IND_obj_ADC4)->obj_data[0] = adc_val->CH4_ADC;
	this_obj(IND_obj_ADC5)->obj_data[0] = adc_val->CH5_ADC;
	this_obj(IND_obj_ADC6)->obj_data[0] = adc_val->CH6_ADC;
	
	this_obj(obj_STATUS)->obj_data[1] = adc_val->TEMP_SENSOR;
}
/*тик с каждым ивентом*/
void TICK_Handler(OBJ_STRUCT *obj){
	
	obj->obj_data[0]++;
}

/*управление светодиодом*/
void LED_Control_Handler(OBJ_STRUCT *obj){
	
		if(GPIOC->ODR&=GPIO_ODR_ODR13){
				LED_ON;
			}else{
				LED_OFF;
			}
}

/*пустой обработчик*/
void Dummy_Handler(OBJ_STRUCT *obj){
	
}
