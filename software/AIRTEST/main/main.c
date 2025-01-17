#include "system.h"
#include "sys/alt_irq.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../driver/LQ12864.h"
#include "../driver/code.h"
#include "../inc/sopc.h"
#include "../inc/uart_co.h"
#include "../inc/uart_no2.h"
#include "../inc/uart_o3.h"
#include "../inc/uart_so2.h"
#include "../inc/uart_sds011.h"
#include "../inc/uart_hmi.h"


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:
 * =====================================================================================
 */
    unsigned  char temp[32];
    unsigned char endoff=0xFF;
    void UART_Send_END(void)
    {
    	uart_hmi.send_byte(endoff);
    	uart_hmi.send_byte(endoff);
    	uart_hmi.send_byte(endoff);
    }
int main(void)
{
	uart_hmi.init6();
	while(1)
	{
		    uart_so2.init();
			uart_co.init2();
			uart_no2.init3();
		    uart_o3.init4();
			uart_sds011.init5();
            UART_Send_END();
			sprintf(temp,"TEM.txt=\"%.2f\"\xFF\xFF\xFF", uart_so2.tem_DATA);
            uart_hmi.send_string(sizeof(temp),temp);
            UART_Send_END();

			sprintf(temp,"HUM.txt=\"%.2f \"\xFF\xFF\xFF", uart_so2.hum_DATA);
            uart_hmi.send_string(sizeof(temp),temp);
            UART_Send_END();

			sprintf(temp,"SO2.txt=\"%.3f\"\xFF\xFF\xFF", uart_so2.SO2_DATA);
            uart_hmi.send_string(sizeof(temp),temp);
            UART_Send_END();

			sprintf(temp,"CO.txt=\"%.3f\"\xFF\xFF\xFF", uart_co.CO_DATA);
            uart_hmi.send_string(sizeof(temp),temp);
            UART_Send_END();

		    sprintf(temp,"NO2.txt=\"%.3f\"\xFF\xFF\xFF", uart_no2.NO2_DATA);
            uart_hmi.send_string(sizeof(temp),temp);
            UART_Send_END();

			sprintf(temp,"O3.txt=\"%.3f\"\xFF\xFF\xFF", uart_o3.O3_DATA);
            uart_hmi.send_string(sizeof(temp),temp);
            UART_Send_END();

			sprintf(temp,"PM25.txt=\"%.2f\"\xFF\xFF\xFF", uart_sds011.pm25_DATA);
            uart_hmi.send_string(sizeof(temp),temp);
            UART_Send_END();

			sprintf(temp,"PM10.txt=\"%.2f\"\xFF\xFF\xFF", uart_sds011.pm10_DATA);
            uart_hmi.send_string(sizeof(temp),temp);
            UART_Send_END();

	}
	return 0;
}
