/*************************************************
* File Name          : OBJ_MODEL.h
* Author             : Tatarchenko S.
* Version            : v 1.1
* Description        : header for OBJ_MODEL.c 
*************************************************/
#ifndef OBJ_DATA_H_
#define	OBJ_DATA_H_

/*-----------------------------------------------*/
#include "stm32f10x.h"
#include "stdint.h"
#include "string.h"
/*-----------------------------------------------*/
#include "obj_model_config.h"
/*-----------------------------------------------*/
/*-----------------------------------------------*/
/*------------object description-----------------*/
/*-----------------------------------------------*/
#define LEN_NETW	1
#define LEN_ID		1
#define	LEN_INDEX	2
#define LEN_DATA	8
#define	LEN_CRC		2
#define LEN_HEAD_SIZE			(LEN_NETW + LEN_ID)
#define LEN_OBJ					(LEN_INDEX + LEN_DATA + LEN_CRC)
#define	LEN_USART_MSG_OBJ		(LEN_NETW + LEN_ID + LEN_INDEX + LEN_DATA + LEN_CRC)
/*-----------------------------------------------*/
#pragma pack(push,1)
typedef	struct{
	/* ID 2 byte*/
	uint8_t id[2];
	/* Data 8 byte*/
	union {		
		/*default obj field*/
		struct{
			union{
				uint8_t byte;
				struct{
					uint8_t state : 1;
					uint8_t event : 1;
					uint8_t rez2  : 1;
					uint8_t rez3  : 1;
					uint8_t rez4  : 1;
					uint8_t rez5  : 1;
					uint8_t rez6  : 1;
					uint8_t hardware  : 1;
				}bit;
			}control_byte;
			uint16_t HW_adress;
			uint16_t value;
			uint8_t rezerv[3];
		}default_field;
		/* extended data field for data transmit*/
		struct{
			uint8_t data[8];
		}data_field;
	}obj_field;	
}OBJ_STRUCT;
#pragma pack(pop)

#pragma pack(push,1)
typedef union{
	uint8_t status;
	struct{
		uint8_t power:1;
		uint8_t mode:1;
		uint8_t	hwobj:1;
		uint8_t	debug:1;
		uint8_t	rez4:1;
		uint8_t	rez5:1;
		uint8_t	rez6:1;
		uint8_t	rez7:1;
	}bit;
}BOARD_STATE;
#pragma pack(pop)

/*                 object type                   */
#define IND_obj_COM				4	/*data command*/
#define IND_obj_CAS				3	/*control and status*/
#define IND_obj_CWS				2	/*control without status*/
#define IND_obj_SWC				1	/*status without control*/
/*-----------------------------------------------*/
#define this_obj(obj_id)		(objDefault + obj_id)
/*---------------------------------------------*/
#define event_mask				0x02
#define state_mask				0x01
#define hardware_mask			0x80

#define typeof_obj				id[1]
#define status_field 			obj_field.default_field.control_byte.byte
#define obj_event				obj_field.default_field.control_byte.bit.event
#define obj_state				obj_field.default_field.control_byte.bit.state
#define obj_value				obj_field.default_field.value
#define hardware_adress			obj_field.default_field.HW_adress
#define obj_hardware			obj_field.default_field.control_byte.bit.hardware
#define obj_data				obj_field.default_field.data
/*-----------------------------------------------*/
/*-----------struct for USART frame--------------*/
/*-----------------------------------------------*/
#pragma pack(push,1)
typedef union{
	struct{
        uint8_t id_netw;
        uint8_t id_modul;
        uint8_t index[2];
        uint8_t data[LEN_DATA];
        uint16_t crc;
    }d_struct;
    uint8_t byte[LEN_USART_MSG_OBJ];
}USART_FRAME;
#pragma pack(pop)

/*-----------------------------------------------*/
/*-----------------------------------------------*/
/*           struct for CAN frame                */
/*-----------------------------------------------*/
/*-----------------------------------------------*/
/*         system arrays for CAN                 */
/*-----------------------------------------------*/
/*-----------------------------------------------*/


/*-----------------------------------------------*/
/*--------------Common variables-----------------*/
/*-----------------------------------------------*/
/*pointer to memory space of objects*/
extern OBJ_STRUCT *objDefault;
/*array of object handlers*/
extern void ((*obj_handlers[num_of_all_obj +1]))(OBJ_STRUCT*);

extern BOARD_STATE	board_state;

#ifdef	HARDWARE_OBLECT
	extern OBJ_STRUCT *HW_OBJ[NUM_OF_HWOBJ];
	
#endif	

/*-----------------------------------------------*/
/*-----------------------------------------------*/
/*----------Common functions prototypes----------*/
/*-----------------------------------------------*/

/*init obj model*/
void OBJ_Init(void);
/*create object*/
OBJ_STRUCT* Obj_Create(int obj_id, int obj_type);
/*object event*/
extern void OBJ_Event(int obj_id);
/*set obj state*/
extern void OBJ_SetState(int obj_id,int state);
/*hardware event handler, board special*/
extern void HWOBJ_event(OBJ_STRUCT* obj,int obj_id);
/*update this obj */
extern void OBJ_Upd_USART(OBJ_STRUCT *obj);
/*update all obj */
extern void Upd_All_OBJ_USART(void);
/*receive object data from message*/
extern void Rx_OBJ_Data(USART_FRAME *mes);
/*check control sum of receive data*/
extern uint8_t Check_CRC(USART_FRAME *Rx_obj_c);

/*-----------------------------------------------*/
extern void obj_snap(void);
#include "obj_ID.h"
/*-----------------------------------------------*/


#endif
