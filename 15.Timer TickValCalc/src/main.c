#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_pinsel.h"

int main()
{	
 TIM_TIMERCFG_Type timCfg;
 TIM_MATCHCFG_Type mat0Cfg;
	PINSEL_CFG_Type  mat0PinSel;
	
 timCfg.PrescaleOption=TIM_PRESCALE_USVAL;
 timCfg.PrescaleValue=1000;
 
 TIM_Init(LPC_TIM1,TIM_TIMER_MODE,&timCfg);
	
	mat0Cfg.ExtMatchOutputType=TIM_EXTMATCH_TOGGLE;
	mat0Cfg.IntOnMatch=DISABLE;
	mat0Cfg.MatchChannel=0;
	mat0Cfg.MatchValue=10;
	mat0Cfg.ResetOnMatch=ENABLE;
	mat0Cfg.StopOnMatch=DISABLE;
	
	TIM_ConfigMatch(LPC_TIM1,&mat0Cfg);
	
	mat0PinSel.Funcnum=PINSEL_FUNC_3;
	mat0PinSel.OpenDrain=PINSEL_PINMODE_NORMAL;
	mat0PinSel.Pinmode=PINSEL_PINMODE_TRISTATE;
	mat0PinSel.Pinnum=22;
	mat0PinSel.Portnum=1;
	
	PINSEL_ConfigPin(&mat0PinSel);
	
	TIM_Cmd(LPC_TIM1,ENABLE);
	
while(1)
{
	
}
	
}
