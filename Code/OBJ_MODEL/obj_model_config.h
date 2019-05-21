#ifndef OBJ_CONFIG_H_
#define	OBJ_CONFIG_H_

#define TRUE    1
#define FALSE   0

#define USART_MODE  0
#define CAN_MODE    1

#define DEBUG_MODE	TRUE

#define HARDWARE_OBJECT TRUE
#define USART_DATA_FAST	TRUE

#define	num_of_all_obj		  255

#define	ID_NETWORK			0x01
#define	ID_DEVICE			0x72
#define ID_REMOTE_CNTRL		0x02
#define	FLAG_RX_ALL			0xFF

#define MES_BUF_SIZE		20


#ifdef HARDWARE_OBJECT
    #define NUM_OF_HWOBJ    20
#endif
/*-------------------------------------------------
                  FreeRTOS 
-------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h" 
/*-------------------------------------------------
                !board special!
-------------------------------------------------*/
#include "global.h"
/*     network and board description             */



#endif

