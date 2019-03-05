#include "OBJ_DATA.h"


/*----------- global variables-------------------*/
uint8_t obj_mem_area[sizeof(OBJ_STRUCT)*num_of_all_obj];
OBJ_STRUCT *objDefault;

xSemaphoreHandle xMutex_USART_BUSY;
/*-----------------------------------------------*/


/*-----------------------------------------------*/
uint8_t	FLAG_RECEIVE;
//TX_RX_FRAME	Rx_obj;
volatile uint8_t buff_rx[LEN_MSG_OBJ];
uint8_t st_rx;
//static uint8_t n_byte = 0;
/*-----------------------------------------------*/



/*init obj model*/
void OBJ_Init(){
	
	/*create mutex for correct usart transmit*/
	xMutex_USART_BUSY = xSemaphoreCreateMutex();
	
	objDefault =(OBJ_STRUCT*)obj_mem_area;
	OBJ_create(objDefault);
	
}

void OBJ_event(OBJ_STRUCT *obj,void(*obj_func)(void)){
	obj_func();
	OBJ_Upd(obj);	
}

/*           update this obj             */
void	OBJ_Upd(OBJ_STRUCT *obj){
	
	uint8_t *pointer;
	uint8_t buff[sizeof(TX_RX_FRAME)];
	TX_RX_FRAME message;
	TX_RX_FRAME *message_pointer;
	uint16_t _CRC_ = 0;
	
	pointer = buff;
	/*create default message with obj info*/
	message.d_struct.id_netw = ID_NETWORK;
	message.d_struct.id_modul = MY_ID;
	pointer += (sizeof(message.d_struct.id_netw)+sizeof(message.d_struct.id_modul));
	memcpy(pointer,obj,sizeof(OBJ_STRUCT));
	
	/* Calc check summ */
	for(int i = 0; i < LEN_MSG_OBJ - LEN_CRC; i++)
	{
		_CRC_ += buff[i];
	}
	message.d_struct.crc = _CRC_;
	
	message_pointer =&message;
	
	/*mutex return in dma transfer complete interrupt*/
	xSemaphoreTake(xMutex_USART_BUSY,portMAX_DELAY);
	send_usart_message((uint8_t*)message_pointer,sizeof(TX_RX_FRAME));	// transfer data to usart
}

/*             update all obj                */
void Upd_All_OBJ(){

		for(int counter = 0; counter < num_of_all_obj; counter ++){
		OBJ_Upd(this_obj(counter));
	}

}


/* Receive Data Obj */
uint8_t	Rx_OBJ_Data(void)
{
	//uint8_t buff[LEN_MSG_OBJ];
	TX_RX_FRAME	Rx_obj;
	uint8_t i = 0;

	if(FLAG_RECEIVE & FLAG_RX_REMOTE_CTRL)
	{
		FLAG_RECEIVE &= ~FLAG_RX_REMOTE_CTRL;
		
		/* Read byte index, data, crc */
		for(i = 0; i < LEN_MSG_OBJ; i++)
		{
			Rx_obj.byte[i] = buff_rx[i];
		}
		
		Data_to_OBJ(&Rx_obj);
		
		/* check crc*/
		if(Check_CRC(&Rx_obj))
		{
			/* check index */
			Data_to_OBJ(&Rx_obj);
			return 1;
		}
	}
		
	return 0;
}



uint8_t Check_CRC(TX_RX_FRAME *Rx_obj_c)
{
	uint16_t calc_CRC = 0x0000;
	uint8_t i = 0;

	for(i = 0; i < (LEN_MSG_OBJ - LEN_CRC); i++)
	{
		calc_CRC += Rx_obj_c->byte[i];
	}
	
	return (Rx_obj_c->d_struct.crc == calc_CRC)? 1 : 0;
}

