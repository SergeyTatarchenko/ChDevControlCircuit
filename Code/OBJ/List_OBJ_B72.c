
#include "B72.h"
#include "global.h"
/************************************************************************************/
/* 									 OBJ_Handlers									*/
/************************************************************************************/
static uint8_t current_limit_trigger = 0;

void general_CAN_Handler(CAN_MSG_TypeDef *msg){
	
	/*test can handler*/
	if(msg->Data[0] == 1){
		value_of_obj(IND_obj_Q)= msg->Data[1];
	}
}
/*first obj*/
void board_START(OBJ_STRUCT_TypeDef *obj)
{
	if(obj->OBJ_STATUS.soft.state == 1)
	{
		load_configuration(&ChargerConfig);
		value_of_obj(IND_obj_PWM_FREQ) = ChargerConfig.Frequency; 
		board_power = 1;
		OBJ_Event(IND_obj_USART_TX);
		OBJ_Event(IND_obj_CAN_SEND);
	}
	else
	{
		board_power = 0;
		PWM_OFF;
		pwm_control(OFF,NULL,NULL,&ChargerConfig);	
		/*выкл контактор*/
		OBJ_Event(IND_obj_tKM_Off);
		SYNC_LED_OFF;
	}
}



void ADC0_Handler(OBJ_STRUCT_TypeDef *obj)
{
	/*	AIN0 - dvl1000 выходное напряжение */
	uint16_t value = obj->obj_def_value;
	value = (value*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	this_obj(IND_obj_aOUTV)->obj_def_value = get_dvl1000_value(value);
}

void ADC1_Handler(OBJ_STRUCT_TypeDef *obj)
{
	/*AIN1 - lac300 выходной ток*/
	uint16_t value = obj->obj_def_value;
	value = (value*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	this_obj(IND_obj_aOUTC)->obj_def_value = get_lac300_value(value);
	if((current_limit_trigger == 0)&&(value_of_obj(IND_obj_aOUTC)>value_of_obj(IND_obj_CURLIMIT)))
	{
		obj_state_off(IND_obj_M_BUCK_MODE);
		state_of_obj(IND_obj_CURLIMIT) = 1;
		current_limit_trigger = 1;
	}
}

void CurrentLimit(OBJ_STRUCT_TypeDef *obj)
{
	if(obj->obj_state == 0)
	{
		current_limit_trigger = 0;
	}
}

void ADC2_Handler(OBJ_STRUCT_TypeDef *obj)
{
	/*AIN2 - dvl1000 входное напряжение*/
	uint16_t value = obj->obj_def_value;
	value = (value*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	this_obj(IND_obj_aINV)->obj_def_value = get_dvl1000_value(value);
}

void ADC3_Handler(OBJ_STRUCT_TypeDef *obj)
{
	/*AIN3 - lac300 входной ток*/
	uint16_t value = obj->obj_def_value;
	value = (value*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	this_obj(IND_obj_aINC)->obj_def_value = get_lac300_value(value);	
}

void ADC4_Handler(OBJ_STRUCT_TypeDef *obj)
{
	/*AIN4 - dvl1000   напряжение дросселя*/
	uint16_t value = obj->obj_def_value;
	value = (value*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	this_obj(IND_obj_aDRV)->obj_def_value = get_dvl1000_value(value);	
}

void ADC5_Handler(OBJ_STRUCT_TypeDef *obj)
{
	/*AIN5 - lf510   ток дросселя*/
	uint16_t value = obj->obj_def_value;
	value = (value*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	this_obj(IND_obj_aDRC)->obj_def_value = get_lf510_value(value);		
}

void ADC7_Handler(OBJ_STRUCT_TypeDef *obj)
{
	uint16_t temp_radiator;
	/*AIN6 - температура радиатора */
	uint16_t value = obj->obj_def_value;
	temp_radiator = ADC_B57045_1K21 (value);
	this_obj(IND_obj_TempRadiator)->obj_def_value = temp_radiator ;
}

/*Отправка через последовательный порт обратной связи об объектах (загрузка таблицы в приложение)*/
void USART_Handler(OBJ_STRUCT_TypeDef *obj){
	sync_led_invertor();
	
	if(board_power == 1){
		sp_all_obj_sync();
		OBJ_Event(IND_obj_USART_TX);
	}else{
		SYNC_LED_OFF;
	}
}
void CAN_Sender(OBJ_STRUCT_TypeDef *obj){
    
	static CanTxMsg msg;
	msg.ExtId = 0x18FF0250;
	msg.Data[1] = 2;
	msg.Data[2] = 3;
	msg.Data[3] = 4;
	msg.Data[4] = 5;
	msg.Data[5] = 6;
	msg.Data[6] = 7;
	msg.Data[7] = 8;
	msg.DLC = 8;
	msg.IDE = CAN_Id_Extended;
	CAN_Send(&msg);
	msg.Data[0] ++;
	OBJ_Event(IND_obj_CAN_SEND);
}
/**/
void _Diagnostic_(OBJ_STRUCT_TypeDef *obj)
{
//	static int diagnostic_array[] = {_diagnostic_};

}
/*таймер отключения контактора */
void KM_Off_Handler(OBJ_STRUCT_TypeDef *obj)
{
	if(value_of_obj(IND_obj_aOUTC)<= ChargerConfig.PermissibleCurrentSensorError)
	{
		obj_state_off(IND_obj_KM1);
		obj->obj_def_value = 0;
	}
	else
	{
		obj->obj_def_value++;
		if(obj->obj_def_value > 5)
		{
			ChargerErrors.value.bit.main_contactor_error = 1;
			ChargerErrors.value.bit.internal_circuit_error = 1;
			obj_state_off(IND_obj_KM1);
		}
		OBJ_Event(IND_obj_tKM_Off);
	}
}

void pwm_common(OBJ_STRUCT_TypeDef *obj)
{
	if(obj->obj_state == 1)
	{
		PWM_ON;	
	}
	else
	{
		PWM_OFF;
	}	
}

void pwm_channel_4(OBJ_STRUCT_TypeDef *obj)
{
	if(obj-> obj_state == 1)
	{
		PWMSetValue(CH4,obj->obj_def_value);	
	}
}
void pwm_channel_3(OBJ_STRUCT_TypeDef *obj)
{
	if(obj-> obj_state == 1)
	{
		PWMSetValue(CH3,obj->obj_def_value);	
	}
	sync_led_invertor();
}

/*включение режима понижающего преобразователя*/
void BUCK_Mode_Handler(OBJ_STRUCT_TypeDef *obj)
{
	if((obj->obj_state == 1) &&(current_limit_trigger == 0))
	{
		/*вкл контактор*/
		pwm_module_init(value_of_obj(IND_obj_PWM_FREQ),BUCK_MODE);
		obj_state_on(IND_obj_KM1);
		value_of_obj(IND_obj_PWM_ON)= ChargerConfig.MinDutyCycle;
		obj_state_on(IND_obj_PWM_ON);
		PWM_ON;
	}
	else
	{	
		obj_state_off(IND_obj_PWM_ON);
		/*выкл контактор*/
		OBJ_Event(IND_obj_tKM_Off);
	}
}

/*включение режима повышающего преобразователя*/
void BOOST_Mode_Handler(OBJ_STRUCT_TypeDef *obj)
{
	if(obj->obj_state == 1)
	{
		pwm_module_init(ChargerConfig.Frequency,BUCK_BOOST_MODE);
	}
	else
	{
		pwm_module_init(0,OFF);	
	}
}

/*контроль частоты ШИМ*/
void PWM_freq_config_Handler(OBJ_STRUCT_TypeDef *obj){
	if(obj->obj_state){
		PWMSetFrequency(obj->obj_def_value);
	}
}

/*Включение и выключение ШИМ в микросхеме*/
void PWM_Control_Handler(OBJ_STRUCT_TypeDef *obj)
{
	if(obj->obj_state)
	{
		/*BOOST mode*/
		if(state_of_obj(IND_obj_M_BOOST_MODE) == 1)
		{
			pwm_control(BOOST_MODE,NULL,obj->obj_def_value,&ChargerConfig);
		}
		/*BUCK mode*/
		if(state_of_obj(IND_obj_M_BUCK_MODE) == 1)
		{
			pwm_control(BUCK_MODE,obj->obj_def_value,NULL,&ChargerConfig);
		}
	}
	else
	{
		PWM_OFF;
		pwm_control(OFF,NULL,NULL,&ChargerConfig);
	}
}

/*устатовка констант ПИД регулятора*/
void PID_COEF_Handler(OBJ_STRUCT_TypeDef *obj){
//	pid_current_out.Kp = (float)(this_obj(IND_obj_PID1_KP)->dWordL)/10000.0;
//	pid_current_out.Ki = (float)(this_obj(IND_obj_PID1_KI)->dWordL)/10000.0;
//	pid_current_out.Kd = (float)(this_obj(IND_obj_PID1_KD)->dWordL)/10000.0;
}

/*Активация ПИД регулятора (тест)*/
void PID_Control_Handler(OBJ_STRUCT_TypeDef *obj){
	if(obj->obj_state == 1){
		pid_current_out.setpoint_val =(uint16_t)obj->obj_def_value;
	}else{
		pid_current_out.setpoint_val = 0;
	}
}

/*запись конфигурации в flash память МК*/
void Write_config_Handler(OBJ_STRUCT_TypeDef *obj)
{
//	ChargerConfig.PrechargeMinVoltage = value_of_obj(IND_obj_cPMinV);
//	ChargerConfig.PrechargeMaxVoltage = value_of_obj(IND_obj_cPMaxV);
//	
//	ChargerConfig.PermissibleVoltageSensorError = value_of_obj(IND_obj_cSVError);
//	ChargerConfig.PermissibleCurrentSensorError = value_of_obj(IND_obj_cSCError);
	
	ChargerConfig.MaxDutyCycle = value_of_obj(IND_obj_cMaxDutyC);
	ChargerConfig.MinDutyCycle = value_of_obj(IND_obj_cMinDutyC);
	
//	ChargerConfig.MaxCurrrent = value_of_obj(IND_obj_cMaxTemp);
//	ChargerConfig.Frequency = value_of_obj(IND_obj_cFreq);
//	ChargerConfig.VoltageGysteresisMode = value_of_obj(IND_obj_cFreq);

//	if(obj->obj_state == 1){
//		/*!!! stop executing main program*/
//		write_configuration(&ChargerConfig);
//	}
}
