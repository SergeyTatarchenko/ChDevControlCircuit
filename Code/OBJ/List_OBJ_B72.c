
#include "B72.h"
#include "global.h"
/************************************************************************************/
/* 									 OBJ_Handlers									*/
/************************************************************************************/


/*переинициализировать !!! макрос как часть структуры установочных параметров в ПЗУ*/
#define set_charge_min_voltage	500
#define set_charge_max_voltage	900

#define set_current_sensor_error	2
#define set_voltage_sensor_error	10	

#define buck_min_value			400	
#define buck_max_value  		800

#define charger_buck_mode		1
#define charger_boost_mode		2

void board_START(OBJ_STRUCT *obj)
{
	if(obj->obj_state == 1)
	{
		board_power = 1;
		OBJ_Event(IND_obj_USART_TX);
	}
	else
	{
		board_power = 0;
		set_all_obj_off();
		LED_OFF;
	}
}

/*показания ацп*/
void ADC_Handler(OBJ_STRUCT *obj){
	/*
	AIN0 - dvl1000   входное напряжение
	AIN1 - lac300  	 входной ток 	

	AIN2 - dvl1000   выходное напряжение
	AIN3 - lac300    выходной ток

	AIN4 - dvl1000   напряжение дросселя
	AIN5 - lf510     ток дросселя
	*/
	this_obj(IND_obj_aINV)->obj_value = get_dvl1000_value(adc_val->CH1_ADC);
	this_obj(IND_obj_aINC)->obj_value = get_lac300_value(adc_val->CH2_ADC);
	
	this_obj(IND_obj_aOUTV)->obj_value = get_dvl1000_value(adc_val->CH3_ADC);
	this_obj(IND_obj_aOUTC)->obj_value = get_lac300_value(adc_val->CH4_ADC);
	
	this_obj(IND_obj_aDRV)->obj_value = get_dvl1000_value(adc_val->CH5_ADC);
	this_obj(IND_obj_aDRC)->obj_value = get_lac300_value(adc_val->CH6_ADC);
	
	/* test */
//	this_obj(IND_obj_aINV)->obj_value = adc_val->CH1_ADC;
//	this_obj(IND_obj_aINC)->obj_value = adc_val->CH2_ADC;
//	this_obj(IND_obj_aOUTV)->obj_value = adc_val->CH3_ADC;
//	this_obj(IND_obj_aOUTC)->obj_value = adc_val->CH4_ADC;
//	this_obj(IND_obj_aDRC)->obj_value = adc_val->CH5_ADC;
//	this_obj(IND_obj_aDRV)->obj_value = adc_val->CH6_ADC;
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

/*Отправка через последовательный порт обратной связи об объектах*/
void USART_Handler(OBJ_STRUCT *obj){
	
	obj->obj_value++;
	led_invertor();
	
	if(board_power == 1){
		FAST_Upd_All_OBJ_USART();
		OBJ_Event(IND_obj_USART_TX);
	}
}
/**/
void ChDevStart_Handler(OBJ_STRUCT *obj)
{
	static int charger_permission;
	if(obj->obj_state){
		/*старт алгоритма ЗУ, проверка входных датчиков*/
		/*------------------------------------*/
		charger_permission = comparator(value_of_obj(IND_obj_aINC),set_current_sensor_error);
		if(!charger_permission){
			/*утечка или ошибка датчика входного тока*/
		}
		charger_permission &= comparator(value_of_obj(IND_obj_aINV),set_voltage_sensor_error);
		if(!charger_permission){
			/*утечка или ошибка датчика входного напряжения*/
		}
		/*------------------------------------*/
		charger_permission &= comparator(value_of_obj(IND_obj_aOUTC),set_current_sensor_error);
		if(!charger_permission){
			/*утечка или ошибка датчика выходного тока*/
		}
		charger_permission &= comparator(value_of_obj(IND_obj_aOUTV),set_voltage_sensor_error);
		if(!charger_permission){
			/*утечка или ошибка датчика выходного напряжения*/
		}
		/*------------------------------------*/
		charger_permission &= comparator(value_of_obj(IND_obj_aDRV),set_voltage_sensor_error);
		if(!charger_permission){
			/*утечка или ошибка датчика напряжения дросселя*/
		}
		charger_permission &= comparator(value_of_obj(IND_obj_aDRC),set_current_sensor_error);
		if(!charger_permission){
			/*утечка или ошибка датчика тока дросселя*/
		}
		/*в новой ревизии платы добавить проверку датчиков температуры ключей и радиатора + проверка обратной связи контактора*/
		
		/*в случае отсутствия ошибок - пуск преобразователя (режим работы закладывается в поле value)*/
		if(charger_permission){
			/*включение платы предзаряда*/
			obj_state_on(IND_obj_PredZar);
			/*запуск таймера задержки старта*/
			OBJ_Event(IND_obj_DELAY_START);
		}
	}	
}

/**/
void DelayStart_Handler(OBJ_STRUCT *obj)
{
	static int charger_permission;
	/*---------------------------------------------*/
	/*выключение платы предзаряда*/
	obj_state_off(IND_obj_PredZar);
	
	/*проверка входного напряжения */
	charger_permission = comparator(value_of_obj(IND_obj_aINV),set_charge_min_voltage);
	if(!charger_permission){
		/*низкое входное напряжение*/
	}
	charger_permission &= comparator(value_of_obj(IND_obj_aINV),set_charge_max_voltage);
	if(!charger_permission){
		/*высокое входное напряжение*/
	}
	if(charger_permission){
		/*включение контактора КМ1*/
		obj_state_on(IND_obj_KM1);
		/*добавить проверку на залипание контактора*/
		
		/*ТЕСТ понижающий режим*/
		obj_state_on(IND_obj_BUCK_MODE);
		
	}	
}

/*включение режима понижающего преобразователя*/
void BUCK_Mode_Handler(OBJ_STRUCT *obj)
{
	if(obj->obj_state == 1){
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


/*контроль частоты ШИМ*/
void PWM_freq_config_Handler(OBJ_STRUCT *obj){
	if(obj->obj_state){
		PWMSetFrequency(obj->obj_value);
	}else{
		obj_state_off(IND_obj_PWM_ON);
	}
}

/*Включение и выключение ШИМ в микросхеме*/
void PWM_Control_Handler(OBJ_STRUCT *obj)
{
	if(obj->obj_state){
		/*ограничение значения D при ручном управлении*/
		if(obj->obj_value >buck_max_value){
			obj->obj_value = buck_max_value;
		}
		if(obj->obj_value <buck_min_value){
			obj->obj_value = buck_min_value;
		}
		/*BOOST mode*/
		if(this_obj(IND_obj_PWM1)->obj_state == 1){
			PWMSetValue(CH3,obj->obj_value);
			PWMSetValue(CH4,PERIOD_PWM);
			PWM_ON;	
		}
		/*BUCK mode*/
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
	
	pid_current_out.Kp = (float)(this_obj(IND_obj_PID1_KP)->dWordL)/10000.0;
	pid_current_out.Ki = (float)(this_obj(IND_obj_PID1_KI)->dWordL)/10000.0;
	pid_current_out.Kd = (float)(this_obj(IND_obj_PID1_KD)->dWordL)/10000.0;
}

/*Активация ПИД регулятора (тест)*/
void PID_Control_Handler(OBJ_STRUCT *obj){
	if(obj->obj_state == 1){
		pid_current_out.setpoint_val = obj->obj_value;
	}else{
		pid_current_out.setpoint_val = 0;
	}
}


