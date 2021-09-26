/*
 * uart.h
 *
 *  Created on: 2021-4-22
 *      Author: Administrator
 */

#ifndef UART_CO_H_
#define UART_CO_H_

/*-----------------------------------------------------------------------------
 *  Include
 *-----------------------------------------------------------------------------*/
#include "../inc/sopc.h"

/*-----------------------------------------------------------------------------
 *  Define
 *-----------------------------------------------------------------------------*/
#define BUFFER_SIZE 200

/*------------------------------------------------------------------------------
 *  Struct
 *-----------------------------------------------------------------------------*/
typedef struct{
	 float CO_DATA;
	unsigned int receive_flag;
	unsigned int receive_count;
	unsigned char receive_buffer[BUFFER_SIZE];
	int (* send_byte)(unsigned char data);
	void (* send_string)(unsigned int len, unsigned char *str);
	int (* init2)(void);
	unsigned int (* baudrate)(unsigned int baudrate);
}UART_CO_T;

extern UART_CO_T uart_co;	//����Ϊ�ⲿ��������ȫ��ʹ��




#endif /* UART_H_ */