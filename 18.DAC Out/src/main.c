#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_dac.h"

#include "Delay_RIT.h"

int main()
{	
	PINSEL_CFG_Type dacPinsel;
	
	dacPinsel.Funcnum=PINSEL_FUNC_2;
	dacPinsel.OpenDrain=PINSEL_PINMODE_NORMAL;
	dacPinsel.Pinmode=PINSEL_PINMODE_TRISTATE;
	dacPinsel.Pinnum=26;
	dacPinsel.Portnum=0;
	
	PINSEL_ConfigPin(&dacPinsel);
	
	DAC_Init(LPC_DAC);
	
	DAC_UpdateValue(LPC_DAC,1023);
	
	
	while(1)
	{
		
		
	}
	
}
