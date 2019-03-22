#include "OBJ_DATA.h"

/*----------- global variables-------------------*/
uint8_t obj_mem_area[sizeof(OBJ_STRUCT)*num_of_all_obj];
OBJ_STRUCT *objDefault;
void ((*obj_handlers[num_of_all_obj+1]))(OBJ_STRUCT*);

/* data array for usart obj receive */
uint8_t USART1_receive_array[LEN_MSG_OBJ];

/* data array for usart obj transfer */
uint8_t USART1_transmit_array[LEN_MSG_OBJ];

uint8_t usart_irq_counter = 0;

xSemaphoreHandle xMutex_USART_BUSY;
xQueueHandle usart_receive_buffer;

/*-----------------------------------------------*/
void USART1_IRQHandler(){
	uint8_t buff;
	
	if(USART1->SR &= USART_SR_RXNE){
		
		buff = USART1->DR;
		
		switch(buff){
			/**/
			case ID_NETWORK:
				if(usart_irq_counter == 0){
					USART1_receive_array[usart_irq_counter] = buff;
					usart_irq_counter++;
				}else{
					if((usart_irq_counter < LEN_MSG_OBJ) && (usart_irq_counter > (LEN_HEAD_SIZE -1))){
						/**/
						USART1_receive_array[usart_irq_counter] = buff;
						if(usart_irq_counter == (LEN_MSG_OBJ)){
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
					USART1_receive_array[usart_irq_counter] = buff;
					usart_irq_counter++;
				}else{
					if((usart_irq_counter < LEN_MSG_OBJ) && (usart_irq_counter > (LEN_HEAD_SIZE -1))){
						USART1_receive_array[usart_irq_counter] = buff;
						if(usart_irq_counter == (LEN_MSG_OBJ)){
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
				if((usart_irq_counter < LEN_MSG_OBJ) && (usart_irq_counter > (LEN_HEAD_SIZE -1))){
					USART1_receive_array[usart_irq_counter] = buff;
					if(usart_irq_counter == (LEN_MSG_OBJ)){
							break;
						}
						usart_irq_counter++;
					}else{
						usart_irq_counter = 0;
					}
				break;
		}
		
		if(usart_irq_counter == (LEN_MSG_OBJ)){
			xQueueSendFromISR(usart_receive_buffer,USART1_receive_array,0);
			usart_irq_counter = 0;	
		}	
	}
}

/*-----------------------------------------------*/

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
	
	for(int counter = 0;counter <= num_of_all_obj;counter++){
		obj_handlers[counter]= Dummy_Handler;
	}
	/* object create and handler mapping*/
	obj_snap();
	Obj_MCP23017_snap();
}

/*create object, return pointer to obj */
OBJ_STRUCT* Obj_Create(int obj_id, int obj_type ){
	
	OBJ_STRUCT* obj;
	obj = objDefault + obj_id;
	obj->id[1] = obj_type;
	return obj;
}
/*create hardware obj*/
void Obj_MCP23017_snap(){
	int counter = 0;
	/*inputs*/
	/*create obj for all inputs*/
	while(counter < sizeof(IO_Pointer->INPUTS)*8){
		if(this_obj(IND_obj_IN0 + counter)->id[1]!=0){
			this_obj(IND_obj_IN0 + counter)->obj_hardware =1;
		}
		counter++;
	}
}
/*update data from mcp2017 snap with obj, call handler if state change */
void Obj_MCP23017_upd(){
	uint8_t port_state;
	int counter = 0;
	/*inputs*/
	port_state = IO_Pointer->INPUTS;
	while(counter < sizeof(IO_Pointer->INPUTS)*8){
		if((this_obj(IND_obj_IN0 + counter)->id[1]!=0) && (this_obj(IND_obj_IN0 + counter)->obj_hardware == 1)){
			if(this_obj(IND_obj_IN0 + counter)->obj_state != (port_state&1) ){
				this_obj(IND_obj_IN0 + counter)->obj_state = port_state&1;
				OBJ_Event(IND_obj_IN0 + counter);
			}
		}
		port_state = port_state>>1;
		counter++;
	}
}

/*set state with update*/
void OBJ_SetState(int obj,int state){
	/*change hardware state*/
	
	if(this_obj(obj)->obj_hardware == 1){
		xSemaphoreTake(xMutex_BUS_BUSY,portMAX_DELAY);	
		/*add mcp23017 set state function */
		xSemaphoreGive(xMutex_BUS_BUSY);		
	}
	
	if(this_obj(obj)->obj_state != state){
		this_obj(obj)->obj_state = state;
		obj_handlers[obj](this_obj(obj));
		OBJ_Upd(this_obj(obj));		
	}
}


/* object event, call object handler and call update function, if event = 1 */
void OBJ_Event(int obj_id){
	
	obj_handlers[obj_id](this_obj(obj_id));
	
	/*feedback*/
	if(this_obj(obj_id)->obj_event == 1){
		this_obj(obj_id)->obj_event = 0;
		OBJ_Upd(this_obj(obj_id));
	}	
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
	message_pointer->d_struct.id_modul = ID_DEVICE;
	
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
	
	/*message delay for corrent receive */
	vTaskDelay(25);
}

/*             update all obj                */
void Upd_All_OBJ(){
	for(int counter = 0; counter < num_of_all_obj; counter ++){
		if(this_obj(counter)->id[1]!=0){
			OBJ_Upd(this_obj(counter));
		}
	}
}

/* Receive Data Obj */
void Rx_OBJ_Data(TX_RX_FRAME *mes){
	
	int id;
	int i;
	uint8_t type;
	uint16_t _CRC = 0;
	OBJ_STRUCT *obj;
	uint8_t *pointer;
	
	id = mes->d_struct.index[0];
	type = mes->d_struct.index[1];
	obj = objDefault + id;
	
	for(i = 0; i < (LEN_MSG_OBJ - LEN_CRC); i++)
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
	/*if it is a control object*/	
	if((type == obj->id[1])&& power_on){
		pointer = (uint8_t*)mes;
		pointer += (sizeof(mes->d_struct.id_netw)+sizeof(mes->d_struct.id_modul));
		memcpy(obj,pointer,sizeof(OBJ_STRUCT));
		
		if(obj->obj_event == 1){
			/*call obj handler,change event bit on feedback*/
			OBJ_Event(id);
			
			if(obj->obj_hardware == 1){
				/*hardware event*/
			}
		}
		else{
			/*feedback*/
	//		OBJ_Upd(this_obj(id));
		}
	}	
}

