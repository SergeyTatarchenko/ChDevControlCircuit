#include "List_OBJ.h"
#include "OBJ_DATA.h"


uint8_t Task_rx_PID = 0x00;

/* Rx from PC */
OBJ_STRUCT  objd_CTRL;
OBJ_STRUCT	objd_SetPORT_DIO;
OBJ_STRUCT	objd_SetPWM;
OBJ_STRUCT	objd_SetPID1_0;
OBJ_STRUCT	objd_SetPID1_1;
OBJ_STRUCT	objd_SetPID2_0;
OBJ_STRUCT	objd_SetPID2_1;

/* Tx to PC*/
OBJ_STRUCT	objd_VOLTAGE;
OBJ_STRUCT	objd_CURRENT;
OBJ_STRUCT	objd_CNT;
OBJ_STRUCT	objd_STATUS;
OBJ_STRUCT	objd_PWM;
OBJ_STRUCT	objd_fb_PORT_DIO;
OBJ_STRUCT	objd_PID1_0;
OBJ_STRUCT	objd_PID1_1;
OBJ_STRUCT	objd_PID2_0;
OBJ_STRUCT	objd_PID2_1;

void Conf_INDEX_OBJ(void)
{
	objd_STATUS.id = IND_obj_STATUS;		// initialize ID object
	objd_CTRL.id = IND_obj_CTRL;			// initialize ID object
	
	objd_VOLTAGE.id = IND_obj_VOLTAGE;		// initialize ID object
	objd_CURRENT.id = IND_obj_CURRENT;		// initialize ID object
	objd_CNT.id = IND_obj_CNT;				// initialize ID object
	objd_PWM.id = IND_obj_PWM;				// initialize ID object
	objd_SetPWM.id = IND_obj_SetPWM;				// initialize ID object
	objd_SetPORT_DIO.id = IND_obj_SetPORT_DIO;			// initialize ID object
	objd_fb_PORT_DIO.id = IND_obj_fb_PORT_DIO;	// initialize ID object
	objd_SetPID1_0.id = IND_obj_SetPID1_0;			// initialize ID object
	objd_SetPID1_1.id = IND_obj_SetPID1_1;			// initialize ID object
	objd_SetPID2_0.id = IND_obj_SetPID2_0;			// initialize ID object
	objd_SetPID2_1.id = IND_obj_SetPID2_1;			// initialize ID object
	objd_PID1_0.id = IND_obj_PID1_0;			// initialize ID object
	objd_PID1_1.id = IND_obj_PID1_1;			// initialize ID object
	objd_PID2_0.id = IND_obj_PID2_0;			// initialize ID object
	objd_PID2_1.id = IND_obj_PID2_1;			// initialize ID object

}

/************************************************************************************/
/* 									 Tx_OBJ											*/
/************************************************************************************/
void Tx_OBJ(uint16_t *index)
{
	OBJ_STRUCT *n_obj;
	uint8_t permiss_send = 0;
	switch(*index)
		{
			case 0:
				n_obj = &objd_VOLTAGE;
				permiss_send = 1;
				break;
			case 1:
				n_obj = &objd_CURRENT;
				permiss_send = 1;
				break;
			case 2:
				n_obj = &objd_CNT;
				permiss_send = 1;
				break;
			case 3:
				n_obj = &objd_STATUS;
				permiss_send = 1;
				break;
			case 4:
				n_obj = &objd_PWM;
				permiss_send = 1;
				break;
			case 5:
				n_obj = &objd_fb_PORT_DIO;
				permiss_send = 1;
				break;
			case 6:
				n_obj = &objd_PID1_0;
				permiss_send = 1;
				break;
			case 7:
				n_obj = &objd_PID1_1;
				permiss_send = 1;
				break;
			case 8:
				n_obj = &objd_PID2_0;
				permiss_send = 1;
				break;
			case 9:
				n_obj = &objd_PID2_1;
				permiss_send = 1;
				break;
			default:
				*index = 0;
				break;
		}

		if(permiss_send)
		{
			Tx_OBJ_Data(n_obj);			// transfer object to UART
			
			Read_val_rx_OBJ();
		}
		
//		if(*index > IND_obj_fb_PORT_DIO)
//		{
//			*index = 0;
//		}
//		n_obj = &objd_VOLTAGE;
//		Tx_OBJ_Data(n_obj + *index);			// transfer object to UART
		
//		Tx_OBJ_Data(&objd_PWM);
//		Tx_OBJ_Data(&objd_CNT);
//		Tx_OBJ_Data(&objd_STATUS);
//		Tx_OBJ_Data(&objd_VOLTAGE);
//		Tx_OBJ_Data(&objd_CURRENT);
}


