#ifndef OBJ_DATA_H_
#define	OBJ_DATA_H_

#include "usart.h"
#include "user_tasks.h"
#include "obj_ID.h"
#include "List_OBJ.h"

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
#define	LEN_INDEX	1
#define LEN_DATA	8
#define	LEN_CRC		2

#define	LEN_MSG_OBJ		(LEN_NETW + LEN_ID + LEN_INDEX + LEN_DATA + LEN_CRC)

#define	FLAG_RX_REMOTE_CTRL		0x02
#define	FLAG_RX_ALL				0xFF

#pragma pack(push,1)
typedef	struct{
	
	/* ID 1 byte*/
	uint8_t id;
	
	/* Data 8 byte*/
	union {
		
		U8			b8[8];
		uint8_t 	d8b[8];	
		
		U16			b16[4];
		uint16_t 	d16b[4];
		
		U32			b32[2];
		uint32_t	d32b[2];
		
		uint64_t	d64b;
	
	}data;
}OBJ_STRUCT;
#pragma pack(pop)
/*-----------------------------------------------*/
/*           struct for usart frame              */
/*-----------------------------------------------*/
typedef union{
	
	struct{
        uint8_t id_netw;
        uint8_t id_modul;
        uint8_t index;
        uint8_t data[LEN_DATA];
        uint16_t crc;
    }d_struct;

    uint8_t byte[LEN_MSG_OBJ];
}TX_RX_FRAME;
/*-----------------------------------------------*/

extern uint8_t	USART1_transmit_array[LEN_MSG_OBJ];

/*-----------------------------------------------*/
/*pointer to memory space of objects*/
extern OBJ_STRUCT *objDefault;
/*-----------------------------------------------*/

/*init obj model*/
extern void OBJ_Init(void);

/*init all object from obj_ID.h*/
extern void OBJ_create(OBJ_STRUCT *obj);

/*object event*/
extern void OBJ_event(OBJ_STRUCT *obj,void(*obj_func)(void));

/*update this obj */
extern void OBJ_Upd(OBJ_STRUCT *obj);

/*update all obj */
extern void Upd_All_OBJ(void);


//uint8_t	Tx_OBJ_Data(OBJ_STRUCT *obj);	// Transfer Data Obj to USART
void Tx_OBJ(uint16_t *index);
uint8_t	Rx_OBJ_Data(void);				// Receive Data Obj from USART
uint8_t Check_CRC(TX_RX_FRAME *Rx_obj_c);
uint8_t Data_to_OBJ(TX_RX_FRAME *Rx_obj_d);

#define	obj_ram_addr(obj_)		&obj_	
#define	objU8_byte(obj_v)		obj_v.Byte_
#define	objU_byte(obj_v, b)	    obj_v.Byte[b].Byte_
#define	objU_word(obj_v, b)		obj_v.Word[b].Word

#define this_obj(obj_id)		(objDefault + obj_id)

#endif
