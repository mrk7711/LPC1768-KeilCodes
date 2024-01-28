#include "lpc17xx_gpio.h"
#include "lpc17xx_nvic.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_exti.h"

const uint8_t segmentTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

uint8_t countOfkey=0;

void DelayRefresh()
{
   for(uint32_t count=0;count<UINT16_MAX+40000;count++);  //6.4mS	    
}

void EINT1_IRQHandler(void);
void EINT3_IRQHandler(void);

void EINT1_IRQHandler()
{
	EXTI_ClearEXTIFlag(EXTI_EINT1);
	countOfkey++;

}

void EINT3_IRQHandler()
{
	if(GPIO_GetIntStatus(2,12,1))
	{
		GPIO_ClearInt(2,(1<<12));
    countOfkey--;		
	}
}


int main()
{	
	PINSEL_CFG_Type  exti1CFG;
	EXTI_InitTypeDef extiConfig;
	
	NVIC_SetPriorityGrouping(0x07);
	
	exti1CFG.Funcnum=PINSEL_FUNC_1;
	exti1CFG.OpenDrain=PINSEL_PINMODE_NORMAL;
	exti1CFG.Pinmode=PINSEL_PINMODE_PULLUP;
	exti1CFG.Pinnum=11;
	exti1CFG.Portnum=2;
	
	PINSEL_ConfigPin(&exti1CFG);
	
	GPIO_SetDir(2,(1<<11),0);
	
	extiConfig.EXTI_Line=EXTI_EINT1;
	extiConfig.EXTI_Mode=EXTI_MODE_EDGE_SENSITIVE;
	extiConfig.EXTI_polarity=EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE;
	
	EXTI_Config(&extiConfig);
	
	NVIC_SetPriority(EINT1_IRQn,NVIC_EncodePriority(0x07,0,1));
	NVIC_EnableIRQ(EINT1_IRQn);
	
	GPIO_IntCmd(2,(1<<12),1);
	NVIC_EnableIRQ(EINT3_IRQn);
	
	
	/*---7 Segment Data---*/
	FIO_ByteSetDir(1,2,0xff,1);
	
	/*---7 Segment Digits---*/
	GPIO_SetDir(0,(1<<1),1);
	GPIO_SetDir(0,(1<<2),1);
	GPIO_SetDir(0,(1<<3),1);
	
while(1)
{			
		
  GPIO_ClearValue(0,(1<<3));
	GPIO_SetValue(0,(1<<1));
	FIO_ByteSetValue(1,2,segmentTable[countOfkey]);
	FIO_ByteClearValue(1,2,~segmentTable[countOfkey]);
	DelayRefresh();
	GPIO_ClearValue(0,(1<<1));
	GPIO_SetValue(0,(1<<2));
	FIO_ByteSetValue(1,2,segmentTable[0]);
	FIO_ByteClearValue(1,2,~segmentTable[0]);
	DelayRefresh();
	GPIO_ClearValue(0,(1<<2));
	GPIO_SetValue(0,(1<<3));
	FIO_ByteSetValue(1,2,segmentTable[0]);
	FIO_ByteClearValue(1,2,~segmentTable[0]);
	DelayRefresh();	
}
	
}
