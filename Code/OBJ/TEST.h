#ifndef TEST_H_
#define	TEST_H_


#include "OBJ_MODEL.h"
#include "obj_ID.h"
#include "global.h"
/*-------------------------------------------------*/
#define	ID_NETWORK			0x01
#define	ID_DEVICE			0x00
#define ID_REMOTE_CNTRL		0x02
#define	FLAG_RX_ALL			0xFF

/*
v 0.3
1) create object name  example   " #define obj_name	(IND_obj_NULL + x)"
2) create object init like "obj_name_init  obj_index,class,snap,handler	
3) add 	object init to 	_obj_cofig_	
*/
/*----------------------------------------------------------------------------------------------------\
           name           |      index          |   class     | type     | hw_snap  |   Handler       | 
\----------------------------------------------------------------------------------------------------*/

#define _obj_STATUS_init       obj_STATUS           ,IND_obj_CAS  ,obj_soft  ,   NULL   ,board_START
#define _obj_LED_init	       IND_obj_LED          ,IND_obj_CAS  ,obj_soft  ,   NULL   ,LED_Control_Handler
#define _obj_TICK_1S_init      IND_obj_TICK_1S      ,IND_obj_SWC  ,obj_soft  ,   NULL   ,TICK_Handler
#define _obj_TICK_100_ms_init  IND_obj_TICK_100_ms  ,IND_obj_SWC  ,obj_soft  ,   NULL   ,TICK_Handler

#define _obj_cofig_	{_obj_STATUS_init},{_obj_LED_init},{_obj_TICK_1S_init},{_obj_TICK_100_ms_init}
					

/*--------------------------------------------------------------------------------------*/
			
/*-------------------------------------------------*/
/*obj handlers*/
void board_START(OBJ_STRUCT *obj);
void TICK_Handler(OBJ_STRUCT *obj);
void LED_Control_Handler(OBJ_STRUCT *obj);
#endif
