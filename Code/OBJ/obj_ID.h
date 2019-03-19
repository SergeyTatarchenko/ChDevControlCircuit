#ifndef OBJ_ID_H_
#define	OBJ_ID_H_

/* byte[0]*/
#define	ID_NETWORK			0x01

/* byte[1]*/
#define	ID_DEVICE			0x72
#define ID_REMOTE_CNTRL		0x02

/* byte[2] & byte[3]*/
#define	IND_obj_NULL			0x00
#define	IND_obj_END				0xFF

/*control and status*/
#define IND_obj_CAS				3
/*control without status*/
#define IND_obj_CWS				2
/*status without control*/
#define IND_obj_SWC				1


/*
v 0.1
1) create object name  example   " #define obj_name	(IND_obj_NULL + x)"
2) create object type in List_OBJ.c
3) create prototype of object handler in List-OBJ.h
4) create object handler in List_OBJ.c
5) span object with handler in List_OBJ.c
*/


/*-----------------------------------------------*/
#define IND_obj_IO            (IND_obj_NULL + 1)	// входы выходы на плате
#define IND_obj_ADC1          (IND_obj_NULL + 2)	// аппаратный ацп 1
#define IND_obj_ADC2          (IND_obj_NULL + 3)	// аппаратный ацп 2
#define IND_obj_ADC3          (IND_obj_NULL + 4)	// аппаратный ацп 3
#define IND_obj_ADC4          (IND_obj_NULL + 5)	// аппаратный ацп 4
#define IND_obj_ADC5          (IND_obj_NULL + 6)	// аппаратный ацп 5
#define IND_obj_ADC6          (IND_obj_NULL + 7)	// аппаратный ацп 6

#define IND_obj_TICK          (IND_obj_NULL + 8)	// тик тест

#define IND_obj_LED           (IND_obj_NULL + 9)	// светодиод на плате

#define IND_obj_PWM           (IND_obj_NULL + 10)	// ШИМ

#define	num_of_all_obj			11		//! counter  (все объекты + 1)
/*-----------------------------------------------*/

#endif
