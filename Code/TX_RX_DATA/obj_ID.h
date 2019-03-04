
/* byte[0]*/
#define	ID_NETWORK			0x01

/* byte[1]*/
#define	MY_ID				0x72
#define ID_REMOTE_CNTRL		0x02

/* byte[2] & byte[3]*/
#define	IND_obj_NULL			0x0000
#define	IND_obj_VOLTAGE			0x0001
#define IND_obj_CURRENT			0x0002
#define IND_obj_CNT				0x0003
#define	IND_obj_STATUS			0x0004
#define	IND_obj_PWM  			0x0005
#define IND_obj_SetPORT_DIO     0x0006  
#define IND_obj_fb_PORT_DIO 	0x0007  
#define IND_obj_SetPWM			0x0008  
#define IND_obj_SetPID1_0		0x0009
#define	IND_obj_SetPID1_1       0x000A
#define IND_obj_PID1_0          0x000B
#define	IND_obj_PID1_1          0x000C
#define IND_obj_SetPID2_0		0x000D
#define	IND_obj_SetPID2_1       0x000E
#define IND_obj_PID2_0          0x000F
#define	IND_obj_PID2_1          0x0010
#define IND_obj_CTRL            0x0011


#define	IND_obj_END			0xFFFF
