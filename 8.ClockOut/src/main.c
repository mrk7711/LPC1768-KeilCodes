#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"


int main()
{	
  PINSEL_CFG_Type clkoutConfig;

  clkoutConfig.Funcnum=PINSEL_FUNC_1;
  clkoutConfig.OpenDrain=PINSEL_PINMODE_NORMAL;
  clkoutConfig.Pinmode=PINSEL_PINMODE_TRISTATE;
  clkoutConfig.Pinnum=PINSEL_PIN_27;
  clkoutConfig.Portnum=PINSEL_PORT_1;
	
	PINSEL_ConfigPin(&clkoutConfig);
while(1)
{		


}
	
}
