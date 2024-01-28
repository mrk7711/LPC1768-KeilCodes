#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_dac.h"
#include "lpc17xx_timer.h"

const uint16_t SinSamples[]=
{
	511,	669,	811,	924,	997,	1022,	997,	924,
	811,	669,	511,	353,	211,	98,	25,	0,	25,
	98,	211,	353,
};

uint8_t sampleCount=0;

//1/1000 =>20KHz ->1/20K=
void TIMER0_IRQHandler(void);

void TIMER0_IRQHandler()
{
	if(TIM_GetIntStatus(LPC_TIM0,TIM_MR0_INT))
	{
		TIM_ClearIntPending(LPC_TIM0,TIM_MR0_INT);
		DAC_UpdateValue(LPC_DAC,SinSamples[sampleCount]);
		sampleCount++;
		if(sampleCount==20)
			sampleCount=0;
		

		
	}
	
}

int main()
{	
	PINSEL_CFG_Type dacPinsel;
	TIM_TIMERCFG_Type timCfg;
	TIM_MATCHCFG_Type matCfg;
	
	timCfg.PrescaleOption=TIM_PRESCALE_USVAL;
	timCfg.PrescaleValue=1;
	
	TIM_Init(LPC_TIM0,TIM_TIMER_MODE,&timCfg);
	
	matCfg.ExtMatchOutputType=DISABLE;
	matCfg.IntOnMatch=ENABLE;
	matCfg.MatchChannel=0;
	matCfg.MatchValue=49;
	matCfg.ResetOnMatch=ENABLE;
	matCfg.StopOnMatch=DISABLE;
	
	TIM_ConfigMatch(LPC_TIM0,&matCfg);
	
	NVIC_EnableIRQ(TIMER0_IRQn);
	TIM_Cmd(LPC_TIM0,ENABLE);
	
	
	dacPinsel.Funcnum=PINSEL_FUNC_2;
	dacPinsel.OpenDrain=PINSEL_PINMODE_NORMAL;
	dacPinsel.Pinmode=PINSEL_PINMODE_TRISTATE;
	dacPinsel.Pinnum=26;
	dacPinsel.Portnum=0;
	
	PINSEL_ConfigPin(&dacPinsel);
	
	DAC_Init(LPC_DAC);
	
	
	while(1)
	{
		
		
	}
	
}
