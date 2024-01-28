#include "lpc17xx_gpio.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_nvic.h"

const uint8_t segmentTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void ADC_IRQHandler(void);

void DelayRefresh()
{
   for(uint32_t count=0;count<UINT16_MAX+40000;count++);  //6.4mS	    
}

uint16_t volatge,realTemp=0;
float    calcVolt;
uint32_t total=0;
uint8_t countOfSum=0;

volatile uint8_t flagOfTemp=0;

void ADC_IRQHandler()
{
	if(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_0,ADC_DATA_DONE)==0)
	{
		uint16_t temp;
		volatge=ADC_ChannelGetData(LPC_ADC,ADC_CHANNEL_0);
	/*
	 3        4096
	 x        volt
   x=volt*3/4096	
	*/
	
	calcVolt=(volatge*3.0F)/4096;
  temp=(calcVolt*100);
	
	total+=temp;
	countOfSum++;
		if(countOfSum==100)
		{
			countOfSum=0;
			realTemp=total/100;
			total=0;
			flagOfTemp=1;
		}
   ADC_StartCmd(LPC_ADC,ADC_START_NOW);
	}
	
}

int main()
{	
	uint16_t localTemp=0;
	PINSEL_CFG_Type adcpinsel;
	
	
	NVIC_SetPriorityGrouping(0x07);
	
	adcpinsel.Funcnum=PINSEL_FUNC_1;
	adcpinsel.OpenDrain=PINSEL_PINMODE_NORMAL;
	adcpinsel.Pinmode=PINSEL_PINMODE_TRISTATE;
	adcpinsel.Pinnum=23;
	adcpinsel.Portnum=0;
	
	PINSEL_ConfigPin(&adcpinsel);
	
	ADC_Init(LPC_ADC,200000);
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN0,ENABLE);
	ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_0,ENABLE);

	NVIC_SetPriority(ADC_IRQn,NVIC_EncodePriority(0x07,0,1));
  NVIC_EnableIRQ(ADC_IRQn);	

	/*---7 Segment Data---*/
	FIO_ByteSetDir(1,2,0xff,1);
	
	/*---7 Segment Digits---*/
	GPIO_SetDir(0,(1<<1),1);
	GPIO_SetDir(0,(1<<2),1);
	GPIO_SetDir(0,(1<<3),1);
	
	GPIO_SetDir(1,(1<<26),1);

   ADC_StartCmd(LPC_ADC,ADC_START_NOW);
while(1)
{		
  if(flagOfTemp)
	{
		flagOfTemp=0;
		localTemp=realTemp;
	}
	
		if(localTemp>40)
		{
			GPIO_SetValue(1,(1<<26));		
		}
		else
		{
			GPIO_ClearValue(1,(1<<26));
		}
  
	
  GPIO_ClearValue(0,(1<<2));
	GPIO_SetValue(0,(1<<1));
	FIO_ByteSetValue(1,2,segmentTable[localTemp/10]);
	FIO_ByteClearValue(1,2,~segmentTable[localTemp/10]);
	DelayRefresh();
	GPIO_ClearValue(0,(1<<1));
	GPIO_SetValue(0,(1<<2));
	FIO_ByteSetValue(1,2,segmentTable[localTemp%10]);
	FIO_ByteClearValue(1,2,~segmentTable[localTemp%10]);
	DelayRefresh();
}
	
}
