#ifndef OBJ_ID_H_
#define	OBJ_ID_H_

#include "OBJ_MODEL.h"

#define	IND_obj_NULL			0x00
#define	IND_obj_END				0xFF

/**/
enum obj_adc{adc_1 = 1,adc_2 = 2,adc_3 = 3,adc_4 = 4,adc_5 = 5,adc_6 = 6};
enum obj_in {in_0 = 7,in_1 = 8,in_2 = 9,in_3 = 10};
enum obj_out{out_0 = 11,out_1 = 12,out_2 = 12,out_3 = 13,out_4 = 14,out_5 = 15,out_6 = 16,out_7 = 17};

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
/*-----------------SOFTOBJ-----------------------*/
#define IND_obj_TICK          (IND_obj_NULL + 2)	// тик тест
#define IND_obj_LED           (IND_obj_NULL + 3)	// светодиод на плате
#define IND_obj_PWM           (IND_obj_NULL + 4)	// ШИМ

#define IND_obj_TEST	      (IND_obj_NULL + 5)	// тест

#define IND_obj_PID_KP		  (IND_obj_NULL + 6)
#define IND_obj_PID_KI		  (IND_obj_NULL + 7)
#define IND_obj_PID_KD		  (IND_obj_NULL + 8)
#define IND_obj_PID_SET_VAl	  (IND_obj_NULL + 9)
#define IND_obj_PID_FDB		  (IND_obj_NULL + 10)
/*---------------------HWOBJ---------------------*/
#define IND_obj_ADC1          (IND_obj_NULL + 11)		// аппаратный ацп 1
/*-----------------------------------------------*/


/*-----------------------------------------------*/
/*obj handlers*/
void board_START(OBJ_STRUCT *obj);
void ADC_Handler(OBJ_STRUCT *obj);
void TICK_Handler(OBJ_STRUCT *obj);
void LED_Control_Handler(OBJ_STRUCT *obj);
void Dummy_Handler(OBJ_STRUCT *obj);

#endif
