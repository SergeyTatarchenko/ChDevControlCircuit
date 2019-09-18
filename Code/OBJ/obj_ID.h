#ifndef OBJ_ID_H_
#define	OBJ_ID_H_


#define	IND_obj_NULL			0x00
#define	IND_obj_END				0xFF

/*-----------------------------------------------*/
#define obj_STATUS				(IND_obj_NULL + 1)	
/*---------------------HWOBJ---------------------*/
/*adc*/
#define IND_obj_aADC0			(IND_obj_NULL + 2)		// аппаратный ацп 1
#define IND_obj_aADC1			(IND_obj_NULL + 3)		// аппаратный ацп 2
#define IND_obj_aADC2			(IND_obj_NULL + 4)		// аппаратный ацп 3
#define IND_obj_aADC3			(IND_obj_NULL + 5)		// аппаратный ацп 4
#define IND_obj_aADC4			(IND_obj_NULL + 6)		// аппаратный ацп 5
#define IND_obj_aADC5			(IND_obj_NULL + 7)		// аппаратный ацп 6 
/*inputs*/
#define IND_obj_iInput0			(IND_obj_NULL + 8)		// аппаратный вход 1 
#define IND_obj_iInput1			(IND_obj_NULL + 9)		// аппаратный вход 2 
#define IND_obj_iInput2			(IND_obj_NULL + 10)		// аппаратный вход 3 
#define IND_obj_iInput3			(IND_obj_NULL + 11)		// аппаратный вход 4 
/*-----------------------------------------------*/
/*outputs*/
#define IND_obj_PredZar			(IND_obj_NULL + 12)		// аппаратный выход [вкл. плату предзаряда]
#define IND_obj_KM1				(IND_obj_NULL + 13)		// аппаратный выход [вкл. контактор КМ1]
/*-----------------------------------------------*/
#define IND_obj_PWM1			(IND_obj_NULL + 14)		// [аппаратный ШИМ 1 активен !ПОВЫШАЮЩИЙ режим]
#define IND_obj_PWM2			(IND_obj_NULL + 15)		// [аппаратный ШИМ 2 активен !ПОНИЖАЮЩИЙ режим]
/*-----------------SOFTOBJ-----------------------*/
#define IND_obj_USART_TX		(IND_obj_NULL + 16)		// [Таймер обновления состояния объектов платы по USART]
/*-----------------------------------------------*/
#define IND_obj_aINV			(IND_obj_NULL + 17)		// [входное напряжение ]
#define IND_obj_aINC			(IND_obj_NULL + 18)		// [входной ток        ]
#define IND_obj_aOUTV			(IND_obj_NULL + 19)		// [выходное напряжение]
#define IND_obj_aOUTC			(IND_obj_NULL + 20)		// [выходной ток       ]
#define IND_obj_aDRV			(IND_obj_NULL + 21)		// [напряжение дросселя]
#define IND_obj_aDRC			(IND_obj_NULL + 22)		// [ток дросселя       ] 

/*             ручное управление ШИМ                    */
#define IND_obj_PWM_FREQ		(IND_obj_NULL + 23)		// [Установка частоты ШИМ] 
#define IND_obj_PWM_ON			(IND_obj_NULL + 24)		// [Вкл./Выкл. ШИМ] 

/*           ПИД регулятор - 1                         */
#define IND_obj_PID1_KP			(IND_obj_NULL + 25)
#define IND_obj_PID1_KI			(IND_obj_NULL + 26)
#define IND_obj_PID1_KD			(IND_obj_NULL + 27)
#define IND_obj_PID_ON			(IND_obj_NULL + 28)

/*ручное управление режимами преобразователя (тестовое) */
#define IND_obj_BUCK_MODE		(IND_obj_NULL + 29)		//[понижающий режим преобразователя]
#define IND_obj_BOOST_MODE		(IND_obj_NULL + 30)		//[повышающий режим пребразователя]
#define IND_obj_DELAY_START		(IND_obj_NULL + 31)		//[Таймер задержки старта преобразователя]
/*-----------------------------------------------*/
#define IND_obj_ACUR_C			(IND_obj_NULL + 32)		//[предполагаемая амплитуда тока дросселя]
#define IND_obj_ACUR_G			(IND_obj_NULL + 33)		//[измеренная  амплитуда тока дросселя]
#define IND_obj_CUR_C			(IND_obj_NULL + 34)		//[предполагаемый максимальный ток в дросселе]
#define IND_obj_CUR_G			(IND_obj_NULL + 35)		//[измеренный максимальный ток в дросселе]
/*-----------------------------------------------*/
#define IND_obj_ECE	  			(IND_obj_NULL + 36)		//[текущий КПД системы]
#define IND_obj_Q	  			(IND_obj_NULL + 37)		//[коэффициент сглаживания выходного LC фильтра]
#define IND_obj_ERR_ARRAY	  	(IND_obj_NULL + 38)		//[массив ошибок ЗУ]
#define IND_obj_START		  	(IND_obj_NULL + 39)		//[команда "ПУСК" ЗУ после включения]
#define IND_obj_TEST2		  	(IND_obj_NULL + 40)		//[тест режима с двумя каналами одновременно]

#endif
