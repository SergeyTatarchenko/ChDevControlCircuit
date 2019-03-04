#include "OBJ_DATA.h"

uint8_t	FLAG_RECEIVE;

ST_CHARGER Status_Charger;


//TX_RX_FRAME	Rx_obj;
volatile uint8_t buff_rx[LEN_MSG_OBJ];
uint8_t st_rx;
static uint8_t n_byte = 0;

void USART1_IRQHandler(void)
{
	volatile unsigned int IIR;
	
	IIR = USART1->SR;
	
//    if (IIR & USART_FLAG_RXNE) {                  // read interrupt
//		USART1->SR &= ~USART_FLAG_RXNE;	          // clear interrupt
		//buff_rx[n_byte] = usart_rx(&st_rx);
		buff_rx[n_byte] = USART1->DR;
		//objd_STATUS.data.data8b[0] = (uint8_t)USART1->DR;
		if(buff_rx[0] == ID_NETWORK)
		{
			if(n_byte < LEN_MSG_OBJ)
			{
				//buff_rx[++n_byte] = usart_rx(&st_rx);
				buff_rx[++n_byte] = USART1->DR;
			}else{
				
				n_byte = 0;	
			}
			
			if(n_byte == LEN_MSG_OBJ)
			{
				if(buff_rx[1] == ID_REMOTE_CNTRL)
				{
					FLAG_RECEIVE |= FLAG_RX_REMOTE_CTRL;
				}
			}
			
		}else{
			n_byte = 0;
		}
//	}
}



/* Transfer Data Obj */
uint8_t	Tx_OBJ_Data(OBJ_STRUCT *obj)
{
	uint8_t buff[LEN_MSG_OBJ];
	uint8_t n_byte = 0;
	uint16_t _CRC_ = 0;
	uint8_t i = 0;
	
	buff[n_byte] = ID_NETWORK;			// byte[0]
	buff[++n_byte] = MY_ID;				// byte[1]
	buff[++n_byte] = obj->id;			// byte[2]	index lsb
	buff[++n_byte] = ((obj->id) >> 8);	// byte[3]	index msb
	
	//n_byte = 0;
	for(i = 0; i < LEN_DATA; i++)
	{
		buff[++n_byte] = obj->data.d8b[i];	// byte[4]...byte[11]
	}

	
	/* Calc check summ */
	for(i = 0; i < LEN_MSG_OBJ - LEN_CRC; i++)
	{
		_CRC_ += buff[i];
	}
	
	buff[++n_byte] = _CRC_;					// byte[12]
	buff[++n_byte]	= (_CRC_ >> 8);				// byte[13]
	
	usart_tx(buff, LEN_MSG_OBJ);	// transfer data to usart
	//send_usart_message(buff, (uint32_t)LEN_MSG_OBJ);	// transfer data to usart
	
	return 0;
}


///* Receive Data Obj */
//uint8_t	Rx_OBJ_Data(void)
//{
//	//uint8_t buff[LEN_MSG_OBJ];
//	TX_RX_FRAME	Rx_obj;
//	uint8_t st_rx = 0;
//	uint8_t i = 0;

////	Rx_obj.d_struct.id_netw = ID_NETWORK;			// byte[0]
////	Rx_obj.d_struct.id_modul = ID_REMOTE_CNTRL;		// byte[1]
//	Rx_obj.d_struct.index = IND_obj_STATUS;			// byte[2:3]
////	
////	/* data byte[4:11] */
////	Rx_obj.d_struct.data[0] = 0x01;
////	Rx_obj.d_struct.data[1] = 0x01;
////	Rx_obj.d_struct.data[2] = 0x01;
////	Rx_obj.d_struct.data[3] = 0x00;
////	Rx_obj.d_struct.data[4] = 0x00;
////	Rx_obj.d_struct.data[5] = 0x00;
////	Rx_obj.d_struct.data[6] = 0x00;
////	Rx_obj.d_struct.data[7] = 0x00;
////	
////	Rx_obj.d_struct.crc = 0x0A;	
////	Rx_obj.byte[4] = usart_rx(&st_rx);
////	if(st_rx)
////	{
////		for(i = 5; i < LEN_MSG_OBJ; i++)
////		{
////			Rx_obj.byte[i] = usart_rx(&st_rx);
////		}
////	}
//	//Rx_obj.byte[i] = usart_rx(1);
//	//Data_to_OBJ(&Rx_obj);
//	
//	//buff[0] = usart_rx(1);
//	Rx_obj.d_struct.id_netw = usart_rx(&st_rx);
//	if(st_rx && (Rx_obj.d_struct.id_netw == ID_NETWORK))
//	{
//		st_rx = 0;
//		//buff[1] = usart_rx(1);

