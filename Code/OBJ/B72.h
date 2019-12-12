#ifndef B72_H_
#define	B72_H_

#include "OBJ_MODEL.h"
#include "obj_ID.h"
#include "hw_support.h"
#include "AlgorithmCD.h"
/*-------------------------------------------------*/
#define	ID_NETWORK			0x01
#define	ID_DEVICE			0x72
#define ID_REMOTE_CNTRL		0x02
#define	FLAG_RX_ALL			0xFF
/*
v 0.6
1) create object name  example   " #define obj_name	(IND_obj_NULL + x)"
2) create object init like "obj_index,class,snap,delay,handler in  _obj_cofig_ define	
----------------------------------------------------------------------------------------------------------------;
           index          |     class        |   type    | hw_snap   |    delay    |   Handler         
----------------------------------------------------------------------------------------------------------------;
*/
#define _obj_cofig_                                                                                         	\
{ obj_STATUS             ,IND_obj_CAS        ,obj_soft  ,    NSD    ,NSD            ,board_START             }, \
{ IND_obj_aADC0          ,IND_obj_CAS        ,obj_hard  ,   adc_0   ,NSD            ,ADC0_Handler            }, \
{ IND_obj_aADC1          ,IND_obj_CAS        ,obj_hard  ,   adc_1   ,NSD            ,ADC1_Handler            }, \
{ IND_obj_aADC2          ,IND_obj_CAS        ,obj_hard  ,   adc_2   ,NSD            ,ADC2_Handler            }, \
{ IND_obj_aADC3          ,IND_obj_CAS        ,obj_hard  ,   adc_3   ,NSD            ,ADC3_Handler            }, \
{ IND_obj_aADC4          ,IND_obj_CAS        ,obj_hard  ,   adc_4   ,NSD            ,ADC4_Handler            }, \
{ IND_obj_aADC5          ,IND_obj_CAS        ,obj_hard  ,   adc_5   ,NSD            ,ADC5_Handler            }, \
{ IND_obj_aADC6          ,IND_obj_CAS        ,obj_hard  ,   adc_6   ,NSD            ,NSD                     }, \
{ IND_obj_aADC7          ,IND_obj_CAS        ,obj_hard  ,   adc_7   ,NSD            ,ADC7_Handler            }, \
{ IND_obj_iInput0        ,IND_obj_CAS        ,obj_hard  ,   in_0    ,NSD            ,NSD                     }, \
{ IND_obj_iInput1        ,IND_obj_CAS        ,obj_hard  ,   in_1    ,NSD            ,NSD                     }, \
{ IND_obj_iInput2        ,IND_obj_CAS        ,obj_hard  ,   in_2    ,NSD            ,NSD                     }, \
{ IND_obj_iInput3        ,IND_obj_CAS        ,obj_hard  ,   in_3    ,NSD            ,NSD                     }, \
{ IND_obj_iInput4        ,IND_obj_CAS        ,obj_hard  ,   in_4    ,NSD            ,NSD                     }, \
{ IND_obj_iInput5        ,IND_obj_CAS        ,obj_hard  ,   in_5    ,NSD            ,NSD                     }, \
{ IND_obj_iInput6        ,IND_obj_CAS        ,obj_hard  ,   in_6    ,NSD            ,NSD                     }, \
{ IND_obj_iInput7        ,IND_obj_CAS        ,obj_hard  ,   in_7    ,NSD            ,NSD                     }, \
{ IND_obj_oOUT0          ,IND_obj_CAS        ,obj_hard  ,   out_0   ,NSD            ,NSD                     }, \
{ IND_obj_oOUT1          ,IND_obj_CAS        ,obj_hard  ,   out_1   ,NSD            ,NSD                     }, \
{ IND_obj_oOUT2          ,IND_obj_CAS        ,obj_hard  ,   out_2   ,NSD            ,NSD                     }, \
{ IND_obj_oOUT3          ,IND_obj_CAS        ,obj_hard  ,   out_3   ,NSD            ,NSD                     }, \
{ IND_obj_Vent           ,IND_obj_CAS        ,obj_hard  ,   out_7   ,NSD            ,NSD                     }, \
{ IND_obj_DrOn           ,IND_obj_CAS        ,obj_hard  ,   out_6   ,NSD            ,NSD                     }, \
{ IND_obj_PredZar        ,IND_obj_CAS        ,obj_hard  ,   out_5   ,NSD            ,NSD                     }, \
{ IND_obj_KM1            ,IND_obj_CAS        ,obj_hard  ,   out_4   ,NSD            ,NSD                     }, \
{ IND_obj_USART_TX       ,IND_obj_SWC        ,obj_timer ,   NSD     ,150            ,USART_Handler           }, \
{ IND_obj_tKM_Off        ,IND_obj_SWC        ,obj_timer ,   NSD     ,200            ,KM_Off_Handler          }, \
{ IND_obj_aINV           ,IND_obj_SWC        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_aINC           ,IND_obj_SWC        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_aOUTV          ,IND_obj_SWC        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_aOUTC          ,IND_obj_SWC        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_aDRV           ,IND_obj_SWC        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_aDRC           ,IND_obj_SWC        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_TempRadiator   ,IND_obj_SWC        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_PID1_KP        ,IND_obj_COM        ,obj_soft  ,   NSD     ,NSD            ,PID_COEF_Handler        }, \
{ IND_obj_PID1_KI        ,IND_obj_COM        ,obj_soft  ,   NSD     ,NSD            ,PID_COEF_Handler        }, \
{ IND_obj_PID1_KD        ,IND_obj_COM        ,obj_soft  ,   NSD     ,NSD            ,PID_COEF_Handler        }, \
{ IND_obj_PID_ON         ,IND_obj_CAS        ,obj_soft  ,   NSD     ,NSD            ,PID_Control_Handler     }, \
{ IND_obj_cPMinV         ,IND_obj_CWS        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_cPMaxV         ,IND_obj_CWS        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_cSVError       ,IND_obj_CWS        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_cSCError       ,IND_obj_CWS        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_cMaxDutyC      ,IND_obj_CWS        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_cMinDutyC      ,IND_obj_CWS        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_cMaxTemp       ,IND_obj_CWS        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_cFreq          ,IND_obj_CWS        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_cGysteresis    ,IND_obj_CWS        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_cSync          ,IND_obj_CWS        ,obj_soft  ,   NSD     ,NSD            ,Write_config_Handler    }, \
{ IND_obj_ACUR_C         ,IND_obj_SWC        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_ACUR_G         ,IND_obj_SWC        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_CUR_C          ,IND_obj_SWC        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_CUR_G          ,IND_obj_SWC        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_ECE            ,IND_obj_SWC        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_Q              ,IND_obj_SWC        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_ERR_ARRAY      ,IND_obj_SWC        ,obj_soft  ,   NSD     ,NSD            ,NSD                     }, \
{ IND_obj_PWM_FREQ       ,IND_obj_CAS        ,obj_soft  ,   NSD     ,NSD            ,PWM_freq_config_Handler }, \
{ IND_obj_PWM_ON         ,IND_obj_CAS        ,obj_soft  ,   NSD     ,NSD            ,PWM_Control_Handler     }, \
{ IND_obj_M_BUCK_MODE    ,IND_obj_CAS        ,obj_soft  ,   NSD     ,NSD            ,BUCK_Mode_Handler       }, \
{ IND_obj_M_BOOST_MODE   ,IND_obj_CAS        ,obj_soft  ,   NSD     ,NSD            ,BOOST_Mode_Handler      }, \
{ IND_obj_PWM_COMMON     ,IND_obj_CAS        ,obj_soft  ,   NSD     ,NSD            ,pwm_common              }, \
{ IND_obj_PWM_CHANNEL4   ,IND_obj_CAS        ,obj_soft  ,   NSD     ,NSD            ,pwm_channel_4           }, \
{ IND_obj_PWM_CHANNEL3   ,IND_obj_CAS        ,obj_soft  ,   NSD     ,NSD            ,pwm_channel_3           }, \
{ IND_obj_CURLIMIT       ,IND_obj_CAS        ,obj_soft  ,   NSD     ,NSD            ,CurrentLimit            }
/*-------------------------------------------------------------------------------------------------------------*/
#define _diagnostic_	IND_obj_aINV,IND_obj_aINC,IND_obj_aOUTV,IND_obj_aOUTC,IND_obj_aDRV,IND_obj_aDRC
/*-------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------obj handlers prototypes------------------------------------------------*/
void board_START(OBJ_STRUCT *obj);
void ADC0_Handler(OBJ_STRUCT *obj);
void ADC1_Handler(OBJ_STRUCT *obj);
void ADC2_Handler(OBJ_STRUCT *obj);
void ADC3_Handler(OBJ_STRUCT *obj);
void ADC4_Handler(OBJ_STRUCT *obj);
void ADC5_Handler(OBJ_STRUCT *obj);
void ADC7_Handler(OBJ_STRUCT *obj);
void USART_Handler(OBJ_STRUCT *obj);
void Write_config_Handler(OBJ_STRUCT *obj);
void PWM_freq_config_Handler(OBJ_STRUCT *obj);
void PWM_Control_Handler(OBJ_STRUCT *obj);
void BUCK_Mode_Handler(OBJ_STRUCT *obj);
void BOOST_Mode_Handler(OBJ_STRUCT *obj);
void PID_COEF_Handler(OBJ_STRUCT *obj);
void PID_Control_Handler(OBJ_STRUCT *obj);
void KM_Off_Handler(OBJ_STRUCT *obj);
void key_on(OBJ_STRUCT *obj);
void pwm_common(OBJ_STRUCT *obj);
void pwm_channel_4(OBJ_STRUCT *obj);
void pwm_channel_3(OBJ_STRUCT *obj);
void CurrentLimit(OBJ_STRUCT *obj);
#endif
