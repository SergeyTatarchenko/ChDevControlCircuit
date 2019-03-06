#ifndef OBJ_ID_H_
#define	OBJ_ID_H_

/* byte[0]*/
#define	ID_NETWORK			0x01

/* byte[1]*/
#define	MY_ID				0x72
#define ID_REMOTE_CNTRL		0x02

/* byte[2] & byte[3]*/
#define	IND_obj_NULL			0x0000
#define	IND_obj_END				0x00FF

/*control and status*/
#define IND_obj_CAS				2
/*control without status*/
#define IND_obj_CWS				1
/*status without control*/
#define IND_obj_SWC				0


/*
v 0.1
1) create object name  example   " #define obj_name	(IND_obj_NULL + x)"
3) create prototype of object handler in List-OBJ.h
4) create object handler in List_OBJ.c
5) span object with handler in List_OBJ.c
*/


/*-----------------------------------------------*/
#define IND_obj_CTRL            (IND_obj_NULL + 1)
#define IND_obj_SetPORT_DIO     (IND_obj_NULL + 2)
#define IND_obj_SetPWM			(IND_obj_NULL + 3)
#define IND_obj_SetPID2_0		(IND_obj_NULL + 4)
#define	IND_obj_SetPID2_1       (IND_obj_NULL + 5)
#define IND_obj_SetPID1_0		(IND_obj_NULL + 6)
#define	IND_obj_SetPID1_1       (IND_obj_NULL + 7)
/*-----------------------------------------------*/    
#define	IND_obj_VOLTAGE			(IND_obj_NULL + 8)
#define IND_obj_CURRENT			(IND_obj_NULL + 9)
#define IND_obj_CNT				(IND_obj_NULL +10)
#define	IND_obj_STATUS			(IND_obj_NULL +11)
#define	IND_obj_PWM  			(IND_obj_NULL +12)
#define IND_obj_fb_PORT_DIO 	(IND_obj_NULL +13)
#define IND_obj_PID1_0          (IND_obj_NULL +14)
#define	IND_obj_PID1_1          (IND_obj_NULL +15)
#define IND_obj_PID2_0          (IND_obj_NULL +16)
#define	IND_obj_PID2_1          (IND_obj_NULL +17)

#define	num_of_all_obj			17		//! counter
/*-----------------------------------------------*/

#endif
