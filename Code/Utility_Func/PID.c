#include "PID.h"

K_PID pid_inductance;
K_PID pid_current_out;

uint16_t PID_controller(K_PID *val)
{
	//float set_ctrl_val = 0.0;
	uint16_t set_ctrl_val = 0;
	int16_t ErrDiff = 0;
	float P_term = 0.0;
	float I_term = 0.0;
	float D_term = 0.0;
	
	/* Derivate error */
	ErrDiff = val->setpoint_val - val->feedback;
	//if(ErrDiff > 2045) ErrDiff = 2045;
	//if(ErrDiff < -32000) ErrDiff = -32000;
	
	/* Proportional term */
	P_term = ErrDiff * val->Kp;
	
	/* Integral term */
	//if((last_set_ctrl_val != 0) && (last_set_ctrl_val <= 1023) && (ErrDiff != last_err))
	//{
		val->iSum = val->iSum + ErrDiff;
		if(val->iSum > 32000) val->iSum = 32000;
		if(val->iSum < -32000) val->iSum = -32000;
		
		//if(iSum > 65000) iSum = 65000;
		//if(iSum < -65000) iSum = -65000;
	//}
	//if((last_set_ctrl_val <= 1) && (last_set_ctrl_val > 1022) /*&& (ErrDiff != last_err)*/)
	//{
		//iSum = last_iSum;
	//}
	
	I_term = val->iSum * val->Ki;
	/* Set limit for iSum */
	//if(iSum > 1000) iSum = 1000;
	//if(iSum < -32000) iSum = -32000;
	
	/* Derivative term */
	D_term = (ErrDiff - val->last_err) * val->Kd;
	
	/* Calc PID control value */
	set_ctrl_val = /*last_set_ctrl_val +*/ P_term + I_term + D_term;
	/* Set limit for  set_ctrl_val*/
	if(set_ctrl_val >= 1000) set_ctrl_val = 1000;
	if(set_ctrl_val <= 1) set_ctrl_val = 0;
	
	val->last_iSum = val->iSum;
	val->last_err = ErrDiff;
	
	val->last_set_ctrl_val = set_ctrl_val;
	
	return (uint16_t)set_ctrl_val;
}





