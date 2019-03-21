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
//#define IND_obj_IN			(IND_obj_NULL + 0x10)	// inputs
//#define IND_obj_OUT			(IND_obj_NULL + 0x20)	// outputs
//#define IND_obj_ADC			(IND_obj_NULL + 0x30)	// ADC inputs
//#define IND_obj_ALL			(IND_obj_NULL + 0x40)	// user obj

#define IND_obj_IN			(IND_obj_NULL + 16)	// inputs
#define IND_obj_OUT			(IND_obj_NULL + 32)	// outputs
#define IND_obj_ADC			(IND_obj_NULL + 48)	// ADC inputs
#define IND_obj_ALL			(IND_obj_NULL + 64)	// user obj

/*-----------------------------------------------*/
#define IND_obj_IN0            (IND_obj_IN + 1)		// ���� 1
#define IND_obj_IN1            (IND_obj_IN + 2)		// ���� 2
#define IND_obj_IN2            (IND_obj_IN + 3)		// ���� 3
#define IND_obj_IN3            (IND_obj_IN + 4)		// ���� 4
#define IND_obj_IN4            (IND_obj_IN + 5)		// ���� 5
#define IND_obj_IN5            (IND_obj_IN + 6)		// ���� 6
#define IND_obj_IN6            (IND_obj_IN + 7)		// ���� 7
#define IND_obj_IN7            (IND_obj_IN + 8)		// ���� 8
/*-----------------------------------------------*/
#define IND_obj_OUT0           (IND_obj_OUT + 1)	// ����� 1
#define IND_obj_OUT1           (IND_obj_OUT + 2)	// ����� 2
#define IND_obj_OUT2           (IND_obj_OUT + 3)	// ����� 3
#define IND_obj_OUT3           (IND_obj_OUT + 4)	// ����� 4
#define IND_obj_OUT4           (IND_obj_OUT + 5)	// ����� 5
#define IND_obj_OUT5           (IND_obj_OUT + 6)	// ����� 6
#define IND_obj_OUT6           (IND_obj_OUT + 7)	// ����� 7
#define IND_obj_OUT7           (IND_obj_OUT + 8)	// ����� 8
/*-----------------------------------------------*/
#define IND_obj_ADC1          (IND_obj_ADC + 1)		// ���������� ��� 1
#define IND_obj_ADC2          (IND_obj_ADC + 2)		// ���������� ��� 2
#define IND_obj_ADC3          (IND_obj_ADC + 3)		// ���������� ��� 3
#define IND_obj_ADC4          (IND_obj_ADC + 4)		// ���������� ��� 4
#define IND_obj_ADC5          (IND_obj_ADC + 5)		// ���������� ��� 5
#define IND_obj_ADC6          (IND_obj_ADC + 6)		// ���������� ��� 6
/*-----------------------------------------------*/

/*-----------------------------------------------*/
#define IND_obj_TICK          (IND_obj_ALL    )	// ��� ����
#define IND_obj_LED           (IND_obj_ALL + 1)	// ��������� �� �����
#define IND_obj_PWM           (IND_obj_ALL + 2)	// ���

#define	num_of_all_obj		  (IND_obj_ALL + 3)		//! counter  (��� ������� + 1)
/*-----------------------------------------------*/

#endif
