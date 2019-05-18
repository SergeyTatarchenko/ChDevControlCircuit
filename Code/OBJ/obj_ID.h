#ifndef OBJ_ID_H_
#define	OBJ_ID_H_

#include "OBJ_MODEL.h"

#define	IND_obj_NULL			0x00
#define	IND_obj_END				0xFF

/*-------------------board special---------------------*/
enum obj_hw{adc_0 = 0,adc_1 = 1,adc_2 = 2,adc_3 = 3,adc_4 = 4,adc_5 = 5,in_0 = 6,in_1 = 7,in_2 = 8,in_3 = 9,
			out_0 = 10,out_1 = 11,out_2 = 12,out_3 = 13,out_4 = 14,out_5 = 15,out_6 = 16,out_7 = 17,
			pwm_0=18,pwm_1=19};

#define out_offset	out_0
#define pwm_offset	pwm_0
#define adc_offset	adc_0
#define in_offset	in_0			
/*-------------------board special---------------------*/

/*
v 0.3
1) create object name  example   " #define obj_name	(IND_obj_NULL + x)"
2) create object init like "obj_name_init  obj_index,class,snap,handler	
3) add 	object init to 	_obj_cofig_	
*/


/*-----------------------------------------------*/
#define obj_STATUS			  (IND_obj_NULL + 1)	
/*---------------------HWOBJ---------------------*/
#define IND_obj_ADC1          (IND_obj_NULL + 2)		// аппаратный ацп 1
/*-----------------------------------------------*/
#define IND_obj_OUT0          (IND_obj_NULL + 3)		// аппаратный выход 0
#define IND_obj_OUT7          (IND_obj_NULL + 4)		// аппаратный выход 7
/*-----------------------------------------------*/
//#define IND_obj_IN0           (IND_obj_NULL + 5)		// аппаратный вход (порог Uпит/2)
/*-----------------------------------------------*/
#define IND_obj_PWM0          (IND_obj_NULL + 6)		// аппаратный ШИМ 1
#define IND_obj_PWM1          (IND_obj_NULL + 7)		// аппаратный ШИМ 2
			/*-----------------SOFTOBJ-----------------------*/
#define IND_obj_TICK          (IND_obj_NULL + 8)	// тик тест
#define IND_obj_LED           (IND_obj_NULL + 9)	// светодиод на плате
#define IND_obj_PID_KP		  (IND_obj_NULL + 10)
#define IND_obj_PID_KI		  (IND_obj_NULL + 11)
#define IND_obj_PID_KD		  (IND_obj_NULL + 12)
#define IND_obj_PID_SET_VAl	  (IND_obj_NULL + 13)
#define IND_obj_PID_FDB		  (IND_obj_NULL + 14)

#define IND_obj_CHAR1         (IND_obj_NULL + 15)		//  
#define IND_obj_CHAR2         (IND_obj_NULL + 16)		//  
#define IND_obj_CHAR3         (IND_obj_NULL + 17)		//  
#define IND_obj_CHAR4         (IND_obj_NULL + 18)		//  

/*----------------------------------------------------------------------------------------------------\
           name           |      index          |   class     | type     | hw_snap  |   Handler       | 
\----------------------------------------------------------------------------------------------------*/

#define _obj_STATUS_init       obj_STATUS           ,IND_obj_CAS  ,obj_soft  ,   NULL   ,board_START
#define _obj_LED_init	       IND_obj_LED          ,IND_obj_CAS  ,obj_soft  ,   NULL   ,LED_Control_Handler
#define _obj_TICK_init	       IND_obj_TICK         ,IND_obj_SWC  ,obj_soft  ,   NULL   ,TICK_Handler

#define _obj_PID_KP_init       IND_obj_PID_KP        ,IND_obj_COM  ,obj_soft  ,   NULL   ,NULL
#define _obj_PID_KI_init       IND_obj_PID_KI        ,IND_obj_COM  ,obj_soft  ,   NULL   ,NULL
#define _obj_PID_KD_init       IND_obj_PID_KD        ,IND_obj_COM  ,obj_soft  ,   NULL   ,NULL
#define _obj_PID_KP_init       IND_obj_PID_KP        ,IND_obj_COM  ,obj_soft  ,   NULL   ,NULL

#define _obj_PID_SET_VAl_init  IND_obj_PID_SET_VAl   ,IND_obj_COM  ,obj_soft  ,   NULL   ,NULL
#define _obj_PID_FDB_init      IND_obj_PID_FDB       ,IND_obj_COM  ,obj_soft  ,   NULL   ,NULL
                               
/*---------------------------------------------------------------------------------------------------*/
#define _obj_ADC1_init	   IND_obj_ADC1         ,IND_obj_CAS  ,obj_hard  ,   adc_0   ,ADC_Handler
#define _obj_PWM0_init	   IND_obj_PWM0         ,IND_obj_CAS  ,obj_hard  ,   pwm_0   ,PWM_Handler
#define _obj_OUT0_init	   IND_obj_OUT0         ,IND_obj_CAS  ,obj_hard  ,   out_0   ,NULL
#define _obj_OUT7_init	   IND_obj_OUT7         ,IND_obj_CAS  ,obj_hard  ,   out_7   ,NULL
/*---------------------------------------------------------------------------------------------------*/

#define _obj_cofig_	{_obj_STATUS_init},{_obj_LED_init},{_obj_TICK_init}, \
					{_obj_OUT0_init},{_obj_OUT7_init},{_obj_ADC1_init},{_obj_PWM0_init},	\
					{_obj_PID_KP_init},{_obj_PID_KI_init},{_obj_PID_KD_init},{_obj_PID_KP_init}, \
					{_obj_PID_SET_VAl_init},{_obj_PID_FDB_init}

/*--------------------------------------------------------------------------------------*/
/*obj handlers*/
void board_START(OBJ_STRUCT *obj);
void ADC_Handler(OBJ_STRUCT *obj);
void TICK_Handler(OBJ_STRUCT *obj);
void LED_Control_Handler(OBJ_STRUCT *obj);
void PWM_Handler(OBJ_STRUCT *obj);
void Dummy_Handler(OBJ_STRUCT *obj);

#endif
