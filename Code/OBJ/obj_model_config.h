/*-------------------------------------------------
                SOM global config 
-------------------------------------------------*/
#ifndef OBJ_CONFIG_H_
#define	OBJ_CONFIG_H_

#define REVISION	1

#define USE_HWOBJ		TRUE
#define USE_TIMERS		TRUE
#define USE_SERIAL_PORT	TRUE
#define USE_RTOS		TRUE

#define USE_CAN_BUS		TRUE

#define SOM_MODE	APP_MODE

/*<hw snap/>*/
#define NUM_OF_OBJ_ADC	8
#define NUM_OF_OBJ_INPUTS	8
#define NUM_OF_OBJ_OUTPUTS	8
#define NUM_OF_PWM	2

#define in_offset	0
#define out_offset	(in_offset +  NUM_OF_OBJ_INPUTS)
#define adc_offset	(out_offset + NUM_OF_OBJ_OUTPUTS)
#define pwm_offset	(adc_offset + NUM_OF_OBJ_ADC)

typedef enum
{
	in_0  = in_offset,in_1,in_2,in_3,in_4,in_5,in_6,in_7,
	out_0 = out_offset,out_1,out_2,out_3,out_4,out_5,out_6,out_7,
	adc_0 = adc_offset,adc_1,adc_2,adc_3,adc_4,adc_5,adc_6,adc_7,
	pwm_0 = pwm_offset,pwm_1
}OBJ_HW;
/*</hw snap>*/
/*-----------------------------------------------
************SOM memory usage config**************
-----------------------------------------------*/
#if SOM_MODE == APP_MODE

#define	num_of_all_obj		100
#define MES_BUF_SIZE		20
#define NUM_OF_HWOBJ		50
#define NUM_OF_TIMER		20

#define CAN_MSG_SIZE		20

#ifndef TARGET
#include "DEFAULT.h"
#endif

#ifdef USE_RTOS
#include "RTOS.h"
#endif

#endif

#ifdef	TARGET
#if	TARGET == 0
	#include "TEST.h"
#elif TARGET == 72
	#include "B72.h"
#endif
#endif


#endif

