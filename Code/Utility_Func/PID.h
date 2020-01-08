#ifndef _PID_H
#define	_PID_H

#include "global.h"
#include "FreeRTOS.h"

typedef struct K_pid{
	float Kp;
	float Ki;
	float Kd;
	//float setpoint_val;
	//float feedback;
	uint16_t setpoint_val;
	uint16_t feedback;
	
	/* Range value out*/
	uint16_t out_Max;
	uint16_t out_Min;
	
    int32_t iSum;
    int32_t last_iSum;
	
	int16_t last_err;	// init last_err = ErrDiff
	float last_set_ctrl_val;
	
}K_PID;

extern K_PID pid_inductance;
extern K_PID pid_current_out;


int16_t PID_controller(K_PID *val);
int pid_regulator(K_PID *val,uint8_t reset);

#endif
