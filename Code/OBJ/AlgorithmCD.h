/*************************************************
* File Name          : AlgorithmCD.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : AlgorithmCD.c header
*************************************************/
#ifndef ALGORITHM_CD_H
#define ALGORITHM_CD_H
/*-----------------------------------------------*/
#include "global.h"
/*-----------------------------------------------*/
#pragma pack(push,1)
typedef struct{
	union{
		uint16_t value;
		struct{
			unsigned power_buck_driver_error:1;			/*bit 0 ошибка в цепи питания драйвера верхнего ключа*/
			unsigned power_boost_driver_error:1;		/*bit 1 ошибка в цепи питания драйвера нижнего  ключа*/
			unsigned input_voltage_sensor_error:1;		/*bit 2 ошибка датчика входного напряжения*/	
			unsigned input_current_sensor_error:1;		/*bit 3 ошибка датчика входного тока*/
			unsigned output_voltage_sensor_error:1;		/*bit 4 ошибка датчика выходного напряжения*/
			unsigned output_current_sensor_error:1;		/*bit 5 ошибка датчика выходного тока*/
			unsigned throttle_voltage_sensor_error:1;	/*bit 6 ошибка датчика напряжения дросселя*/
			unsigned throttle_current_sensor_error:1;	/*bit 7 ошибка датчика тока дросселя*/
			unsigned internal_circuit_error:1;			/*bit 8 Внутренняя ошибка платы управления*/
			unsigned precharge_circuit_error:1;			/*bit 9 Неисправность платы предзаряда*/
			unsigned buck_switch_overheat:1;			/*bit 10 перегрев ключа верхнего транзистора*/	
			unsigned boost_switch_overheat:1;			/*bit 11 перегрев ключа нижнего транзистора*/
			unsigned buck_algorithm_error:1;			/*bit 12 отказ управления в понижающем режиме*/
			unsigned boost_algorithm_error:1;			/*bit 13 отказ управления в повышающем режиме*/
			unsigned main_contactor_error:1;			/*bit 14 залипание или отказ контактора КМ1*/
			unsigned main_overheat:1;					/*bit 15 Общий перегрев ЗУ*/
		}bit;
	}value;
}ChargerErrors_TypeDef;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct{
	
	uint16_t PrechargeMinVoltage;
	uint16_t PrechargeMaxVoltage;
	uint8_t  PermissibleCurrentSensorError;
	uint8_t  PermissibleVoltageSensorError;
	uint16_t MinDutyCycle;
	uint16_t MaxDutyCycle;
	uint16_t MaxCurrrent;
	uint16_t MaxTemperature;
	uint16_t Frequency;
	uint16_t VoltageGysteresisMode;
	
}ChargerConfig_TypeDef;
#pragma pack(pop)
/*-----------------------------------------------*/
#define GONFIG_PAGE	127
#define GONFIG_ADRESS	(FLASH_START_ADRESS+(FLASH_PAGE_SIZE*GONFIG_PAGE)+GONFIG_PAGE)
/*-----------------------------------------------*/
extern ChargerErrors_TypeDef ChargerErrors;
extern ChargerConfig_TypeDef ChargerConfig;
/*-----------------------------------------------*/
typedef enum{
	BUCK_MODE = 1, BOOST_MODE = 2, BUCK_BOOST_MODE = 3, OFF = 4
}CD_MODE;
typedef enum{
	ILDE = 1, CHARGING = 2, FAULT = 3
}CD_STATE;
/*-----------------------------------------------*/
/*Checking the initial state of the charging device*/
int PowerBoardInit(ChargerErrors_TypeDef* errors,ChargerConfig_TypeDef* configuration,
	uint16_t InputVoltage,uint16_t InputCurrent,uint16_t OutputVoltage,uint16_t OutputCurrent);
/*setup the PWM unit in MCPU*/
void pwm_module_init(uint16_t frequency,CD_MODE mode);
/*PWM module control function*/
void pwm_control(CD_MODE mode,uint16_t D1,uint16_t D2,ChargerConfig_TypeDef* configuration);
/*load configuration from memory (WARNING!!! watchdog disable)*/
int load_configuration(ChargerConfig_TypeDef* configuration);
/*write configuration to memory (WARNING!!! watchdog disable)*/
int write_configuration(ChargerConfig_TypeDef* configuration);


CD_MODE ChargingModeSelect(uint16_t InputVoltage,uint16_t OutputVoltage);

#endif
