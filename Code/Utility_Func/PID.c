#include "PID.h"

K_PID pid_inductance;
K_PID pid_current_out;

int16_t PID_controller(K_PID *val)
{
	float set_ctrl_val = 0.0;
	//uint16_t set_ctrl_val = 0;
	int16_t ErrDiff = 0;
	float P_term = 0.0;
	float I_term = 0.0;
	float D_term = 0.0;
	
	/* Derivate error */
	ErrDiff = (int16_t)(val->setpoint_val - val->feedback);
	
	/* Proportional term */
	P_term = (float)(ErrDiff) * val->Kp;
	
	/* Integral term */
	int32_t last_iSum = val->iSum;
	val->iSum = val->iSum + (int32_t)(ErrDiff);
	if(val->iSum > 32000) val->iSum = 32000;
	if(val->iSum < -32000) val->iSum = -32000;
	
	I_term = (float)(val->iSum) * val->Ki;
	
	/* Derivative term */
	D_term = (float)(ErrDiff - val->last_err) * val->Kd;
	
	/**** Calc PID control value ****/
	set_ctrl_val = P_term + I_term + D_term;
	/**** ********************** ****/
	
	/* Set limit for  set_ctrl_val*/
	if(set_ctrl_val >= (val->out_Max - 1))
	{
		set_ctrl_val = val->out_Max;
		
		/*  */
		if(val->iSum > last_iSum)
		{
			val->iSum = last_iSum;
		}
		
	
	}else if(set_ctrl_val <= val->out_Min) 
	{
		set_ctrl_val = val->out_Min;
		
		/*  */
		if(val->iSum < last_iSum)
		{
			val->iSum = last_iSum;
		}
	}
	/* */

	val->last_err = ErrDiff;
	val->last_set_ctrl_val = set_ctrl_val;
	
	return (int16_t)(set_ctrl_val);
}





