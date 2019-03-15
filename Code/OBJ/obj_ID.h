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

#define	num_of_all_obj			1		//! counter
/*-----------------------------------------------*/

#endif