/************************************************************************************/
/* 									 Send to OBJ Rx data							*/
/************************************************************************************/
uint8_t Data_to_OBJ(TX_RX_FRAME *Rx_obj_d)
{
	uint8_t i = 0;
	uint8_t index_detect = 0;
	OBJ_STRUCT *obj;

	switch(Rx_obj_d->d_struct.index)
	{
		case IND_obj_CTRL:
		{
			obj = &objd_CTRL;
			index_detect = 1;
			break;
		}
		case IND_obj_SetPWM:
		{
			obj = &objd_SetPWM;
			Read_val_rx_obj_PWM();
			index_detect = 1;
			break;
		}
		case IND_obj_SetPORT_DIO:
		{
			obj = &objd_SetPORT_DIO;
			index_detect = 1;
			break;
		}
		case IND_obj_SetPID1_0:
		{
			obj = &objd_SetPID1_0;
			Task_rx_PID |= TASK_RX_PID1_0;
			index_detect = 1;
			break;
		}
		case IND_obj_SetPID1_1:
		{
			obj = &objd_SetPID1_1;
			Task_rx_PID |= TASK_RX_PID1_1;
			index_detect = 1;
			break;
		}
		case IND_obj_SetPID2_0:
		{
			obj = &objd_SetPID2_0;
			Task_rx_PID |= TASK_RX_PID2_0;
			index_detect = 1;
			break;
		}
		case IND_obj_SetPID2_1:
		{
			obj = &objd_SetPID2_1;
			Task_rx_PID |= TASK_RX_PID2_1;
			index_detect = 1;
			break;
		}
		default:
			index_detect = 0;
			break;
	}
	
	if(index_detect)
	{
		for(i = 0; i < LEN_DATA; i++)
		{
			obj->data.b8[i].Byte_ = Rx_obj_d->d_struct.data[i];
		}
	}
	return 1;
}

/****************************************************************************************************************************/
/*
*	Read_val_rx_OBJ()
*	Обработчик переноса полученных значений(уставок) из объектов в переменные
*/
/****************************************************************************************************************************/
void Read_val_rx_OBJ(void)
{
	Read_val_rx_obj_PID();
}

/****************************************************************************************************************************/
/*
*	Read_val_rx_obj_PID()
*	Обработчик принятых уставок для ПИД регуляторов 
*/
/****************************************************************************************************************************/
void Read_val_rx_obj_PID(void)
{
	if(Task_rx_PID & TASK_RX_PID1_0)
	{
		Task_rx_PID &= ~TASK_RX_PID1_0;
		pid_inductance.Kp = (float)objd_SetPID1_0.data.d32b[0]/10000.0;
		pid_inductance.Ki = (float)objd_SetPID1_0.data.d32b[1]/10000.0;
		
	}else if(Task_rx_PID & TASK_RX_PID1_1)
	{
		Task_rx_PID &= ~TASK_RX_PID1_1;
		pid_inductance.Kd = (float)objd_SetPID1_1.data.d32b[0]/10000.0;
		
	}else if(Task_rx_PID & TASK_RX_PID2_0)
	{
		Task_rx_PID &= ~TASK_RX_PID2_0;
		pid_current_out.Kp = (float)objd_SetPID2_0.data.d32b[0]/10000.0;
		pid_current_out.Ki = (float)objd_SetPID2_0.data.d32b[1]/10000.0;
	}else if(Task_rx_PID & TASK_RX_PID2_1)
	{
		Task_rx_PID &= ~TASK_RX_PID2_1;
		pid_current_out.Kd = (float)objd_SetPID2_1.data.d32b[0]/10000.0;
	}
}

/****************************************************************************************************************************/
/*
*	Read_val_rx_obj_PWM()
*	Обработчик принятых уставок для PWM 
*/
/****************************************************************************************************************************/
void Read_val_rx_obj_PWM(void)
{
	
}
