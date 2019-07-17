
#include "B72.h"
/************************************************************************************/
/* 									 OBJ_Handlers									*/
/************************************************************************************/
TimerHandle_t TestTimer;
const unsigned portBASE_TYPE TimerID = 1;

void TimerFunction(){
	
}

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
		
		obj_state_off(IND_obj_PredZar);
		obj_state_off(IND_obj_KM1);
	}
}

/*показания ацп*/
void ADC_Handler(OBJ_STRUCT *obj){

#define dvl_1000 50
#define lac_300  33
	/*
	DVL 1000  - 50uA per 1V
	LAC 300  -  33uA per 1A
	*/
	static const int load = 82;	
	static int indication;
	/*
	AIN0 - dvl1000   входное напряжение
	AIN1 - lac300  	 входной ток 	

	AIN2 - dvl1000   выходное напряжение
	AIN3 - lac300    выходной ток

	AIN4 - dvl1000   напряжение дросселя
	AIN5 - lf510     ток дросселя
	*/
	indication = (INT_ADC_REF - adc_val->CH1_ADC)*1000/load; //rez in uA
	if(indication > 0){
		/*костыль*/
		if(indication > 700){
			indication = 0;
		}
		this_obj(IND_obj_aINV)->obj_value = (uint16_t)(indication/dvl_1000);	
	}	
	indication = (INT_ADC_REF - adc_val->CH2_ADC)*1000/load; //rez in uA
	if(indication > 0){
		/*костыль*/
		if(indication > 700){
			indication = 0;
		}
	this_obj(IND_obj_aINC)->obj_value = (uint16_t)(indication/lac_300);
	}
	
	indication = (INT_ADC_REF - adc_val->CH3_ADC)*1000/load; //rez in uA
	if(indication > 0){
		/*костыль*/
		if(indication > 700){
			indication = 0;
		}
	this_obj(IND_obj_aOUTV)->obj_value = (uint16_t)(indication/dvl_1000);
	}
		
	indication = (INT_ADC_REF - adc_val->CH4_ADC)*1000/load; //rez in uA
	if(indication > 0){
		/*костыль*/
		if(indication > 700){
			indication = 0;
		}
	this_obj(IND_obj_aOUTC)->obj_value = (uint16_t)(indication/lac_300);
	}
//	
//	indication = (INT_ADC_REF - adc_val->CH5_ADC)*1000/load; //rez in uA
//	if(indication > 0){
//	this_obj(IND_obj_aDRV)->obj_value = (uint16_t)(indication/dvl_1000);
//	}
//	
//	indication = (INT_ADC_REF - adc_val->CH6_ADC)*1000/load; //rez in uA
//	if(indication > 0){
//	this_obj(IND_obj_aDRC)->obj_value = (uint16_t)(indication/33);
//	}
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

/*включение режима понижающего преобразователя*/
void BUCK_Mode_Handler(OBJ_STRUCT *obj)
{
	if(obj->obj_state == 1){
		/*вкл контактор*/
		obj_state_on(IND_obj_KM1);
		
		/*включение ШИМ канала для верхнего транзистора, нижний транзистор закрыт*/
		obj_state_on(IND_obj_PWM2);	
		/*установка частоты 2 кГц*/
		this_obj(IND_obj_PWM_FREQ)->obj_value = 2000;
		obj_state_on(IND_obj_PWM_FREQ);
	
		/*Включение ШИМ  - скважность 50%*/
		this_obj(IND_obj_PWM_ON)->obj_value = 500;
		obj_state_on(IND_obj_PWM_ON);	
	}else{
		obj_state_off(IND_obj_PWM_ON);
		obj_state_off(IND_obj_PWM2);
		/*выкл контактор*/
		obj_state_off(IND_obj_KM1);
	}
}

/*включение режима повышающего преобразователя*/
void BOOST_Mode_Handler(OBJ_STRUCT *obj)
{
	if(obj->obj_state == 1){
		
		/*вкл контактор*/
		obj_state_on(IND_obj_KM1);
		
		/*включение ШИМ канала для нижнего транзистора, верхний транзистор открыт*/
		obj_state_on(IND_obj_PWM1);	
		/*установка частоты 2 кГц*/
		this_obj(IND_obj_PWM_FREQ)->obj_value = 2000;
		obj_state_on(IND_obj_PWM_FREQ);
	
		/*Включение ШИМ  - скважность 50%*/
		this_obj(IND_obj_PWM_ON)->obj_value = 500;
		obj_state_on(IND_obj_PWM_ON);
		PWM_PIN1_ON; // открытие верхнего транзистора !!!
	}
	else{
		obj_state_off(IND_obj_PWM_ON);
		PWM_PIN1_OFF;
		obj_state_off(IND_obj_PWM2);
		
		/*выкл контактор*/
		obj_state_off(IND_obj_KM1);

	}
}

/*контроль канала ШИМ 1*/
void PWM1_Handler(OBJ_STRUCT *obj){
	
	if(obj->obj_state == 1){
		obj_state_off(IND_obj_PWM2);
		
		PWMSetActiveChannel(CH4);
		PWMSetActiveChannel(CH3);
	}else{
		PWMSetActiveChannel(ALL_CH_OFF);		
	}
}

/*контроль канала ШИМ 2*/
void PWM2_Handler(OBJ_STRUCT *obj){
	if(obj->obj_state == 1){
		PWMSetActiveChannel(ALL_CH_OFF);
		PWMSetActiveChannel(CH4);
	}else{
		PWMSetActiveChannel(ALL_CH_OFF);
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
			PWMSetValue(CH4,PERIOD_PWM);
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

/*устатовка констант ПИД регулятора*/
void PID_COEF_Handler(OBJ_STRUCT *obj){
	
	pid_current_out.Kp = ((float)(*((int*)&this_obj(IND_obj_PID1_KP)->obj_data[0])))/1000.0;
	pid_current_out.Ki = ((float)(*((int*)&this_obj(IND_obj_PID1_KI)->obj_data[0])))/1000.0;
	pid_current_out.Kd = ((float)(*((int*)&this_obj(IND_obj_PID1_KD)->obj_data[0])))/1000.0;
}

/*Активация ПИД регулятора (тест)*/
void PID_Control_Handler(OBJ_STRUCT *obj){
	if(obj->obj_state == 1){
		pid_current_out.setpoint_val = obj->obj_value;
	}else{
		pid_current_out.setpoint_val = 0;
	}
}
