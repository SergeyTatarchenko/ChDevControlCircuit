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
	/*test message*/
	uint8_t buff[USART1_DEFAULT_BUF_SIZE] = {"test message\r\n"};
	
	for(;;){
		adc_calc_value();
		
		send_usart_message(buff,(uint32_t)USART1_DEFAULT_BUF_SIZE);
		vTaskDelay(1000);
	}
}


/*************************************************

*************************************************/
void vTask_Transfer_Data(void *pvParameters)
{
	uint16_t index = 0;
	
	for(;;){
		Tx_OBJ(&index);
		index++;
		objd_CNT.data.d64b++;
		vTaskDelay(30);
	}
}


/*************************************************

*************************************************/
void vTask_Receive_Data(void *pvParameters)
{
	for(;;){
		Rx_OBJ_Data();
		vTaskDelay(10);
	}
}

/*************************************************

*************************************************/
void vTask_Handler_Data(void *pvParameters)
{
	/* Init parameters for pid cintroller */
	pid_inductance.Kp = 0.0187;
	pid_inductance.Ki = 400;
	pid_inductance.Kd = 0.0;
	
	pid_current_out.Kp = 0.0187;
	pid_current_out.Ki = 400;
	pid_current_out.Kd = 0.0;
	
	for(;;){
		
		/* PID */
		objd_PID1_0.data.d32b[0] = (uint32_t)(pid_inductance.Kp * 10000);
		objd_PID1_0.data.d32b[1] = (uint32_t)(pid_inductance.Ki * 10000);
		objd_PID1_1.data.d32b[0] = (uint32_t)(pid_inductance.Kd * 10000);

		objd_PID2_0.data.d32b[0] = (uint32_t)(pid_current_out.Kp * 10000);
		objd_PID2_0.data.d32b[1] = (uint32_t)(pid_current_out.Ki * 10000);
		objd_PID2_1.data.d32b[0] = (uint32_t)(pid_current_out.Kd * 10000);
		
		/*STATUS*/
		Status_Charger.st.error.bus_err = bus_error;
		Status_Charger.st.error.i2c_err = I2C_ERROR;
		objd_STATUS.data.d64b = Status_Charger.st_All;
		
		/* PORT_IO */
		objd_fb_PORT_DIO.data.d8b[0] = IO_STATE.OUTPUTS;	// outputs
		objd_fb_PORT_DIO.data.d8b[1] = IO_STATE.INPUTS;	// inputs
				
		/* Voltage AIN */
		objd_VOLTAGE.data.d16b[0] = AIN_State.AIN1;
		objd_VOLTAGE.data.d16b[1] = AIN_State.AIN2;
		objd_VOLTAGE.data.d16b[2] = AIN_State.AIN3;
		objd_VOLTAGE.data.d16b[3] = AIN_State.AIN4;
		
		/* PWM */
		objd_PWM.data.d16b[0] = TIM3->CCR3;
		objd_PWM.data.d16b[1] = TIM3->CCR4;
		
		vTaskDelay(1);
	}
}
