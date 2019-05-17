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
v 0.2
1) create object name  example   " #define obj_name	(IND_obj_NULL + x)"
2) create prototype of object handler
3) create object type in List_OBJ.c
4) create object handler in List_OBJ.c
5) span object with handler in List_OBJ.c
*/


/*-----------------------------------------------*/
#define obj_STATUS			  (IND_obj_NULL + 1)	
/*---------------------HWOBJ---------------------*/
#define IND_obj_ADC1          (IND_obj_NULL + 2)		// ���������� ��� 1
/*-----------------------------------------------*/
#define IND_obj_OUT0          (IND_obj_NULL + 3)		// ���������� ����� 0
#define IND_obj_OUT7          (IND_obj_NULL + 4)		// ���������� ����� 7
/*-----------------------------------------------*/
//#define IND_obj_IN0           (IND_obj_NULL + 5)		// ���������� ���� (����� U���/2)
/*-----------------------------------------------*/
#define IND_obj_PWM0          (IND_obj_NULL + 6)		// ���������� ��� 1
#define IND_obj_PWM1          (IND_obj_NULL + 7)		// ���������� ��� 2

			/*-----------------SOFTOBJ-----------------------*/
#define IND_obj_TICK          (IND_obj_NULL + 8)	// ��� ����
#define IND_obj_LED           (IND_obj_NULL + 9)	// ��������� �� �����
#define IND_obj_PID_KP		  (IND_obj_NULL + 10)
#define IND_obj_PID_KI		  (IND_obj_NULL + 11)
#define IND_obj_PID_KD		  (IND_obj_NULL + 12)
#define IND_obj_PID_SET_VAl	  (IND_obj_NULL + 13)
#define IND_obj_PID_FDB		  (IND_obj_NULL + 14)

#define IND_obj_CHAR1         (IND_obj_NULL + 15)		//  
#define IND_obj_CHAR2         (IND_obj_NULL + 16)		//  
#define IND_obj_CHAR3         (IND_obj_NULL + 17)		//  
#define IND_obj_CHAR4         (IND_obj_NULL + 18)		//  

/*-----------------------------------------------*/

/*-----------------------------------------------*/
/*obj handlers*/
void board_START(OBJ_STRUCT *obj);
void ADC_Handler(OBJ_STRUCT *obj);
void TICK_Handler(OBJ_STRUCT *obj);
void LED_Control_Handler(OBJ_STRUCT *obj);
void PWM_Handler(OBJ_STRUCT *obj);
void Dummy_Handler(OBJ_STRUCT *obj);

#endif
