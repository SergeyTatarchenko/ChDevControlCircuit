#ifndef OBJ_ID_H_
#define	OBJ_ID_H_


#define	IND_obj_NULL			0x00
#define	IND_obj_END				0xFF

/*-----------------------------------------------*/
#define obj_STATUS				(IND_obj_NULL + 1)	
/*---------------------HWOBJ---------------------*/
/*adc*/
#define IND_obj_aADC0			(IND_obj_NULL + 2)		// ���������� ��� 1
#define IND_obj_aADC1			(IND_obj_NULL + 3)		// ���������� ��� 2
#define IND_obj_aADC2			(IND_obj_NULL + 4)		// ���������� ��� 3
#define IND_obj_aADC3			(IND_obj_NULL + 5)		// ���������� ��� 4
#define IND_obj_aADC4			(IND_obj_NULL + 6)		// ���������� ��� 5
#define IND_obj_aADC5			(IND_obj_NULL + 7)		// ���������� ��� 6 
/*inputs*/
/*-----------------------------------------------*/
/*outputs*/
#define IND_obj_PredZar			(IND_obj_NULL + 8)		// ���������� ����� [���. ����� ����������]
#define IND_obj_KM1				(IND_obj_NULL + 9)		// ���������� ����� [���. ��������� ��1]
/*-----------------------------------------------*/
#define IND_obj_PWM1			(IND_obj_NULL + 10)		// [���������� ��� 1 ������� !���������� �����]
#define IND_obj_PWM2			(IND_obj_NULL + 11)		// [���������� ��� 2 ������� !���������� �����]
/*-----------------SOFTOBJ-----------------------*/
#define IND_obj_USART_TX		(IND_obj_NULL + 12)		// [������ ���������� ��������� �������� ����� �� USART]
/*-----------------------------------------------*/
#define IND_obj_aINV			(IND_obj_NULL + 14)		// [������� ���������� ]
#define IND_obj_aINC			(IND_obj_NULL + 15)		// [������� ���        ]
#define IND_obj_aOUTV			(IND_obj_NULL + 16)		// [�������� ����������]
#define IND_obj_aOUTC			(IND_obj_NULL + 17)		// [�������� ���       ]
#define IND_obj_aDRV			(IND_obj_NULL + 18)		// [���������� ��������]
#define IND_obj_aDRC			(IND_obj_NULL + 19)		// [��� ��������       ] 

/*             ������ ���������� ���                    */
#define IND_obj_PWM_FREQ		(IND_obj_NULL + 20)		// [��������� ������� ���] 
#define IND_obj_PWM_ON			(IND_obj_NULL + 21)		// [���./����. ���] 

/*           ��� ��������� - 1                         */
#define IND_obj_PID1_KP			(IND_obj_NULL + 22)
#define IND_obj_PID1_KI			(IND_obj_NULL + 23)
#define IND_obj_PID1_KD			(IND_obj_NULL + 24)
#define IND_obj_PID_ON			(IND_obj_NULL + 25)

/*������ ���������� �������� ��������������� (��������) */
#define IND_obj_BUCK_MODE		(IND_obj_NULL + 26)		//[���������� ����� ���������������]
#define IND_obj_BOOST_MODE		(IND_obj_NULL + 27)		//[���������� ����� ��������������]
#define IND_obj_DELAY_START		(IND_obj_NULL + 28)		//[������ �������� ������ ���������������]
/*-----------------------------------------------*/
#define IND_obj_ACUR_C			(IND_obj_NULL + 29)		//[�������������� ��������� ���� ��������]
#define IND_obj_ACUR_G			(IND_obj_NULL + 30)		//[����������  ��������� ���� ��������]
#define IND_obj_CUR_C			(IND_obj_NULL + 31)		//[�������������� ������������ ��� � ��������]
#define IND_obj_CUR_G			(IND_obj_NULL + 32)		//[���������� ������������ ��� � ��������]
/*-----------------------------------------------*/
#define IND_obj_ECE	  			(IND_obj_NULL + 33)		//[������� ��� �������]
#define IND_obj_Q	  			(IND_obj_NULL + 34)		//[����������� ����������� ��������� LC �������]
#define IND_obj_ERR_ARRAY	  	(IND_obj_NULL + 35)		//[������ ������ ��]
#define IND_obj_START		  	(IND_obj_NULL + 36)		//[������� "����" �� ����� ���������]
#define IND_obj_TEST2		  	(IND_obj_NULL + 37)		//[���� ������ � ����� �������� ������������]

#endif
