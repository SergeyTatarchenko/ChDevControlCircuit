#ifndef OBJ_DATA_H_
#define	OBJ_DATA_H_

#include "usart.h"
#include "obj_ID.h"
#include "global.h"
#include "List_OBJ.h"
//#include "system_stm32f10x.h"

#define LEN_NETW	1
#define LEN_ID		1
#define	LEN_INDEX	2
#define LEN_DATA	8
#define	LEN_CRC		2

#define	LEN_MSG_OBJ		(LEN_NETW + LEN_ID + LEN_INDEX + LEN_DATA + LEN_CRC)

#define	FLAG_RX_REMOTE_CTRL		0x02
#define	FLAG_RX_ALL				0xFF

	




typedef union u8{
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

typedef union u16{
	uint16_t Word;
	U8 Byte[2];
}U16;

typedef union u32{
	uint32_t DWord;
	U16 Word[2];
	U8 Byte[4];
}U32;

typedef union u64{
	uint64_t DDWord;
	U32 DWord[2];
	U16 Word[4];
	U8 Byte[8];
}U64;

//typedef union u64{
//	uint64_t DDWord;
//	U32 DWord[2];
//}U64;

#define	obj_ram_addr(obj_)		&obj_	
#define	objU8_byte(obj_v)		obj_v.Byte_
#define	objU_byte(obj_v, b)	    obj_v.Byte[b].Byte_
#define	objU_word(obj_v, b)		obj_v.Word[b].Word


typedef union tx_rx_frame{
	struct{
        uint8_t id_netw;
        uint8_t id_modul;
        uint16_t index;
        uint8_t data[LEN_DATA];
        uint16_t crc;
    }d_struct;

    uint8_t byte[LEN_NETW + LEN_ID + LEN_INDEX + LEN_DATA + LEN_CRC];
}TX_RX_FRAME;

//typedef	struct obj_struct{
//	uint16_t id;
//	
//	/* data 4 byte */
//	union {
//		
//		uint8_t data8b[4];
//		
//		struct{
//			uint16_t data16_L;
//			uint16_t data16_H;
//		}data16b;
//		
//		uint32_t	data32b;
//		
//	}data;
//	
//}OBJ_STRUCT;


typedef	struct obj_struct{
	uint16_t id;
	
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



uint8_t	Tx_OBJ_Data(OBJ_STRUCT *obj);	// Transfer Data Obj to USART
void Tx_OBJ(uint16_t *index);
uint8_t	Rx_OBJ_Data(void);				// Receive Data Obj from USART
uint8_t Check_CRC(TX_RX_FRAME *Rx_obj_c);
uint8_t Data_to_OBJ(TX_RX_FRAME *Rx_obj_d);

/* Rx from PC */
extern OBJ_STRUCT  objd_CTRL;
extern OBJ_STRUCT	objd_SetPORT_DIO;
extern OBJ_STRUCT	objd_SetPWM;
extern OBJ_STRUCT	objd_SetPID1_0;
extern OBJ_STRUCT	objd_SetPID1_1;
extern OBJ_STRUCT	objd_SetPID2_0;
extern OBJ_STRUCT	objd_SetPID2_1;

/* Tx to PC*/
extern OBJ_STRUCT	objd_VOLTAGE;
extern OBJ_STRUCT	objd_CURRENT;
extern OBJ_STRUCT	objd_CNT;
extern OBJ_STRUCT	objd_STATUS;
extern OBJ_STRUCT	objd_PWM;
extern OBJ_STRUCT	objd_fb_PORT_DIO;
extern OBJ_STRUCT	objd_PID1_0;
extern OBJ_STRUCT	objd_PID1_1;
extern OBJ_STRUCT	objd_PID2_0;
extern OBJ_STRUCT	objd_PID2_1;


typedef union{
	
	struct{
		struct{
			uint8_t bus_err : 1; // i2c bus error
			uint8_t rezerv	: 7; //--
			uint8_t i2c_err;	 // i2c reg error
			uint8_t rezerv2;	 //--
			uint8_t rezerv3;	 //--
		}error;
		struct{
			uint8_t rezerv0; //--
			uint8_t rezerv1; //--
			uint8_t rezerv2; //--
			uint8_t rezerv3; //--
		}run;
	}st;
	
	U8	st_byte[8];	
	uint64_t st_All;
}ST_CHARGER;

extern ST_CHARGER Status_Charger;

#endif
