/*
 * uart.c
 *
 *  Created on: 2021-4-22
 *      Author: Administrator
 */

/*--------------------------------------------------------------------------------------
 *  Include
 *-------------------------------------------------------------------------------------*/
#include "sys/alt_irq.h"
#include <stdlib.h>
#include <stdio.h>
#include "../inc/uart_hmi.h"
#include "../inc/sopc.h"

/*--------------------------------------------------------------------------------------
 *  Function Prototype
 *------------------------------------------------------------------------------------*/
static int uart_send_byte(unsigned  char data);
static void uart_send_string(unsigned int len,unsigned char *str);
static int uart_init6(void);
static int set_baudrate(unsigned int baudrate);
/*--------------------------------------------------------------------------------------
 *  Struct initialize
 *------------------------------------------------------------------------------------*/
UART_HMI_T uart_hmi = {
	.send_byte = uart_send_byte,
	.send_string = uart_send_string,
	.init6 = uart_init6,
	.baudrate = set_baudrate,
	};

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  uart_send_byte
 *  Description:
 * =====================================================================================
 */
int uart_send_byte(unsigned char data)
{
	UART_HMI->TXDATA.BITS.TRANSMIT_DATA = data;
	while (!UART_HMI->STATUS.BITS.TRDY);

	return 0;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  uart_send_string
 *  Description:
 * =====================================================================================
 */
void uart_send_string(unsigned int len,unsigned  char *str)
{
	while (len--)
	{
		uart_send_byte(*str++);
	}
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  uart_init
 *  Description:
 * =====================================================================================
 */
int uart_init6(void)
{
	set_baudrate(115200);
	return 0;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  uart_hmi_change
 *  Description:
 * =====================================================================================
 */
void datachange(  char *change)
{
	uart_hmi.send_string(sizeof(change), change);
	UART_HMI->CONTROL.BITS.IRRDY = 1;
	UART_HMI->STATUS.WORD = 0;

}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  set_baudrate
 *  Description:
 * =====================================================================================
 */
int set_baudrate(unsigned int baudrate)
{
	UART_HMI->DIVISOR.WORD = (unsigned int)(ALT_CPU_FREQ / baudrate + 0.5);
	return 0;
}
