/*************************************************
* File Name          : user_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : all code here
*************************************************/
#include "user_tasks.h"
/*************************************************
 Initial configuration and start other tasks
*************************************************/
void StartInit(void *pvParameters){
	
	/*init port for led on PC13*/
	LedInit();
	/*init channel 1 DMA for ADC*/
	DMA_ADC1_Setup();
	/*internal ADC init*/
	ADC_Init();
	/* Init internal timer as PWM */
	PWM_Init();
	/*init hardware I2C module*/
	I2C2Init();
	/*first config for MCP23017 */
	MCP23x17_Init();
	
	
	/*usart init*/
	usart_init();
	
	/*start other tasks*/
	
	/*test blink*/
	xTaskCreate(vBlinker, "blink", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	
	PWM_ON;
	PWMSetValue(4500);
	
	vTaskDelete(NULL); /*delete task*/
	
}

/*************************************************
blink via I2C
*************************************************/
void vBlinker (void *pvParameters){
	for(;;){
		MCP23x17_SetOutPin(0,1);		
		vTaskDelay(200);			
		MCP23x17_SetOutPin(0,0);	
		vTaskDelay(200);			
	}
}

/*************************************************
 hardware errors handler
*************************************************/
void vErrorHandler(void *pvParameters){
	
}
/*************************************************
Init blue LED on board (PC13 pin) 
*************************************************/
void LedInit(){
	/* LED on PC13*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~(GPIO_CRH_MODE13|GPIO_CRH_CNF13);	
	GPIOC->CRH |= (GPIO_CRH_MODE13_0  | GPIO_CRH_MODE13_1);	
}

