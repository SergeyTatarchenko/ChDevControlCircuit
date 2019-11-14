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
v 0.3
1) create object name  example   " #define obj_name	(IND_obj_NULL + x)"
2) create object init like "obj_name_init  obj_index,class,snap,handler	
3) add 	object init to 	_obj_cofig_	
*/
/*-----------------------------------------------------------------------------------------------------------------------\
           name               |      index          |   class     | type     | hw_snap   |    delay    |   Handler        | 
\-----------------------------------------------------------------------------------------------------------------------*/ 
#define _obj_STATUS_init       obj_STATUS           ,IND_obj_CAS  ,obj_soft  ,   NULL     ,NULL        ,board_START
/*--------------------------------------------------------------------------------------------------------------------*/
#define _obj_ADC0_init	       IND_obj_aADC0        ,IND_obj_CAS  ,obj_hard  ,   adc_0   ,NULL         ,ADC0_Handler
#define _obj_ADC1_init	       IND_obj_aADC1        ,IND_obj_CAS  ,obj_hard  ,   adc_1   ,NULL         ,ADC1_Handler
#define _obj_ADC2_init	       IND_obj_aADC2        ,IND_obj_CAS  ,obj_hard  ,   adc_2   ,NULL         ,ADC2_Handler
#define _obj_ADC3_init	       IND_obj_aADC3        ,IND_obj_CAS  ,obj_hard  ,   adc_3   ,NULL         ,ADC3_Handler
#define _obj_ADC4_init	       IND_obj_aADC4        ,IND_obj_CAS  ,obj_hard  ,   adc_4   ,NULL         ,ADC4_Handler
#define _obj_ADC5_init	       IND_obj_aADC5        ,IND_obj_CAS  ,obj_hard  ,   adc_5   ,NULL         ,ADC5_Handler
#define _obj_ADC6_init	       IND_obj_aADC6        ,IND_obj_CAS  ,obj_hard  ,   adc_6   ,NULL         ,NULL
#define _obj_ADC7_init	       IND_obj_aADC7        ,IND_obj_CAS  ,obj_hard  ,   adc_7   ,NULL         ,NULL
/*---------------------------------------------------------------------------------------------------*/
#define _obj_IN0_init	       IND_obj_iInput0      ,IND_obj_CAS  ,obj_hard  ,   in_0   ,NULL         ,NULL
#define _obj_IN1_init	       IND_obj_iInput1      ,IND_obj_CAS  ,obj_hard  ,   in_1   ,NULL         ,NULL
#define _obj_IN2_init	       IND_obj_iInput2      ,IND_obj_CAS  ,obj_hard  ,   in_2   ,NULL         ,NULL
#define _obj_IN3_init	       IND_obj_iInput3      ,IND_obj_CAS  ,obj_hard  ,   in_3   ,NULL         ,NULL
#define _obj_IN4_init	       IND_obj_iInput4      ,IND_obj_CAS  ,obj_hard  ,   in_4   ,NULL         ,NULL
#define _obj_IN5_init	       IND_obj_iInput5      ,IND_obj_CAS  ,obj_hard  ,   in_5   ,NULL         ,NULL
#define _obj_IN6_init	       IND_obj_iInput6      ,IND_obj_CAS  ,obj_hard  ,   in_6   ,NULL         ,NULL
#define _obj_IN7_init	       IND_obj_iInput7      ,IND_obj_CAS  ,obj_hard  ,   in_7   ,NULL         ,NULL
/*---------------------------------------------------------------------------------------------------*/
#define _obj_OUT0_init         IND_obj_oOUT0        ,IND_obj_CAS  ,obj_hard  ,   out_0   ,NULL         ,NULL
#define _obj_OUT1_init	       IND_obj_oOUT1        ,IND_obj_CAS  ,obj_hard  ,   out_1   ,NULL         ,NULL
#define _obj_OUT2_init	       IND_obj_oOUT2        ,IND_obj_CAS  ,obj_hard  ,   out_2   ,NULL         ,NULL
#define _obj_OUT3_init	       IND_obj_oOUT3        ,IND_obj_CAS  ,obj_hard  ,   out_3   ,NULL         ,NULL
#define _obj_OUT4_init	       IND_obj_oOUT4        ,IND_obj_CAS  ,obj_hard  ,   out_4   ,NULL         ,NULL
#define _obj_OUT5_init	       IND_obj_oOUT5        ,IND_obj_CAS  ,obj_hard  ,   out_5   ,NULL         ,NULL
#define _obj_OUT6_init	       IND_obj_PredZar      ,IND_obj_CAS  ,obj_hard  ,   out_6   ,NULL         ,NULL
#define _obj_OUT7_init	       IND_obj_KM1          ,IND_obj_CAS  ,obj_hard  ,   out_7   ,NULL         ,NULL
/*---------------------------------------------------------------------------------------------------*/
#define _obj_USART_TX_init     IND_obj_USART_TX     ,IND_obj_SWC  ,obj_timer ,   NULL   ,100          ,USART_Handler
/*---------------------------------------------------------------------------------------------------*/
#define obj_aINV_init	       IND_obj_aINV         ,IND_obj_SWC  ,obj_soft  ,   NULL ,NULL         ,NULL
#define obj_aINC_init	       IND_obj_aINC         ,IND_obj_SWC  ,obj_soft  ,   NULL ,NULL         ,NULL
#define obj_aOUTV_init	       IND_obj_aOUTV        ,IND_obj_SWC  ,obj_soft  ,   NULL ,NULL         ,NULL
#define obj_aOUTC_init	       IND_obj_aOUTC        ,IND_obj_SWC  ,obj_soft  ,   NULL ,NULL         ,NULL
#define obj_aDRV_init	       IND_obj_aDRV         ,IND_obj_SWC  ,obj_soft  ,   NULL ,NULL         ,NULL
#define obj_aDRC_init	       IND_obj_aDRC         ,IND_obj_SWC  ,obj_soft  ,   NULL ,NULL         ,NULL
/*---------------------------------------------------------------------------------------------------*/
#define _obj_PID1_KP_init      IND_obj_PID1_KP      ,IND_obj_COM  ,obj_soft  ,   NULL   ,NULL          ,PID_COEF_Handler
#define _obj_PID1_KI_init      IND_obj_PID1_KI      ,IND_obj_COM  ,obj_soft  ,   NULL   ,NULL          ,PID_COEF_Handler
#define _obj_PID1_KD_init      IND_obj_PID1_KD      ,IND_obj_COM  ,obj_soft  ,   NULL   ,NULL          ,PID_COEF_Handler
#define _obj_PID_init          IND_obj_PID_ON       ,IND_obj_CAS  ,obj_soft  ,   NULL   ,NULL          ,PID_Control_Handler
/*---------------------------------------------------------------------------------------------------*/
#define obj_cPMinV_init        IND_obj_cPMinV       ,IND_obj_CWS  ,obj_soft  ,   NULL   ,NULL          ,NULL
#define obj_cPMax_Vinit        IND_obj_cPMaxV       ,IND_obj_CWS  ,obj_soft  ,   NULL   ,NULL          ,NULL
#define obj_cSVError_init      IND_obj_cSVError     ,IND_obj_CWS  ,obj_soft  ,   NULL   ,NULL          ,NULL
#define obj_cSCError_init      IND_obj_cSCError     ,IND_obj_CWS  ,obj_soft  ,   NULL   ,NULL          ,NULL
#define obj_cMaxDutyC_init     IND_obj_cMaxDutyC    ,IND_obj_CWS  ,obj_soft  ,   NULL   ,NULL          ,NULL
#define obj_cMinDutyC_init     IND_obj_cMinDutyC    ,IND_obj_CWS  ,obj_soft  ,   NULL   ,NULL          ,NULL
#define obj_cMaxTemp_init      IND_obj_cMaxTemp     ,IND_obj_CWS  ,obj_soft  ,   NULL   ,NULL          ,NULL
#define obj_cFreq_init         IND_obj_cFreq        ,IND_obj_CWS  ,obj_soft  ,   NULL   ,NULL          ,NULL
#define obj_cGysteresis_init   IND_obj_cGysteresis  ,IND_obj_CWS  ,obj_soft  ,   NULL   ,NULL          ,NULL
#define obj_cSync_init         IND_obj_cSync        ,IND_obj_CWS  ,obj_soft  ,   NULL   ,NULL          ,Write_config_Handler
/*---------------------------------------------------------------------------------------------------*/
#define _obj_ACUR_C_init       IND_obj_ACUR_C       ,IND_obj_SWC  ,obj_soft  ,   NULL   ,NULL          ,NULL
#define _obj_ACUR_G_init       IND_obj_ACUR_G       ,IND_obj_SWC  ,obj_soft  ,   NULL   ,NULL          ,NULL
#define _obj_CUR_C_init        IND_obj_CUR_C        ,IND_obj_SWC  ,obj_soft  ,   NULL   ,NULL          ,NULL
#define _obj_CUR_G_init        IND_obj_CUR_G        ,IND_obj_SWC  ,obj_soft  ,   NULL   ,NULL          ,NULL
#define _obj_ECE_init          IND_obj_ECE          ,IND_obj_SWC  ,obj_soft  ,   NULL   ,NULL          ,NULL
#define _obj_Q_init            IND_obj_Q            ,IND_obj_SWC  ,obj_soft  ,   NULL   ,NULL          ,NULL
#define _obj_ERR_init          IND_obj_ERR_ARRAY    ,IND_obj_SWC  ,obj_soft  ,   NULL   ,NULL          ,NULL
/*---------------------------------------------------------------------------------------------------*/
#define _obj_PWM_FRQ_init      IND_obj_PWM_FREQ     ,IND_obj_CAS  ,obj_soft  ,   NULL   ,NULL          ,PWM_freq_config_Handler
#define _obj_PWM_ON_init       IND_obj_PWM_ON       ,IND_obj_CAS  ,obj_soft  ,   NULL   ,NULL          ,PWM_Control_Handler 
#define _obj_BUCK_init         IND_obj_M_BUCK_MODE  ,IND_obj_CAS  ,obj_soft  ,   NULL   ,NULL          ,BUCK_Mode_Handler
#define _obj_BOOST_init        IND_obj_M_BOOST_MODE ,IND_obj_CAS  ,obj_soft  ,   NULL   ,NULL          ,BOOST_Mode_Handler
#define _obj_tKM_Off_init      IND_obj_tKM_Off      ,IND_obj_SWC  ,obj_timer ,   NULL   ,200           ,KM_Off_Handler

