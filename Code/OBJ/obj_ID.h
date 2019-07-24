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
#define IND_obj_PredZar       (IND_obj_NULL + 8)		// аппаратный выход [вкл. плату предзаряда]
#define IND_obj_KM1           (IND_obj_NULL + 9)		// аппаратный выход [вкл. контактор КМ1]
/*-----------------------------------------------*/
#define IND_obj_PWM1          (IND_obj_NULL + 10)		// [аппаратный ШИМ 1 активен]
#define IND_obj_PWM2          (IND_obj_NULL + 11)		// [аппаратный ШИМ 2 активен]
/*-----------------SOFTOBJ-----------------------*/
#define IND_obj_TICK_1S       (IND_obj_NULL + 12)		// [тик c каждым ивентом]
/*-----------------------------------------------*/
#define IND_obj_ADC_CONV      (IND_obj_NULL + 13)		// [включение обработки датчиков ADC]

/*             ручное управление ШИМ                    */
#define IND_obj_PWM_FREQ      (IND_obj_NULL + 14)		// [Установка частоты ШИМ] 
#define IND_obj_PWM_ON        (IND_obj_NULL + 15)		// [Вкл./Выкл. ШИМ] 

/*           ПИД регулятор - 1                         */
#define IND_obj_PID1_KP		  (IND_obj_NULL + 16)
#define IND_obj_PID1_KI		  (IND_obj_NULL + 17)
#define IND_obj_PID1_KD		  (IND_obj_NULL + 18)
#define IND_obj_PID_ON	 	  (IND_obj_NULL + 19)

/*ручное управление режимами преобразователя (тестовое) */
#define IND_obj_BUCK_MODE	  (IND_obj_NULL + 20)	//[понижающий режим преобразователя]
#define IND_obj_BOOST_MODE	  (IND_obj_NULL + 21)	//[повышающий режим пребразователя]

/*тест таймеров*/
#define IND_obj_TIM1		  (IND_obj_NULL + 22)	//[Таймер 1]
#define IND_obj_TIM2		  (IND_obj_NULL + 23)	//[Таймер 2]

#endif
