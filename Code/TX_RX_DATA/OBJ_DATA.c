#include "OBJ_DATA.h"

/*----------- global variables-------------------*/
uint8_t obj_mem_area[sizeof(OBJ_STRUCT)*num_of_all_obj];
OBJ_STRUCT *objDefault;
void ((*obj_handlers[num_of_all_obj+1]))(OBJ_STRUCT*);

xSemaphoreHandle xMutex_USART_BUSY;
xQueueHandle usart_receive_buffer;
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
	OBJ_STRUCT *obj;
	
	/*create mutex for correct usart transmit*/
	xMutex_USART_BUSY = xSemaphoreCreateMutex();
	
	usart_receive_buffer = xQueueCreate(MES_BUF_SIZE,sizeof(TX_RX_FRAME));
	
	/* object memory allocation*/
	memset(obj_mem_area,0,sizeof(OBJ_STRUCT)*num_of_all_obj);
	objDefault =(OBJ_STRUCT*)obj_mem_area;
	for(int counter = 0;counter <= num_of_all_obj;counter++){
		obj = objDefault + counter;
		obj->id[0] = counter;	
	}
	/* object handler mapping*/
	obj_snap();
}

/* object event, call object handler and call update function */
void OBJ_Event(int obj_id){
	
	OBJ_Upd(this_obj(obj_id));	
	obj_handlers[obj_id](this_obj(obj_id));
}

/*           update this object             */
void	OBJ_Upd(OBJ_STRUCT *obj){
	
	uint8_t *pointer;
	TX_RX_FRAME message;
	TX_RX_FRAME *message_pointer;
	uint16_t _CRC_ = 0;
	message_pointer =&message;
	
	/*create default message with obj info*/
	message_pointer->d_struct.id_netw = ID_NETWORK;
	message_pointer->d_struct.id_modul = MY_ID;
	
	pointer = (uint8_t*)message_pointer;
	pointer += (sizeof(message.d_struct.id_netw)+sizeof(message.d_struct.id_modul));
	memcpy(pointer,obj,sizeof(OBJ_STRUCT));
	
	/* Calc check summ */
	for(int i = 0; i < LEN_MSG_OBJ - LEN_CRC; i++)
	{
		_CRC_ += message_pointer->byte[i];
	}
	message_pointer->d_struct.crc = _CRC_;
	
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
void Rx_OBJ_Data(TX_RX_FRAME *mes){
	
	int id;
	OBJ_STRUCT *obj;
	uint8_t *pointer;
	id = mes->d_struct.index[0];
	obj = objDefault + id;
	
	/*if it is a control object*/	
	if( mes->d_struct.index[1]& (IND_obj_CAS|IND_obj_CWS)){
			pointer = (uint8_t*)mes;
			pointer += (sizeof(mes->d_struct.id_netw)+sizeof(mes->d_struct.id_modul));
			memcpy(obj,pointer,sizeof(OBJ_STRUCT));
			obj_handlers[id](this_obj(id));
			OBJ_Upd(this_obj(id));
	}
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

