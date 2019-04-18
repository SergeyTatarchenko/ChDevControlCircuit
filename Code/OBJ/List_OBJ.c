#include "obj_ID.h"

/************************************************************************************/
/* 									 object snapping		 						*/
/************************************************************************************/
void obj_snap(void){
	/*---------------------------------------------------*/
	/*           object type assignment                  */
	/*---------------------------------------------------*/
	Obj_Create(obj_STATUS,IND_obj_CAS);	
	obj_handlers[obj_STATUS] = board_START;
	/*---------------------------------------------------*/
	/*       Obj_Create(obj id,obj type);                */
	/*---------------------------------------------------*/
	/*---------------------------------------------------*/
	Obj_Create(IND_obj_TICK,IND_obj_SWC);
	Obj_Create(IND_obj_LED, IND_obj_CAS);
	Obj_Create(IND_obj_PWM, IND_obj_CAS);
	Obj_Create(IND_obj_TEST,IND_obj_SWC);
	Obj_Create(IND_obj_PID_KP,IND_obj_COM);
	Obj_Create(IND_obj_PID_KI,IND_obj_COM);
	Obj_Create(IND_obj_PID_KD,IND_obj_COM);
	Obj_Create(IND_obj_PID_SET_VAl,IND_obj_COM);
	Obj_Create(IND_obj_PID_FDB,IND_obj_COM);
	/*---------------------------------------------------*/
	/*obj_handlers[object name] = name of object handler;*/
	/*---------------------------------------------------*/	
	/*---------------------------------------------------*/
	obj_handlers[IND_obj_TICK] = TICK_Handler;
	obj_handlers[IND_obj_LED] = LED_Control_Handler;
	obj_handlers[IND_obj_ADC1] = ADC_Handler;
	/*---------------------------------------------------*/	
	Obj_Create(IND_obj_ADC1,IND_obj_CAS);
	this_obj(IND_obj_ADC1)->hardware_adress =adc_0;
	this_obj(IND_obj_ADC1)->obj_hardware = TRUE;

	Obj_Create(IND_obj_OUT0,IND_obj_CAS);
	this_obj(IND_obj_OUT0)->hardware_adress = out_0;
	this_obj(IND_obj_OUT0)->obj_hardware = TRUE;
	
}


/************************************************************************************/
/* 									 OBJ_Handlers									*/
/************************************************************************************/

void board_START(OBJ_STRUCT *obj){
	/*board start*/
	if(obj->obj_state == 1){
		board_state.bit.power = 1;
	}else{
		board_state.bit.power =0;
	}
}

/*показания ацп*/
void ADC_Handler(OBJ_STRUCT *obj){
	uint16_t *pointer;
	pointer = (uint16_t*)adc_val;
	
	this_obj(obj_STATUS)->obj_value = adc_val->TEMP_SENSOR;
//	for(int counter = adc_0;counter <= adc_5;counter++){
//		if(HW_OBJ[counter]->obj_hardware != 0){
//			pU16(HW_OBJ[counter]->obj_value) = *pointer;
//		}
//		pointer++;
//	}
}

/*тик с каждым ивентом*/
void TICK_Handler(OBJ_STRUCT *obj){
	
	obj->obj_value++;
}

/*управление светодиодом*/
void LED_Control_Handler(OBJ_STRUCT *obj){
	
		if(GPIOC->ODR&=GPIO_ODR_ODR13){
				LED_ON;
				Set_IO_State(7,1);
			}else{
				LED_OFF;
				Set_IO_State(7,0);
			}
}

/*пустой обработчик*/
void Dummy_Handler(OBJ_STRUCT *obj){
	
}
