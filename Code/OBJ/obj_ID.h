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
#define IND_obj_aADC6			(IND_obj_NULL + 8)		// аппаратный ацп 7
#define IND_obj_aADC7			(IND_obj_NULL + 9)		// аппаратный ацп 8
/*inputs*/
#define IND_obj_iInput0			(IND_obj_NULL + 10)		// аппаратный вход 0 
#define IND_obj_iInput1			(IND_obj_NULL + 11)		// аппаратный вход 1 
#define IND_obj_iInput2			(IND_obj_NULL + 12)		// аппаратный вход 2 
#define IND_obj_iInput3			(IND_obj_NULL + 13)		// аппаратный вход 3 
#define IND_obj_iInput4			(IND_obj_NULL + 14)		// аппаратный вход 4 
#define IND_obj_iInput5			(IND_obj_NULL + 15)		// аппаратный вход 5 
#define IND_obj_iInput6			(IND_obj_NULL + 16)		// аппаратный вход 6 
#define IND_obj_iInput7			(IND_obj_NULL + 17)		// аппаратный вход 7 
#define IND_obj_iInput8			(IND_obj_NULL + 18)		// аппаратный вход 8 
/*-----------------------------------------------*/
/*outputs*/
#define IND_obj_oOUT0			(IND_obj_NULL + 19)		// аппаратный выход 0 
#define IND_obj_oOUT1			(IND_obj_NULL + 20)		// аппаратный выход 1 
#define IND_obj_oOUT2			(IND_obj_NULL + 21)		// аппаратный выход 2
#define IND_obj_oOUT3			(IND_obj_NULL + 22)		// аппаратный выход 3
#define IND_obj_oOUT4			(IND_obj_NULL + 23)		// аппаратный выход 4
#define IND_obj_oOUT5			(IND_obj_NULL + 24)		// аппаратный выход 5
#define IND_obj_PredZar			(IND_obj_NULL + 25)		// аппаратный выход 6 [вкл. плату предзаряда]
#define IND_obj_KM1 			(IND_obj_NULL + 26)		// аппаратный выход 7 [вкл. контактор КМ1] 
/*-----------------------------------------------*/
#define IND_obj_PWM1			(IND_obj_NULL + 27)		// [аппаратный ШИМ 1 активен !ПОВЫШАЮЩИЙ режим]
#define IND_obj_PWM2			(IND_obj_NULL + 28)		// [аппаратный ШИМ 2 активен !ПОНИЖАЮЩИЙ режим]
/*-----------------SOFTOBJ-----------------------*/
#define IND_obj_USART_TX		(IND_obj_NULL + 29)		// [Таймер обновления состояния объектов платы по USART]
/*-----------------------------------------------*/
#define IND_obj_aINV			(IND_obj_NULL + 30)		// [входное напряжение ]
#define IND_obj_aINC			(IND_obj_NULL + 31)		// [входной ток        ]
#define IND_obj_aOUTV			(IND_obj_NULL + 32)		// [выходное напряжение]
#define IND_obj_aOUTC			(IND_obj_NULL + 33)		// [выходной ток       ]
#define IND_obj_aDRV			(IND_obj_NULL + 34)		// [напряжение дросселя]
#define IND_obj_aDRC			(IND_obj_NULL + 35)		// [ток дросселя       ] 

/*             ручное управление ШИМ                    */
#define IND_obj_PWM_FREQ		(IND_obj_NULL + 36)		// [Установка частоты ШИМ (установить сразу как включили !!!)] 
#define IND_obj_PWM_ON			(IND_obj_NULL + 37)		// [Вкл./Выкл. ШИМ и управление скважностью] 
/*ручное управление режимами преобразователя (тестовое) */
#define IND_obj_MANUAL_MODE		(IND_obj_NULL + 38)		//[ручной режим работы преобразователя]
#define IND_obj_BUCK_MODE		(IND_obj_NULL + 39)		//[понижающий режим преобразователя]
#define IND_obj_BOOST_MODE		(IND_obj_NULL + 40)		//[повышающий режим пребразователя]
#define IND_obj_DELAY_START		(IND_obj_NULL + 41)		//[Таймер задержки старта преобразователя]
/*-----------------------------------------------*/
#define IND_obj_ACUR_C			(IND_obj_NULL + 42)		//[предполагаемая амплитуда тока дросселя]
#define IND_obj_ACUR_G			(IND_obj_NULL + 43)		//[измеренная  амплитуда тока дросселя]
#define IND_obj_CUR_C			(IND_obj_NULL + 44)		//[предполагаемый максимальный ток в дросселе]
#define IND_obj_CUR_G			(IND_obj_NULL + 45)		//[измеренный максимальный ток в дросселе]
#define IND_obj_ECE	  			(IND_obj_NULL + 46)		//[текущий КПД системы]
#define IND_obj_Q	  			(IND_obj_NULL + 47)		//[коэффициент сглаживания выходного LC фильтра]
/*-----------------------------------------------*/
#define IND_obj_ERR_ARRAY	  	(IND_obj_NULL + 48)		//[массив ошибок ЗУ]
#define IND_obj_START		  	(IND_obj_NULL + 49)		//[команда "ПУСК" ЗУ после включения]
/*-----------------------------------------------*/
/*           ПИД регулятор - 1                   */
#define IND_obj_PID1_KP			(IND_obj_NULL + 50)
#define IND_obj_PID1_KI			(IND_obj_NULL + 51)
#define IND_obj_PID1_KD			(IND_obj_NULL + 52)
#define IND_obj_PID_ON			(IND_obj_NULL + 53)
#define IND_obj_TEST2			(IND_obj_NULL + 54)		// [Режим с двумя ключами одноверменно !!!]

#endif
