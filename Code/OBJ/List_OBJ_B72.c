
#include "B72.h"
#include "global.h"

/************************************************************************************/
/* 									 OBJ_Handlers									*/
/************************************************************************************/
static uint8_t current_limit_trigger = 0;

/*first obj*/
void board_START(OBJ_STRUCT *obj)
{
	if(obj->obj_state == 1)
	{
		load_configuration(&ChargerConfig);
		value_of_obj(IND_obj_PWM_FREQ) = ChargerConfig.Frequency; 
		board_power = 1;
		OBJ_Event(IND_obj_USART_TX);
	}
	else
	{
		board_power = 0;
		//set_all_obj_off();
		PWM_OFF;
		pwm_control(OFF,NULL,NULL,&ChargerConfig);	
		/*���� ���������*/
		OBJ_Event(IND_obj_tKM_Off);
		
		SYNC_LED_OFF;
	}
}

void ADC0_Handler(OBJ_STRUCT *obj)
{
	/*	AIN0 - dvl1000 �������� ���������� */
	uint16_t value = obj->obj_value;
	value = (value*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	this_obj(IND_obj_aOUTV)->obj_value = get_dvl1000_value(value);
}

void ADC1_Handler(OBJ_STRUCT *obj)
{
	/*AIN1 - lac300 �������� ���*/
	uint16_t value = obj->obj_value;
	value = (value*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	this_obj(IND_obj_aOUTC)->obj_value = get_lac300_value(value);
	if((current_limit_trigger == 0)&&(value_of_obj(IND_obj_aOUTC)>value_of_obj(IND_obj_CURLIMIT)))
	{
		obj_state_off(IND_obj_M_BUCK_MODE);
		state_of_obj(IND_obj_CURLIMIT) = 1;
		current_limit_trigger = 1;
	}
}

void CurrentLimit(OBJ_STRUCT *obj)
{
	if(obj->obj_state == 0)
	{
		current_limit_trigger = 0;
	}
}

void ADC2_Handler(OBJ_STRUCT *obj)
{
	/*AIN2 - dvl1000 ������� ����������*/
	uint16_t value = obj->obj_value;
	value = (value*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	this_obj(IND_obj_aINV)->obj_value = get_dvl1000_value(value);
}

void ADC3_Handler(OBJ_STRUCT *obj)
{
	/*AIN3 - lac300 ������� ���*/
	uint16_t value = obj->obj_value;
	value = (value*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	this_obj(IND_obj_aINC)->obj_value = get_lac300_value(value);	
}

void ADC4_Handler(OBJ_STRUCT *obj)
{
	/*AIN4 - dvl1000   ���������� ��������*/
	uint16_t value = obj->obj_value;
	value = (value*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	this_obj(IND_obj_aDRV)->obj_value = get_dvl1000_value(value);	
}

void ADC5_Handler(OBJ_STRUCT *obj)
{
	/*AIN5 - lf510   ��� ��������*/
	uint16_t value = obj->obj_value;
	value = (value*(uint16_t)INT_ADC_REF)/(uint16_t)ADC_DEPTH;
	this_obj(IND_obj_aDRC)->obj_value = get_lf510_value(value);		
}

void ADC7_Handler(OBJ_STRUCT *obj)
{
	uint16_t temp_radiator;
	/*AIN6 - ����������� ��������� */
	uint16_t value = obj->obj_value;
	temp_radiator = ADC_B57045_1K21 (value);
	this_obj(IND_obj_TempRadiator)->obj_value = temp_radiator ;
}

/*�������� ����� ���������������� ���� �������� ����� �� �������� (�������� ������� � ����������)*/
void USART_Handler(OBJ_STRUCT *obj){
	obj->obj_value++;
	sync_led_invertor();
	
	if(board_power == 1){
		FAST_Upd_All_OBJ_USART();
		OBJ_Event(IND_obj_USART_TX);		
	}else{
		SYNC_LED_OFF;
		obj->obj_value = 0;
	}
}
/**/
void _Diagnostic_(OBJ_STRUCT *obj)
{
//	static int diagnostic_array[] = {_diagnostic_};
	
}
/*������ ���������� ���������� */
void KM_Off_Handler(OBJ_STRUCT *obj)
{
	if(value_of_obj(IND_obj_aOUTC)<= ChargerConfig.PermissibleCurrentSensorError)
	{
		obj_state_off(IND_obj_KM1);
		obj->obj_value = 0;
	}
	else
	{
		obj->obj_value++;
		if(obj->obj_value > 5)
		{
			ChargerErrors.value.bit.main_contactor_error = 1;
			ChargerErrors.value.bit.internal_circuit_error = 1;
		}
		OBJ_Event(IND_obj_tKM_Off);
	}
}

void pwm_common(OBJ_STRUCT *obj)
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

void pwm_channel_4(OBJ_STRUCT *obj)
{
	if(obj-> obj_state == 1)
	{
		PWMSetValue(CH4,obj->obj_value);	
	}
}
void pwm_channel_3(OBJ_STRUCT *obj)
{
	if(obj-> obj_state == 1)
	{
		PWMSetValue(CH3,obj->obj_value);	
	}
}

/*��������� ������ ����������� ���������������*/
void BUCK_Mode_Handler(OBJ_STRUCT *obj)
{
	if((obj->obj_state == 1) &&(current_limit_trigger == 0))
	{
		/*��� ���������*/
		pwm_module_init(ChargerConfig.Frequency,BUCK_MODE);
		obj_state_on(IND_obj_KM1);
		value_of_obj(IND_obj_PWM_ON)= ChargerConfig.MinDutyCycle;
		obj_state_on(IND_obj_PWM_ON);
		PWM_ON;
	}
	else
	{	
		PWM_OFF;
		pwm_control(OFF,NULL,NULL,&ChargerConfig);	
		/*���� ���������*/
		OBJ_Event(IND_obj_tKM_Off);
	}
}

/*��������� ������ ����������� ���������������*/
void BOOST_Mode_Handler(OBJ_STRUCT *obj)
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

/*�������� ������� ���*/
void PWM_freq_config_Handler(OBJ_STRUCT *obj){
	if(obj->obj_state){
		PWMSetFrequency(obj->obj_value);
	}
}

/*��������� � ���������� ��� � ����������*/
void PWM_Control_Handler(OBJ_STRUCT *obj)
{
	if(obj->obj_state)
	{
		/*BOOST mode*/
		if(state_of_obj(IND_obj_M_BOOST_MODE) == 1)
		{
			pwm_control(BOOST_MODE,NULL,obj->obj_value,&ChargerConfig);
		}
		/*BUCK mode*/
		if(state_of_obj(IND_obj_M_BUCK_MODE) == 1)
		{
			pwm_control(BUCK_MODE,obj->obj_value,NULL,&ChargerConfig);
		}
	}
	else
	{
		PWM_OFF;
		pwm_control(OFF,NULL,NULL,&ChargerConfig);
	}
}

/*��������� �������� ��� ����������*/
void PID_COEF_Handler(OBJ_STRUCT *obj){
	pid_current_out.Kp = (float)(this_obj(IND_obj_PID1_KP)->dWordL)/10000.0;
	pid_current_out.Ki = (float)(this_obj(IND_obj_PID1_KI)->dWordL)/10000.0;
	pid_current_out.Kd = (float)(this_obj(IND_obj_PID1_KD)->dWordL)/10000.0;
}

/*��������� ��� ���������� (����)*/
void PID_Control_Handler(OBJ_STRUCT *obj){
	if(obj->obj_state == 1){
		pid_current_out.setpoint_val =(uint16_t)obj->obj_value;
	}else{
		pid_current_out.setpoint_val = 0;
	}
}

/*������ ������������ � flash ������ ��*/
void Write_config_Handler(OBJ_STRUCT *obj)
{
	ChargerConfig.PrechargeMinVoltage = value_of_obj(IND_obj_cPMinV);
	ChargerConfig.PrechargeMaxVoltage = value_of_obj(IND_obj_cPMaxV);
	
	ChargerConfig.PermissibleVoltageSensorError = value_of_obj(IND_obj_cSVError);
	ChargerConfig.PermissibleCurrentSensorError = value_of_obj(IND_obj_cSCError);
	
	ChargerConfig.MaxDutyCycle = value_of_obj(IND_obj_cMaxDutyC);
	ChargerConfig.MinDutyCycle = value_of_obj(IND_obj_cMinDutyC);
	
	ChargerConfig.MaxCurrrent = value_of_obj(IND_obj_cMaxTemp);
	ChargerConfig.Frequency = value_of_obj(IND_obj_cFreq);
	ChargerConfig.VoltageGysteresisMode = value_of_obj(IND_obj_cFreq);
	
	if(obj->obj_state == 1){
		/*!!! stop executing main program*/
		write_configuration(&ChargerConfig);
	}
}
