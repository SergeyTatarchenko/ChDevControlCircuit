/*************************************************
* File Name          : global.h
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : header for global parameters and
sending messages of charging device 		
*************************************************/
/*----------- global tupedef---------------------*/

/*state of all io port */
#pragma pack(push,1)
typedef struct{
	union{
		uint8_t PortA_All;
		struct{
			unsigned A0:1;
			unsigned A1:1;
			unsigned A2:1;
			unsigned A3:1;
			unsigned A4:1;
			unsigned A5:1;
			unsigned A6:1;
			unsigned A7:1;
			} bit;
		} PortA_Byte;	
	union{
		uint8_t PortB;
		struct{
			unsigned B0:1;
			unsigned B1:1;
			unsigned B2:1;
			unsigned B3:1;
			unsigned B4:1;
			unsigned B5:1;
			unsigned B6:1;
			unsigned B7:1;
			} bit;
		} PortB_Byte_All;		
}PortState_REGISTR;
#pragma pack(pop)

/*----------- global variables-------------------*/
extern PortState_REGISTR IO_STATE;
/*----------- global define----------------------*/
#define	IO_A 	IO_STATE.PortA_Byte.PortA_All 
#define IO_B	IO_STATE.PortB_Byte.PortB_All 















