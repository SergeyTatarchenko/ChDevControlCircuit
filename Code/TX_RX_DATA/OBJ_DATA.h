#ifndef OBJ_DATA_H_
#define	OBJ_DATA_H_

#include "global.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "usart.h"
#include "obj_ID.h"

#define	obj_ram_addr(obj_)		&obj_	
#define	objU8_byte(obj_v)		obj_v.Byte_
#define	objU_byte(obj_v, b)	    obj_v.Byte[b].Byte_
#define	objU_word(obj_v, b)		obj_v.Word[b].Word

#define this_obj(obj_id)		(objDefault + obj_id)



/*-----------------------------------------------*/
typedef union {
	uint8_t Byte_;
	
	struct bit{
		uint8_t b0 :1;
		uint8_t b1 :1;
		uint8_t b2 :1;
		uint8_t b3 :1;
		uint8_t b4 :1;
		uint8_t b5 :1;
		uint8_t b6 :1;
		uint8_t b7 :1;
	}Bit;
}U8;

typedef union {
	uint16_t Word;
	U8 Byte[2];
}U16;

typedef union{
	uint32_t DWord;
	U16 Word[2];
	U8 Byte[4];
}U32;

typedef union{
	uint64_t DDWord;
	U32 DWord[2];
	U16 Word[4];
	U8 Byte[8];
}U64;
/*-----------------------------------------------*/

/*-----------------------------------------------*/
/*            object description                 */
/*-----------------------------------------------*/
#define LEN_NETW	1
#define LEN_ID		1
#define	LEN_INDEX	2
#define LEN_DATA	8
#define	LEN_CRC		2

#define LEN_HEAD_SIZE	(LEN_NETW + LEN_ID)
#define	LEN_MSG_OBJ		(LEN_NETW + LEN_ID + LEN_INDEX + LEN_DATA + LEN_CRC)


/**/
#define MES_BUF_SIZE	20


#define	FLAG_RX_REMOTE_CTRL		0x02
#define	FLAG_RX_ALL				0xFF



#pragma pack(push,1)

typedef	struct{
	
	/* ID 2 byte*/
	uint8_t id[2];
	
	/* Data 8 byte*/
	union {
		
		U8			b8[8];
		uint8_t 	d8b[8];	
		
		U16			b16[4];
		uint16_t 	d16b[4];
		
		U32			b32[2];
		uint32_t	d32b[2];
		
		uint64_t	d64b;
		
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
			
			uint8_t data[7];
		}default_field;
		
	
	}obj_field;
	
}OBJ_STRUCT;
#pragma pack(pop)

#define obj_event				obj_field.default_field.control_byte.bit.event
#define obj_state				obj_field.default_field.control_byte.bit.state
#define obj_hardware			obj_field.default_field.control_byte.bit.hardware
#define obj_data				obj_field.default_field.data


#define status_field 			obj_field.default_field.control_byte.byte
/*-----------------------------------------------*/
/*           struct for usart frame              */
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

    uint8_t byte[LEN_MSG_OBJ];
}TX_RX_FRAME;
#pragma pack(pop)
/*-----------------------------------------------*/

/* data array for usart obj transfer */
extern uint8_t	USART1_transmit_array[LEN_MSG_OBJ];

/* data array for usart obj receive */
extern uint8_t USART1_receive_array[LEN_MSG_OBJ];

/*usart data byte counter */
extern uint8_t usart_irq_counter;
/*-----------------------------------------------*/
/*pointer to memory space of objects*/
extern OBJ_STRUCT *objDefault;

/*mutex  to perform currect usart transmit */
extern xSemaphoreHandle xMutex_USART_BUSY;

/*queue of messages from usart module*/
extern xQueueHandle usart_receive_buffer;

/*array of object handlers*/
extern void ((*obj_handlers[num_of_all_obj +1]))(OBJ_STRUCT*);
/*-----------------------------------------------*/

/*init obj model*/
void OBJ_Init(void);

/*create object*/
OBJ_STRUCT* Obj_Create(int obj_id, int obj_type);

/*snap obj with MCP23017*/
void Obj_MCP23017_snap(void);

/*upd mcp23017 obj, run in vGetIOState*/
void Obj_MCP23017_upd(void);

/*object event*/
void OBJ_Event(int obj_id);

/*update this obj */
void OBJ_Upd(OBJ_STRUCT *obj);

/*update all obj */
void Upd_All_OBJ(void);

/*receive object data from message*/
void Rx_OBJ_Data(TX_RX_FRAME *mes);

/*-----------------------------------------------*/
uint8_t Check_CRC(TX_RX_FRAME *Rx_obj_c);


/*data command*/
#define IND_obj_COM				4
/*control and status*/
#define IND_obj_CAS				3
/*control without status*/
#define IND_obj_CWS				2
/*status without control*/
#define IND_obj_SWC				1

/* byte[0]*/
#define	ID_NETWORK			0x01

/* byte[1]*/
#define	ID_DEVICE			0x72
#define ID_REMOTE_CNTRL		0x02

/*-----------------------------------------------*/
/*include object handlers*/
#include "List_OBJ.h"
/*-----------------------------------------------*/


#endif
