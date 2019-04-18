/*************************************************
* File Name          : OBJ_DATA.c
* Author             : Tatarchenko S.
* Version            : v 1.1
* Description        : simple obj model BKM
*************************************************/
#include "OBJ_MODEL.h"
/*----------- global variables-------------------*/

static uint8_t obj_mem_area[sizeof(OBJ_STRUCT)*num_of_all_obj];
OBJ_STRUCT *objDefault;
BOARD_STATE	board_state;
void ((*obj_handlers[num_of_all_obj+1]))(OBJ_STRUCT*);

OBJ_STRUCT *HW_OBJ[NUM_OF_HWOBJ];
int HW_OBJ_snap[NUM_OF_HWOBJ];
/*-----------------------------------------------*/
void USART1_IRQHandler(){
	uint8_t buff;
	
	if(USART1->SR &= USART_SR_RXNE){
		
		buff = USART1->DR;
		
		switch(buff){
			/**/
			case ID_NETWORK:
				if(usart_irq_counter == 0){
					usart_data_receive_array[usart_irq_counter] = buff;
					usart_irq_counter++;
				}else{
					if((usart_irq_counter < LEN_USART_MSG_OBJ) && (usart_irq_counter > (LEN_HEAD_SIZE -1))){
						/**/
						usart_data_receive_array[usart_irq_counter] = buff;
						if(usart_irq_counter == (LEN_USART_MSG_OBJ)){
							break;
						}
						usart_irq_counter++;
					}else{
						usart_irq_counter = 0;
					}
				}
				break;
			/**/	
			case ID_REMOTE_CNTRL:
				if(usart_irq_counter == 1){
					usart_data_receive_array[usart_irq_counter] = buff;
					usart_irq_counter++;
				}else{
					if((usart_irq_counter < LEN_USART_MSG_OBJ) && (usart_irq_counter > (LEN_HEAD_SIZE -1))){
						usart_data_receive_array[usart_irq_counter] = buff;
						if(usart_irq_counter == (LEN_USART_MSG_OBJ)){
							break;
						}
						usart_irq_counter++;
					}else{
						usart_irq_counter = 0;
					}
				}
				break;
			/**/	
			default:
				if((usart_irq_counter < LEN_USART_MSG_OBJ) && (usart_irq_counter > (LEN_HEAD_SIZE -1))){
					usart_data_receive_array[usart_irq_counter] = buff;
					if(usart_irq_counter == (LEN_USART_MSG_OBJ)){
							break;
						}
						usart_irq_counter++;
					}else{
						usart_irq_counter = 0;
					}
				break;
		}
		
		if(usart_irq_counter == (LEN_USART_MSG_OBJ)){
			xQueueSendFromISR(usart_receive_buffer,usart_data_receive_array,0);
			usart_irq_counter = 0;	
		}	
	}
}

/*-----------------------------------------------*/
/*init obj model*/
void OBJ_Init(){
	
	OBJ_STRUCT *obj;

	/*create mutex for correct usart transmit*/
	xMutex_USART_BUSY = xSemaphoreCreateMutex();
	usart_receive_buffer = xQueueCreate(MES_BUF_SIZE,sizeof(USART_FRAME));
	
	/* object memory allocation*/
	memset(obj_mem_area,0,sizeof(OBJ_STRUCT)*num_of_all_obj);
	objDefault =(OBJ_STRUCT*)obj_mem_area;
	
	for(int counter = 0;counter <= num_of_all_obj;counter++){
		obj = objDefault + counter;
		obj->id[0] = counter;	
	}
	
	for(int counter = 0;counter <= num_of_all_obj;counter++){
		obj_handlers[counter]= Dummy_Handler;
	}
	#ifdef HARDWARE_OBLECT
		for(int counter = 0;counter <= NUM_OF_HWOBJ;counter++){
		HW_OBJ[counter] = objDefault;
	}
	#endif
	/* object create and handler mapping*/
	obj_snap();
}

/*create object, return pointer to obj */
OBJ_STRUCT* Obj_Create(int obj_id, int obj_type ){
	
	OBJ_STRUCT* obj;
	obj = objDefault + obj_id;
	obj->id[1] = obj_type;
	return obj;
}

