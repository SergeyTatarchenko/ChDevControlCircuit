
#include "B72.h"
#include "global.h"
/************************************************************************************/
/* 									 OBJ_Handlers									*/
/************************************************************************************/

void board_START(OBJ_STRUCT *obj)
{
	if(obj->obj_state == 1)
	{
		board_power = 1;
		OBJ_Event(IND_obj_USART_TX);
	}
	else
	{
		board_power = 0;
		set_all_obj_off();
		LED_OFF;
	}
}

/*��������� ���*/
void ADC_Handler(OBJ_STRUCT *obj){
	/*
	AIN0 - dvl1000   ������� ����������
	AIN1 - lac300  	 ������� ��� 	

	AIN2 - dvl1000   �������� ����������
	AIN3 - lac300    �������� ���

	AIN4 - dvl1000   ���������� ��������
	AIN5 - lf510     ��� ��������
	*/
	this_obj(IND_obj_aINV)->obj_value = get_dvl1000_value(adc_val->CH1_ADC);
	this_obj(IND_obj_aINC)->obj_value = get_lac300_value(adc_val->CH2_ADC);
	
	this_obj(IND_obj_aOUTV)->obj_value = get_dvl1000_value(adc_val->CH3_ADC);
	this_obj(IND_obj_aOUTC)->obj_value = get_lac300_value(adc_val->CH4_ADC);
	
	this_obj(IND_obj_aDRV)->obj_value = get_dvl1000_value(adc_val->CH5_ADC);
	this_obj(IND_obj_aDRC)->obj_value = get_lac300_value(adc_val->CH6_ADC);
	
	/* test */
//	this_obj(IND_obj_aINV)->obj_value = adc_val->CH1_ADC;
//	this_obj(IND_obj_aINC)->obj_value = adc_val->CH2_ADC;
//	this_obj(IND_obj_aOUTV)->obj_value = adc_val->CH3_ADC;
//	this_obj(IND_obj_aOUTC)->obj_value = adc_val->CH4_ADC;
//	this_obj(IND_obj_aDRC)->obj_value = adc_val->CH5_ADC;
//	this_obj(IND_obj_aDRV)->obj_value = adc_val->CH6_ADC;
}

/*�������� ����� ���������������� ���� �������� ����� �� ��������*/
void USART_Handler(OBJ_STRUCT *obj){
	
	obj->obj_value++;
	led_invertor();
	
	if(board_power == 1){
		FAST_Upd_All_OBJ_USART();
		OBJ_Event(IND_obj_USART_TX);
	}
}

/*��������� ������ ����������� ���������������*/
void BUCK_Mode_Handler(OBJ_STRUCT *obj)
{
	if(obj->obj_state == 1){
		/*��� ���������*/
		obj_state_on(IND_obj_KM1);
		
		/*��������� ��� ������ ��� �������� �����������, ������ ���������� ������*/
		obj_state_on(IND_obj_PWM2);	
		/*��������� ������� 2 ���*/
		this_obj(IND_obj_PWM_FREQ)->obj_value = 2000;
		obj_state_on(IND_obj_PWM_FREQ);
	
		/*��������� ���  - ���������� 50%*/
		this_obj(IND_obj_PWM_ON)->obj_value = 500;
		obj_state_on(IND_obj_PWM_ON);	
	}else{
		obj_state_off(IND_obj_PWM_ON);
		obj_state_off(IND_obj_PWM2);
		/*���� ���������*/
		obj_state_off(IND_obj_KM1);
	}
}

/*��������� ������ ����������� ���������������*/
void BOOST_Mode_Handler(OBJ_STRUCT *obj)
{
	if(obj->obj_state == 1){
		
		/*��� ���������*/
		obj_state_on(IND_obj_KM1);
		
		/*��������� ��� ������ ��� ������� �����������, ������� ���������� ������*/
		obj_state_on(IND_obj_PWM1);	
		/*��������� ������� 2 ���*/
		this_obj(IND_obj_PWM_FREQ)->obj_value = 2000;
		obj_state_on(IND_obj_PWM_FREQ);
	
		/*��������� ���  - ���������� 50%*/
		this_obj(IND_obj_PWM_ON)->obj_value = 500;
		obj_state_on(IND_obj_PWM_ON);
		PWM_PIN1_ON; // �������� �������� ����������� !!!
	}
	else{
		obj_state_off(IND_obj_PWM_ON);
		PWM_PIN1_OFF;
		obj_state_off(IND_obj_PWM2);
		
		/*���� ���������*/
		obj_state_off(IND_obj_KM1);

	}
}

/*�������� ������ ��� 1*/
void PWM1_Handler(OBJ_STRUCT *obj){
	
	if(obj->obj_state == 1){
		obj_state_off(IND_obj_PWM2);
		
		PWMSetActiveChannel(CH4);
		PWMSetActiveChannel(CH3);
	}else{
		PWMSetActiveChannel(ALL_CH_OFF);		
	}
}

/*�������� ������ ��� 2*/
void PWM2_Handler(OBJ_STRUCT *obj){
	if(obj->obj_state == 1){
		PWMSetActiveChannel(ALL_CH_OFF);
		PWMSetActiveChannel(CH4);
	}else{
		PWMSetActiveChannel(ALL_CH_OFF);
	}
}

/*�������� ������� ���*/
void PWM_freq_config_Handler(OBJ_STRUCT *obj){
	if(obj->obj_state){
		PWMSetFrequency(obj->obj_value);
	}else{
		obj_state_off(IND_obj_PWM_ON);
	}
}

/*��������� � ���������� ��� � ����������*/
void PWM_Control_Handler(OBJ_STRUCT *obj){
	if(obj->obj_state){
		if(this_obj(IND_obj_PWM1)->obj_state == 1){
			PWMSetValue(CH3,obj->obj_value);
			PWMSetValue(CH4,PERIOD_PWM);
			PWM_ON;	
		}
		if(this_obj(IND_obj_PWM2)->obj_state == 1){
			PWMSetValue(CH4,obj->obj_value);
			PWM_ON;
		}
	}else{
		PWM_OFF;
		PWMSetValue(CH3,0);
		PWMSetValue(CH4,0);
	}
}

/*��������� �������� ��� ����������*/
void PID_COEF_Handler(OBJ_STRUCT *obj){
	
	pid_current_out.Kp = (float)(this_obj(IND_obj_PID1_KP)->dWordL)/10000.0;
	pid_current_out.Ki = (float)(this_obj(IND_obj_PID1_KI)->dWordL)/10000.0;
	pid_current_out.Kd = (float)(this_obj(IND_obj_PID1_KD)->dWordL)/10000.0;
}

/*��������� ��� ���������� (����)*/
void PID_Control_Handler(OBJ_STRUCT *obj){
	if(obj->obj_state == 1){
		pid_current_out.setpoint_val = obj->obj_value;
	}else{
		pid_current_out.setpoint_val = 0;
	}
}


