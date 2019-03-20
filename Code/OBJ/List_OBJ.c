
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
	Obj_Create(IND_obj_IO,IND_obj_CWS);
	/*---------------------------------------------------*/
	Obj_Create(IND_obj_ADC1,IND_obj_SWC);
	Obj_Create(IND_obj_ADC2,IND_obj_SWC);
	Obj_Create(IND_obj_ADC3,IND_obj_SWC);
	Obj_Create(IND_obj_ADC4,IND_obj_SWC);
	Obj_Create(IND_obj_ADC5,IND_obj_SWC);
	Obj_Create(IND_obj_ADC6,IND_obj_SWC);
	
	Obj_Create(IND_obj_TICK,IND_obj_SWC);
	
	Obj_Create(IND_obj_LED,IND_obj_CWS);
	
	Obj_Create(IND_obj_PWM,IND_obj_CWS);
	
	/*---------------------------------------------------*/
	/*obj_handlers[object name] = name of object handler;*/
	/*---------------------------------------------------*/	
	obj_handlers[IND_obj_IO] = IO_ControlHandler;
	
	obj_handlers[IND_obj_ADC1] = ADC_Handler;
	obj_handlers[IND_obj_ADC2] = ADC_Handler;
	obj_handlers[IND_obj_ADC3] = ADC_Handler;
	obj_handlers[IND_obj_ADC4] = ADC_Handler;
	obj_handlers[IND_obj_ADC5] = ADC_Handler;
	obj_handlers[IND_obj_ADC6] = ADC_Handler;
	
	obj_handlers[IND_obj_TICK] = TICK_Handler;
	
	obj_handlers[IND_obj_LED] = LED_Control_Handler;
	
	obj_handlers[IND_obj_PWM] = Dummy_Handler;
	
	/*---------------------------------------------------*/

	OBJ_SyncIO(IND_obj_IO);
	
}


/************************************************************************************/
/* 									 OBJ_Handlers									*/
/************************************************************************************/
/*управление входом выходом*/
void IO_ControlHandler(OBJ_STRUCT *obj){
	
	/*event*/
	if(obj->obj_event == 1){
		if(obj->obj_data[2]!= IO_Pointer->OUTPUTS){
			
	//		OBJ_SET_IO_BYTE(obj->obj_data[2]);
		}
	}
}
/*показания ацп*/
void ADC_Handler(OBJ_STRUCT *obj){
	
	this_obj(IND_obj_ADC1)->obj_data[0] = adc_val->CH1_ADC;
	OBJ_Upd(this_obj(IND_obj_ADC1));
	
	this_obj(IND_obj_ADC2)->obj_data[0] = adc_val->CH2_ADC;
	OBJ_Upd(this_obj(IND_obj_ADC2));
	
	this_obj(IND_obj_ADC3)->obj_data[0] = adc_val->CH3_ADC;
	OBJ_Upd(this_obj(IND_obj_ADC3));
	
	this_obj(IND_obj_ADC4)->obj_data[0] = adc_val->CH4_ADC;
	OBJ_Upd(this_obj(IND_obj_ADC4));
	
	this_obj(IND_obj_ADC5)->obj_data[0] = adc_val->CH5_ADC;
	OBJ_Upd(this_obj(IND_obj_ADC5));
	
	this_obj(IND_obj_ADC6)->obj_data[0] = adc_val->CH6_ADC;
	OBJ_Upd(this_obj(IND_obj_ADC6));
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
	LED_ON;
}
