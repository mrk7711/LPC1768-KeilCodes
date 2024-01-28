#include "lpc17xx_gpio.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"

#include "hardware.h"
#include "Delay_RIT.h"

int main()
{	
	HW_Init();
	
	
	while(1)
	{
		uint16_t temp=HW_ADC_Read();
		//Send
		
		Delay_RIT_ms(1000);		
	}
	
}
