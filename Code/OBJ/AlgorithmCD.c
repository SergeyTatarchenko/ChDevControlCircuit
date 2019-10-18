/*************************************************
* File Name          : AlgorithmCD.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : Algorithm for charging device 
*************************************************/
#include "AlgorithmCD.h"
/*-----------------------------------------------*/
ChargerErrors_TypeDef ChargerErrors;
ChargerConfig_TypeDef ChargerConfig; 
/*-----------------------------------------------*/
/*load configuration from flash memory*/
int load_configuration(ChargerConfig_TypeDef* configuration)
{
	configuration->Frequency = 8000;
	configuration->MaxDutyCycle = 900;
	configuration->MinDutyCycle = 200;
	configuration->PermissibleVoltageSensorError = 20;
	configuration->PermissibleCurrentSensorError = 2;
	return 1;
}

int write_configuration(ChargerConfig_TypeDef* configuration)
{
	uint8_t array[sizeof(ChargerConfig_TypeDef)];
	flash_unlock();
	memcpy(array,&ChargerConfig,sizeof(array));
	flash_erase_page((uint32_t)GONFIG_ADRESS);
	flash_write_page(array,(uint32_t)GONFIG_ADRESS,sizeof(array));
	flash_lock();
	return 0;
}

int PowerBoardInit(ChargerErrors_TypeDef* errors,ChargerConfig_TypeDef* configuration,
	uint16_t InputVoltage,uint16_t InputCurrent,
	uint16_t OutputVoltage,uint16_t OutputCurrent)
{
	static int charger_permission = 0;
	/*старт алгоритма ЗУ, проверка входных датчиков на нулевые условия*/
	charger_permission = comparator(configuration->PermissibleCurrentSensorError,InputCurrent);
	if(!charger_permission)
	{
		/*утечка или ошибка датчика входного тока*/
		errors->value.bit.input_current_sensor_error = 1;
	}
	charger_permission &= comparator(configuration->PermissibleVoltageSensorError,InputVoltage);
	if(!charger_permission)
	{
		/*утечка или ошибка датчика входного напряжения*/
		errors->value.bit.input_voltage_sensor_error = 1;
	}
	charger_permission &= comparator(configuration->PermissibleCurrentSensorError,OutputCurrent);
	if(!charger_permission)
	{
		/*утечка или ошибка датчика выходного тока*/
		errors->value.bit.output_current_sensor_error = 1;
	}
	charger_permission &= comparator(configuration->PermissibleVoltageSensorError,OutputVoltage);
	if(!charger_permission)
	{
		/*утечка или ошибка датчика выходного напряжения*/
		errors->value.bit.output_voltage_sensor_error = 1;
	}
	/*в новой ревизии платы добавить проверку датчиков температуры ключей и радиатора + проверка обратной связи контактора*/
	return charger_permission;
}

void pwm_module_init(uint16_t frequency,CD_MODE mode)
{	
	PWMSetFrequency(frequency);
	switch(mode)
	{
		case BUCK_MODE:
			PWMSetActiveChannel(ALL_CH_OFF); /*clean settings for PWM channels*/
			PWMSetActiveChannel(CH4);
			break;
		case BOOST_MODE:
			PWMSetActiveChannel(ALL_CH_ON);
			break;
		case BUCK_BOOST_MODE:
			PWMSetActiveChannel(ALL_CH_ON);
			break;
		case OFF:
			PWMSetActiveChannel(ALL_CH_OFF);
			PWMSetValue(CH3,0);
			PWMSetValue(CH4,0);
			break;
		default:
			PWM_OFF;
			PWMSetActiveChannel(ALL_CH_OFF);
			PWMSetValue(CH3,0);
			PWMSetValue(CH4,0);
			break;
	}
}


void pwm_control(CD_MODE mode,uint16_t D1,uint16_t D2,ChargerConfig_TypeDef* configuration)
{
	if(D1 > configuration->MaxDutyCycle)
	{
		D1 = configuration->MaxDutyCycle;
	}
	if(D1 <configuration->MinDutyCycle)
	{
		D1 = configuration->MinDutyCycle;
	}
	if(D2 > configuration->MaxDutyCycle)
	{
		D2 = configuration->MaxDutyCycle;
	}
	if(D2 <configuration->MinDutyCycle)
	{
		D2 = configuration->MinDutyCycle;
	}
	switch(mode)
	{
		case BUCK_MODE:
			PWMSetValue(CH4,D1);
			break;
		case BOOST_MODE:
			PWMSetValue(CH3,D2);
			/*возможно надо перестраивать пин контроллера из AFPP в PP*/
			PWMSetValue(CH4,PERIOD_PWM);
			break;
		case BUCK_BOOST_MODE:
		//	PWMSetValue(ALL_CH_ON,D);
			break;
		case OFF:
			PWMSetValue(CH3,NULL);
			PWMSetValue(CH4,NULL);
			break;
		default:
			PWMSetValue(CH3,NULL);
			PWMSetValue(CH4,NULL);
			break;
	}
}

