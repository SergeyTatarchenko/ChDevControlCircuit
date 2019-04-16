#ifndef OBJ_CONFIG_H_
#define	OBJ_CONFIG_H_

#define TRUE    1
#define FALSE   0

#define USART_MODE  0
#define CAN_MODE    1

#define HARDWARE_OBLECT TRUE
#define	num_of_all_obj		  255

/*-------------------------------------------------
                  FreeRTOS 
-------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h" 
/*-------------------------------------------------

-------------------------------------------------*/
#include "global.h"
/*     network and board description             */

#define	ID_NETWORK			0x01
#define	ID_DEVICE			0x72
#define ID_REMOTE_CNTRL		0x02
#define	FLAG_RX_ALL			0xFF

#define MES_BUF_SIZE		20


#ifdef HARDWARE_OBLECT
    #define NUM_OF_HWOBJ    20
#endif

#endif

