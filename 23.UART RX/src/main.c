#include <stdio.h>

#include "lpc17xx_gpio.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"

#include "hardware.h"
#include "Delay_RIT.h"

int main()
{	
	uint8_t  buffStr[50];
	HW_Init();
	
	while(1)
	{
		uint8_t  dataPrt[3];
		uint16_t temp=HW_ADC_Read();
		uint8_t len=sprintf((char*)buffStr,"Hello.Temp is %u\n",temp);				
		UART_Send(LPC_UART0,buffStr,len,BLOCKING);
		
		UART_Receive(LPC_UART0,dataPrt,3,BLOCKING);
		
		if(dataPrt[0]==0xAA && dataPrt[1]==1 && dataPrt[2]==0xbb)
		{
			UART_Send(LPC_UART0,"\nLamp ON OK\n",12,BLOCKING);		
		}
		else if(dataPrt[0]==0xAA && dataPrt[1]==2 && dataPrt[2]==0xbb)
		{
			UART_Send(LPC_UART0,"\nLamp OFF OK\n",13,BLOCKING);			
		}
		else
		{
			UART_Send(LPC_UART0,"\nUnknown\n",9,BLOCKING);						
		}
		
		
		
//		if(((LPC_UART0->LSR)>>0)&0x01)
//		{
//			//Data Is Ready
//			/*--------------------*/
//			/*|Header|Command|END|*/
//			/*  0xAA |   1   | 0xbb  Lamp On
//			    0xAA |   2   | 0xbb  Lamp Off
//			/*--------------------*/
//			uint8_t data=UART_ReceiveByte(LPC_UART0);
//			if(data=='a' || data=='A')
//			{
//				UART_Send(LPC_UART0,"\nOK\n",4,BLOCKING);
//			}			
//		}		
				
		Delay_RIT_ms(1000);		
	}
	
}
