#ifndef LIST_OBJ_H_
#define LIST_OBJ_H_

#include	"OBJ_DATA.h"

#define		TASK_RX_PID1_0	0x01
#define		TASK_RX_PID1_1	0x02
#define		TASK_RX_PID2_0	0x04
#define		TASK_RX_PID2_1	0x08

void Conf_INDEX_OBJ(void);

void Read_val_rx_OBJ(void);
void Read_val_rx_obj_PID(void);
void Read_val_rx_obj_PWM(void);

#endif