//		Rx_obj.d_struct.id_modul = usart_rx(&st_rx);

//		if(Rx_obj.d_struct.id_modul == ID_REMOTE_CNTRL)
//		{
//			
//			/* Read byte index, data, crc */
//			for(i = 2; i < LEN_MSG_OBJ; i++)
//			{
//				st_rx = 0;
//				while(!st_rx)
//				{
//					Rx_obj.byte[i] = usart_rx(&st_rx);
//				}
//			}
//			
//			/* check crc*/
//			if(Check_CRC(&Rx_obj))
//			{
//				/* check index */
//				Data_to_OBJ(&Rx_obj);
//				return 1;
//			}
//		}
//	}
//		
//	return 0;
//}

///* Receive Data Obj */
//uint8_t	Rx_OBJ_Data(void)
//{
//	//uint8_t buff[LEN_MSG_OBJ];
//	TX_RX_FRAME	Rx_obj;
//	uint8_t i = 0;

//	
//	st_rx = 0;
//	
////	Rx_obj.d_struct.id_netw = ID_NETWORK;			// byte[0]
////	Rx_obj.d_struct.id_modul = ID_REMOTE_CNTRL;		// byte[1]
//	Rx_obj.d_struct.index = IND_obj_STATUS;			// byte[2:3]
////	
////	/* data byte[4:11] */
////	Rx_obj.d_struct.data[0] = 0x01;
////	Rx_obj.d_struct.data[1] = 0x01;
////	Rx_obj.d_struct.data[2] = 0x01;
////	Rx_obj.d_struct.data[3] = 0x00;
////	Rx_obj.d_struct.data[4] = 0x00;
////	Rx_obj.d_struct.data[5] = 0x00;
////	Rx_obj.d_struct.data[6] = 0x00;
////	Rx_obj.d_struct.data[7] = 0x00;
////	
////	Rx_obj.d_struct.crc = 0x0A;	
////	Rx_obj.byte[4] = usart_rx(&st_rx);
////	if(st_rx)
////	{
////		for(i = 5; i < LEN_MSG_OBJ; i++)
////		{
////			Rx_obj.byte[i] = usart_rx(&st_rx);
////		}
////	}
//	//Rx_obj.byte[i] = usart_rx(1);
//	//Data_to_OBJ(&Rx_obj);
//	
//	//buff[0] = usart_rx(1);
//	Rx_obj.d_struct.id_netw = usart_rx(&st_rx);
//	if(st_rx && (Rx_obj.d_struct.id_netw == ID_NETWORK))
//	{
//		st_rx = 0;
//		//buff[1] = usart_rx(1);

//		Rx_obj.d_struct.id_modul = usart_rx(&st_rx);

//		if(Rx_obj.d_struct.id_modul == ID_REMOTE_CNTRL)
//		{
//			
//			/* Read byte index, data, crc */
//			for(i = 2; i < LEN_MSG_OBJ; i++)
//			{
//				st_rx = 0;
//				Rx_obj.byte[i] = usart_rx(&st_rx);
//			}
//			
//			/* check crc*/
//			if(Check_CRC(&Rx_obj))
//			{
//				/* check index */
//				Data_to_OBJ(&Rx_obj);
//				return 1;
//			}
//		}
//	}
//		
//	return 0;
//}



/* Receive Data Obj */
uint8_t	Rx_OBJ_Data(void)
{
	//uint8_t buff[LEN_MSG_OBJ];
	TX_RX_FRAME	Rx_obj;
	uint8_t i = 0;

	if(FLAG_RECEIVE & FLAG_RX_REMOTE_CTRL)
	{
		FLAG_RECEIVE &= ~FLAG_RX_REMOTE_CTRL;
		
		/* Read byte index, data, crc */
		for(i = 0; i < LEN_MSG_OBJ; i++)
		{
			Rx_obj.byte[i] = buff_rx[i];
		}
		
		Data_to_OBJ(&Rx_obj);
		
		/* check crc*/
		if(Check_CRC(&Rx_obj))
		{
			/* check index */
			Data_to_OBJ(&Rx_obj);
			return 1;
		}
	}
		
	return 0;
}



uint8_t Check_CRC(TX_RX_FRAME *Rx_obj_c)
{
	uint16_t calc_CRC = 0x0000;
	uint8_t i = 0;

	for(i = 0; i < (LEN_MSG_OBJ - LEN_CRC); i++)
	{
		calc_CRC += Rx_obj_c->byte[i];
	}
	
	return (Rx_obj_c->d_struct.crc == calc_CRC)? 1 : 0;
}

