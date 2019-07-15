#ifndef OBJ_ID_H_
#define	OBJ_ID_H_


#define	IND_obj_NULL			0x00
#define	IND_obj_END				0xFF


/*-----------------------------------------------*/
#define obj_STATUS			  (IND_obj_NULL + 1)	
/*---------------------HWOBJ---------------------*/
#define IND_obj_aINV          (IND_obj_NULL + 2)		// аппаратный ацп 1 [входное напряжение ]
#define IND_obj_aINC          (IND_obj_NULL + 3)		// аппаратный ацп 2 [входной ток        ]
#define IND_obj_aOUTV         (IND_obj_NULL + 4)		// аппаратный ацп 3 [выходное напряжение]
#define IND_obj_aOUTC         (IND_obj_NULL + 5)		// аппаратный ацп 4 [выходной ток       ]
#define IND_obj_aDRV          (IND_obj_NULL + 6)		// аппаратный ацп 5 [напряжение дросселя]
#define IND_obj_aDRC          (IND_obj_NULL + 7)		// аппаратный ацп 6 [ток дросселя       ] 
/*-----------------------------------------------*/
#define IND_obj_OUT6          (IND_obj_NULL + 8)		// аппаратный выход 6
#define IND_obj_OUT7          (IND_obj_NULL + 9)		// аппаратный выход 7
/*-----------------------------------------------*/
#define IND_obj_IN0           (IND_obj_NULL + 10)		// аппаратный вход (порог Uпит/2) - не работает!!!
/*-----------------------------------------------*/
#define IND_obj_PWM1          (IND_obj_NULL + 11)		// [аппаратный ШИМ 1 активен]
#define IND_obj_PWM2          (IND_obj_NULL + 12)		// [аппаратный ШИМ 2 активен]

/*-----------------SOFTOBJ-----------------------*/

#define IND_obj_TICK_1S       (IND_obj_NULL + 13)		// [тик тест 1c]
#define IND_obj_TICK_100_ms   (IND_obj_NULL + 14)		// [тик тест 100 мс]
#define IND_obj_LED           (IND_obj_NULL + 15)		// [светодиод на плате]
#define IND_obj_ADC_CONV      (IND_obj_NULL + 16)		// [Обработка датчиков ADC]
#define IND_obj_PWM_FREQ      (IND_obj_NULL + 17)		// [Установка частоты ШИМ] 
#define IND_obj_PWM_ON        (IND_obj_NULL + 18)		// [Вкл./Выкл. ШИМ] 

/*ПИД регулятор - 1*/
#define IND_obj_PID1_KP		  (IND_obj_NULL + 19)
#define IND_obj_PID1_KI		  (IND_obj_NULL + 20)
#define IND_obj_PID1_KD		  (IND_obj_NULL + 21)
#define IND_obj_PID1_SET_VAl  (IND_obj_NULL + 22)
#define IND_obj_PID1_FDB	  (IND_obj_NULL + 23)

/*управление режимами преобразователя (тестовое) */

#define IND_obj_BUCK_MODE	  (IND_obj_NULL + 24)
#define IND_obj_BOOST_MODE	  (IND_obj_NULL + 25)

#define IND_obj_PIN0PWM		  (IND_obj_NULL + 26)
#define IND_obj_PIN1PWM		  (IND_obj_NULL + 27)

#endif
