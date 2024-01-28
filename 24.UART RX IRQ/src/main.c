#include <stdio.h>

#include "lpc17xx_gpio.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"

#include "hardware.h"
#include "Delay_RIT.h"

/*--------------------------------------
  |Header|Command| END  |
  | 0xAA |   1   | 0xbb |  Lamp On
	|	0xAA |   2   | 0xbb |  Lamp Off
/-------------------------------------*/

uint8_t header_rx=0;
uint8_t command_rx,commandFlag=0;

void UART_IntReceive(void)
{
	uint8_t data=UART_ReceiveByte(LPC_UART0);
	if(header_rx==0 && data==0xAA)
	{
		header_rx=1;
	}
	else
	{
	  if(commandFlag==0 && header_rx==1)
	  { 
		  //Command
		  command_rx=data;
      commandFlag=1;		
 	  }
		else
		{	
			if(commandFlag==1)
			{
				if(data==0xBB)
				{
					header_rx=0;
					commandFlag=0;
					
					UART_Send(LPC_UART0,"\nOK\n",4,BLOCKING);			
				}		
			}
		}
}
	
	
	
	
	
	
}


int main()
{	
	uint8_t  buffStr[50];
	HW_Init();
	
	while(1)
	{
		uint16_t temp=HW_ADC_Read();
		uint8_t len=sprintf((char*)buffStr,"Hello.Temp is %u\n",temp);				
		UART_Send(LPC_UART0,buffStr,len,BLOCKING);
	

		Delay_RIT_ms(1000);		
	}
	
}
