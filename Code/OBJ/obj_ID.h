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
#define IND_obj_PredZar       (IND_obj_NULL + 8)		// ���������� ����� [���. ����� ����������]
#define IND_obj_KM1           (IND_obj_NULL + 9)		// ���������� ����� [���. ��������� ��1]
/*-----------------------------------------------*/
#define IND_obj_PWM1          (IND_obj_NULL + 10)		// [���������� ��� 1 �������]
#define IND_obj_PWM2          (IND_obj_NULL + 11)		// [���������� ��� 2 �������]
/*-----------------SOFTOBJ-----------------------*/
#define IND_obj_TICK_1S       (IND_obj_NULL + 12)		// [��� c ������ �������]
/*-----------------------------------------------*/
#define IND_obj_ADC_CONV      (IND_obj_NULL + 13)		// [��������� ��������� �������� ADC]

/*             ������ ���������� ���                    */
#define IND_obj_PWM_FREQ      (IND_obj_NULL + 14)		// [��������� ������� ���] 
#define IND_obj_PWM_ON        (IND_obj_NULL + 15)		// [���./����. ���] 

/*           ��� ��������� - 1                         */
#define IND_obj_PID1_KP		  (IND_obj_NULL + 16)
#define IND_obj_PID1_KI		  (IND_obj_NULL + 17)
#define IND_obj_PID1_KD		  (IND_obj_NULL + 18)
#define IND_obj_PID_ON	 	  (IND_obj_NULL + 19)

/*������ ���������� �������� ��������������� (��������) */
#define IND_obj_BUCK_MODE	  (IND_obj_NULL + 20)	//[���������� ����� ���������������]
#define IND_obj_BOOST_MODE	  (IND_obj_NULL + 21)	//[���������� ����� ��������������]

/*���� ��������*/
#define IND_obj_TIM1		  (IND_obj_NULL + 22)	//[������ 1]
#define IND_obj_TIM2		  (IND_obj_NULL + 23)	//[������ 2]

#endif
