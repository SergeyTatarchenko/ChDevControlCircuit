#ifndef LIST_OBJ_H_
#define LIST_OBJ_H_

extern void obj_snap(void);


/*-----------------------------------------------*/

void IO_ControlHandler(OBJ_STRUCT *obj);
void ADC_Handler(OBJ_STRUCT *obj);

void TICK_Handler(OBJ_STRUCT *obj);

void LED_Control_Handler(OBJ_STRUCT *obj);

void LED_Control_Handler(OBJ_STRUCT *obj);

void Dummy_Handler(OBJ_STRUCT *obj);
#endif
