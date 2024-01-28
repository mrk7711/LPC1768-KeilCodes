#include "Task_Refresh.h"


#include "lpc17xx_gpio.h"

const uint8_t segmentTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};


void Task_Refresh(RunMail_Type runMail,uint8_t *paramsData)
{
  switch(Task_GetStepParam(paramsData))
  {
   case 0:
   {		 	
		 GPIO_ClearValue(0,(1<<3));
		 GPIO_SetValue(0,(1<<1));
		 FIO_ByteSetValue(1,2,segmentTable[0]);
	   FIO_ByteClearValue(1,2,~segmentTable[0]);
		 Task_Delay_ms(8,1);
	 }break;
	 case 1:
	 {
		 GPIO_ClearValue(0,(1<<1));
	   GPIO_SetValue(0,(1<<2));
	   FIO_ByteSetValue(1,2,segmentTable[1]);
	   FIO_ByteClearValue(1,2,~segmentTable[1]);
	   Task_Delay_ms(8,2);
	 }break;
	 case 2:
	 {
		GPIO_ClearValue(0,(1<<2));
		GPIO_SetValue(0,(1<<3));
		FIO_ByteSetValue(1,2,segmentTable[2]);
		FIO_ByteClearValue(1,2,~segmentTable[2]);
		Task_Delay_ms(8,0);
	 }break;
 }	
}