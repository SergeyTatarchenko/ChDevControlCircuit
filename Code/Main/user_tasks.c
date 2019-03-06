/*************************************************
* File Name          : user_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : all code here
**************************************************/
#include "user_tasks.h"
/*************************************************/
/*************************************************
1000 ms timer
*************************************************/	

void vTask_1000ms(void *pvParameters){	
		
	for(;;){
		
		
		this_obj(IND_obj_CTRL)->obj_field.d8b[0] = 0xff;
		this_obj(IND_obj_PID2_1)->obj_field.d8b[0] = 0xAA;
		
		/*test obj upd*/
		OBJ_Upd(this_obj(IND_obj_CTRL));	
		OBJ_Upd(this_obj(IND_obj_PID2_1));
		
		/*test obj event*/
		OBJ_Event(IND_obj_SetPWM);
		
		vTaskDelay(1000);
	}
}
/*************************************************

*************************************************/
void vTask_Handler_Data(void *pvParameters){
	
	TX_RX_FRAME rx_buffer;
	
	/* Init parameters for pid cintroller */
	pid_inductance.Kp = 0.0187;
	pid_inductance.Ki = 400;
	pid_inductance.Kd = 0.0;
	
	pid_current_out.Kp = 0.0187;
	pid_current_out.Ki = 400;
	pid_current_out.Kd = 0.0;
	
	for(;;){
		xQueueReceive(usart_receive_buffer,&rx_buffer,portMAX_DELAY);
		Rx_OBJ_Data(&rx_buffer);	
		vTaskDelay(100);
	}
}
