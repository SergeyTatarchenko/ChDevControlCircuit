#ifndef OBJ_ID_H_
#define	OBJ_ID_H_


#define	IND_obj_NULL			0x00
#define	IND_obj_END				0xFF


/*-----------------------------------------------*/
#define obj_STATUS			  (IND_obj_NULL + 1)	
/*---------------------HWOBJ---------------------*/
#define IND_obj_ADC1          (IND_obj_NULL + 2)		// ���������� ��� 1
/*-----------------------------------------------*/
#define IND_obj_OUT0          (IND_obj_NULL + 3)		// ���������� ����� 0
#define IND_obj_OUT7          (IND_obj_NULL + 4)		// ���������� ����� 7
/*-----------------------------------------------*/
#define IND_obj_IN0           (IND_obj_NULL + 5)		// ���������� ���� (����� U���/2)
/*-----------------------------------------------*/
#define IND_obj_PWM0          (IND_obj_NULL + 6)		// ���������� ��� 1
#define IND_obj_PWM1          (IND_obj_NULL + 7)		// ���������� ��� 2
			/*-----------------SOFTOBJ-----------------------*/
#define IND_obj_TICK_1S       (IND_obj_NULL + 8)	// ��� ���� 1c
#define IND_obj_TICK_100_ms   (IND_obj_NULL + 9)	// ��� ���� 100 ��
#define IND_obj_LED           (IND_obj_NULL + 10)	// ��������� �� �����
#define IND_obj_PID_KP		  (IND_obj_NULL + 11)
#define IND_obj_PID_KI		  (IND_obj_NULL + 12)
#define IND_obj_PID_KD		  (IND_obj_NULL + 13)
#define IND_obj_PID_SET_VAl	  (IND_obj_NULL + 14)
#define IND_obj_PID_FDB		  (IND_obj_NULL + 15)

#define IND_obj_CHAR1         (IND_obj_NULL + 16)		//  
#define IND_obj_CHAR2         (IND_obj_NULL + 17)		//  
#define IND_obj_CHAR3         (IND_obj_NULL + 18)		//  
#define IND_obj_CHAR4         (IND_obj_NULL + 19)		//  

#endif