/*init struct for obj model setup*/
#define _obj_cofig_	\
{_obj_STATUS_init}, \
{_obj_ADC0_init},{_obj_ADC1_init},{_obj_ADC2_init},{_obj_ADC3_init},{_obj_ADC4_init},{_obj_ADC5_init},{_obj_ADC6_init},{_obj_ADC7_init}, \
{_obj_IN0_init},{_obj_IN1_init},{_obj_IN2_init},{_obj_IN3_init},{_obj_IN4_init},{_obj_IN5_init},{_obj_IN6_init},{_obj_IN7_init}, \
{_obj_OUT0_init},{_obj_OUT1_init},{_obj_OUT2_init},{_obj_OUT3_init},{_obj_OUT4_init},{_obj_OUT5_init},{_obj_OUT6_init},{_obj_OUT7_init}, \
{_obj_USART_TX_init}, \
{obj_aINV_init},{obj_aINC_init},{obj_aOUTV_init},{obj_aOUTC_init},{obj_aDRV_init},{obj_aDRC_init}, \
{_obj_PID1_KP_init},{_obj_PID1_KI_init},{_obj_PID1_KD_init},{_obj_PID1_KP_init},{_obj_PID_init}, \
{obj_cPMinV_init},{obj_cPMax_Vinit},{obj_cSVError_init},{obj_cSCError_init},{obj_cMaxDutyC_init},{obj_cMinDutyC_init},{obj_cMaxTemp_init},{obj_cFreq_init},{obj_cGysteresis_init},{obj_cSync_init}, \
{_obj_ACUR_C_init},{_obj_ACUR_G_init},{_obj_CUR_C_init},{_obj_CUR_G_init},{_obj_ECE_init},{_obj_Q_init},{_obj_ERR_init}, \
{_obj_PWM_FRQ_init},{_obj_PWM_ON_init},{_obj_BUCK_init},{_obj_BOOST_init},{_obj_tKM_Off_init}

/*--------------------------------------------------------------------------------------*/
/*obj handlers*/
void board_START(OBJ_STRUCT *obj);
/*-------------------------------------------------*/
void ADC0_Handler(OBJ_STRUCT *obj);
void ADC1_Handler(OBJ_STRUCT *obj);
void ADC2_Handler(OBJ_STRUCT *obj);
void ADC3_Handler(OBJ_STRUCT *obj);
void ADC4_Handler(OBJ_STRUCT *obj);
void ADC5_Handler(OBJ_STRUCT *obj);
/*-------------------------------------------------*/
void USART_Handler(OBJ_STRUCT *obj);
/*-------------------------------------------------*/
void Write_config_Handler(OBJ_STRUCT *obj);
/*-------------------------------------------------*/
void PWM_freq_config_Handler(OBJ_STRUCT *obj);
void PWM_Control_Handler(OBJ_STRUCT *obj);
void BUCK_Mode_Handler(OBJ_STRUCT *obj);
void BOOST_Mode_Handler(OBJ_STRUCT *obj);
void PID_COEF_Handler(OBJ_STRUCT *obj);
void PID_Control_Handler(OBJ_STRUCT *obj);
void KM_Off_Handler(OBJ_STRUCT *obj);
#endif
