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
	uint8_t  bufferTest[6]="Salam";
	HW_Init();
	
	
	while(1)
	{
		uint16_t temp=HW_ADC_Read();
		uint8_t len=sprintf((char*)buffStr,"Hello,Im a logger Machine.Temp is %u\n",temp);
				
		UART_Send(LPC_UART0,buffStr,len,BLOCKING);
		//Send
//		UART_SendByte(LPC_UART0,(temp>>8));
//		
//		while(UART_CheckBusy(LPC_UART0));
//		
//		UART_SendByte(LPC_UART0,temp);
//		
		Delay_RIT_ms(1000);		
	}
	
}
