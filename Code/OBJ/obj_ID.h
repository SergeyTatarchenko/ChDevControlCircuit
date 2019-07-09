#ifndef OBJ_ID_H_
#define	OBJ_ID_H_


#define	IND_obj_NULL			0x00
#define	IND_obj_END				0xFF


/*-----------------------------------------------*/
#define obj_STATUS			  (IND_obj_NULL + 1)	
/*---------------------HWOBJ---------------------*/
#define IND_obj_aINV          (IND_obj_NULL + 2)		// ���������� ��� 1 [������� ���������� ]
#define IND_obj_aINC          (IND_obj_NULL + 3)		// ���������� ��� 2 [������� ���        ]
#define IND_obj_aOUTV         (IND_obj_NULL + 4)		// ���������� ��� 3 [�������� ����������]
#define IND_obj_aOUTC         (IND_obj_NULL + 5)		// ���������� ��� 4 [�������� ���       ]
#define IND_obj_aDRV          (IND_obj_NULL + 6)		// ���������� ��� 5 [���������� ��������]
#define IND_obj_aDRC          (IND_obj_NULL + 7)		// ���������� ��� 6 [��� ��������       ] 
/*-----------------------------------------------*/
#define IND_obj_OUT6          (IND_obj_NULL + 8)		// ���������� ����� 6
#define IND_obj_OUT7          (IND_obj_NULL + 9)		// ���������� ����� 7
/*-----------------------------------------------*/
#define IND_obj_IN0           (IND_obj_NULL + 10)		// ���������� ���� (����� U���/2)
/*-----------------------------------------------*/
#define IND_obj_PWM1          (IND_obj_NULL + 11)		// ���������� ��� 1
#define IND_obj_PWM2          (IND_obj_NULL + 12)		// ���������� ��� 2

/*-----------------SOFTOBJ-----------------------*/

#define IND_obj_TICK_1S       (IND_obj_NULL + 13)		// ��� ���� 1c
#define IND_obj_TICK_100_ms   (IND_obj_NULL + 14)		// ��� ���� 100 ��
#define IND_obj_LED           (IND_obj_NULL + 15)		// ��������� �� �����
#define IND_obj_ADC_CONV      (IND_obj_NULL + 16)		// ��������� ��������� �������� ����� ���
#define IND_obj_PWM_FREQ      (IND_obj_NULL + 17)		// �������� ������� ��� 
#define IND_obj_PWM_ON        (IND_obj_NULL + 18)		// ���./����. ��� 
#define IND_obj_PID_KP		  (IND_obj_NULL + 19)
#define IND_obj_PID_KI		  (IND_obj_NULL + 20)
#define IND_obj_PID_KD		  (IND_obj_NULL + 21)
#define IND_obj_PID_SET_VAl	  (IND_obj_NULL + 22)
#define IND_obj_PID_FDB		  (IND_obj_NULL + 23)

#endif