/*set state with update*/
void OBJ_SetState(int obj_id,int state){
	if(state>1){
		return;
	}
	if(this_obj(obj_id)->obj_state != state){
		this_obj(obj_id)->obj_state = state;
		obj_handlers[obj_id](this_obj(obj_id));
		OBJ_Upd_USART(this_obj(obj_id));
	}
}
void HWOBJ_event(OBJ_STRUCT* obj,int obj_id){
	
	/*output event*/
	if((obj->hardware_adress == out_0)||(obj->hardware_adress == out_1)||(obj->hardware_adress == out_2)||
	   (obj->hardware_adress == out_3)||(obj->hardware_adress == out_4)||(obj->hardware_adress == out_5)||
		(obj->hardware_adress == out_6)){
			Set_IO_State((int)(obj->hardware_adress - out_offset),(int)obj->obj_state);
	}
	OBJ_Event(obj_id);	
}

/* object event, call object handler and call update function, if event = 1 */
void OBJ_Event(int obj_id){
	
	obj_handlers[obj_id](this_obj(obj_id));
	
	/*feedback*/
	if(this_obj(obj_id)->obj_event == 1){
		this_obj(obj_id)->obj_event = 0;
		OBJ_Upd_USART(this_obj(obj_id));
	}	
}

/*           update this object             */
void	OBJ_Upd_USART(OBJ_STRUCT *obj){

		uint8_t *pointer;
		USART_FRAME message;
		USART_FRAME *message_pointer;
		uint16_t _CRC_ = 0;
		message_pointer =&message;
	
		/*create default message with obj info*/
		message_pointer->d_struct.id_netw = ID_NETWORK;
		message_pointer->d_struct.id_modul = ID_DEVICE;
	
		pointer = (uint8_t*)message_pointer;
		pointer += (sizeof(message.d_struct.id_netw)+sizeof(message.d_struct.id_modul));
		memcpy(pointer,obj,sizeof(OBJ_STRUCT));
	
		/* Calc check summ */
		for(int i = 0; i < LEN_USART_MSG_OBJ - LEN_CRC; i++){
			_CRC_ += message_pointer->byte[i];
		}
		message_pointer->d_struct.crc = _CRC_;
	
		/*mutex return in dma transfer complete interrupt*/
		xSemaphoreTake(xMutex_USART_BUSY,portMAX_DELAY);
		send_usart_message((uint8_t*)message_pointer,sizeof(USART_FRAME));	// transfer data to usart

	/*message delay for corrent receive */
	vTaskDelay(25);
}

/*             update all obj                */
void Upd_All_OBJ_USART(){
	
	for(int counter = 0; counter < num_of_all_obj; counter ++){
		if(this_obj(counter)->id[1]!=0){
			OBJ_Upd_USART(this_obj(counter));
		}
	}
}

/* Receive Data Obj */
void Rx_OBJ_Data(USART_FRAME *mes){
	
	int id;
	int i;
	uint8_t type;
	uint16_t _CRC = 0;
	OBJ_STRUCT *obj;
	uint8_t *pointer;
	
	/*id of rec object*/
	id = mes->d_struct.index[0];
	/*type of rec object*/
	type = mes->d_struct.index[1];
	
	obj = objDefault + id;
	
	for(i = 0; i < (LEN_USART_MSG_OBJ - LEN_CRC); i++)
	{
		_CRC += mes->byte[i];
	}
	
	if(_CRC != mes->d_struct.crc){
		/*error crc do not match*/
		return;
	}
	
	/*board control object*/
	if(id == obj_STATUS){
		this_obj(obj_STATUS)->status_field = mes->d_struct.data[0];
		OBJ_Event(obj_STATUS);
		return;
	}
	/*receive data (obj type 4) */
	if((type == IND_obj_COM) && (board_state.bit.power == 1)){
		/*take new object image*/
		pointer = (uint8_t*)mes;
		pointer += (sizeof(mes->d_struct.id_netw)+sizeof(mes->d_struct.id_modul));
		memcpy(obj,pointer,sizeof(OBJ_STRUCT));
		OBJ_Event(id);
		return;		
	}
	/*object event*/
	if(mes->d_struct.data[0] & event_mask){
		/*if it is a control object*/	
		if((type == obj->id[1])&&(type&IND_obj_CAS)&& (board_state.bit.power == 1)){
		/*take new object image*/
		pointer = (uint8_t*)mes;
		pointer += (sizeof(mes->d_struct.id_netw)+sizeof(mes->d_struct.id_modul));
		memcpy(obj,pointer,sizeof(OBJ_STRUCT));
		/*event bit call object handler*/
		
		if(obj->obj_hardware == 1){
			HWOBJ_event(this_obj(id),id);
		}else{
			OBJ_Event(id);
		}
		/*call obj handler,change event bit on feedback*/
		
		}	
	}
}

