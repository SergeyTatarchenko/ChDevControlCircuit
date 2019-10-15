/*-------------------------------------------------
                SOM global config 
-------------------------------------------------*/
#ifndef OBJ_CONFIG_H_
#define	OBJ_CONFIG_H_

#define RTOS_USAGE	TRUE
#define SOM_MODE	APP_MODE
#define DEBUG_MODE TRUE
#define REVISION	1

/*<hw snap>*/
#define NUM_OF_OBJ_ADC	8
#define NUM_OF_OBJ_INPUTS	8
#define NUM_OF_OBJ_OUTPUTS	8
#define NUM_OF_PWM	2

#define in_offset	1
#define out_offset	(NUM_OF_OBJ_INPUTS+1)
#define adc_offset	(out_offset + NUM_OF_OBJ_OUTPUTS+1)
#define pwm_offset	(adc_offset + NUM_OF_OBJ_ADC + 1)

typedef enum
{
	in_0  = in_offset,in_1,in_2,in_3,in_4,in_5,in_6,in_7,
	out_0 = out_offset,out_1,out_2,out_3,out_4,out_5,out_6,out_7,
	adc_0 = adc_offset,adc_1,adc_2,adc_3,adc_4,adc_5,adc_6,adc_7,
	pwm_0 = pwm_offset,pwm_1
}obj_hw;
/*</hw snap>*/
/*-----------------------------------------------
************communication channels***************
-----------------------------------------------*/
#define USART_COM_ENABLE	TRUE
#define CAN_COM_ENABLE    	FALSE
/*-----------------------------------------------
************SOM memory usage config**************
-----------------------------------------------*/

#if SOM_MODE == APP_MODE
	
	#define HARDWARE_OBJECT TRUE
	#define USART_DATA_FAST	TRUE
	#define OBJECT_TIMER	TRUE

	#define	num_of_all_obj		100
	#define MES_BUF_SIZE		20

	#if HARDWARE_OBJECT == TRUE
		#define NUM_OF_HWOBJ    50
	#endif
	#if OBJECT_TIMER == TRUE
		#define NUM_OF_TIMER    20
	#endif

	#ifndef TARGET
		#include "DEFAULT.h"
	#endif
#endif

#if RTOS_USAGE == TRUE
	#include "RTOS.h"
#endif

/*-------------------------------------------------
           !board special! (remove to other file)
-------------------------------------------------*/
#ifdef	TARGET
#if	TARGET == 0
	#include "TEST.h"
#elif TARGET == 72
	#include "B72.h"
#endif
#endif


#endif

