#include "lpc17xx_gpio.h"

const uint8_t segmentTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};


void Delay()
{
   for(uint16_t count=0;count<UINT16_MAX;count++)
	    for(uint8_t count2=0;count2<150;count2++)
	     {
				 
			 }
}


void DelayLow()
{
   for(uint16_t count=0;count<UINT16_MAX;count++)
	    for(uint8_t count2=0;count2<20;count2++)
	     {
				 
			 }
}

int main()
{	
	uint8_t pushCount=0;
	
	/*---7 Segment Data---*/
	FIO_ByteSetDir(1,2,0xff,1);
	
	/*---7 Segment Digits---*/
	GPIO_SetDir(0,(1<<1),1);
	GPIO_SetDir(0,(1<<2),1);
	GPIO_SetDir(0,(1<<3),1);
	
	/*---Key ---*/
	GPIO_SetDir(2,(1<<11),0);
 
	
	GPIO_SetValue(0,(1<<1));
	
while(1)
{		
	uint32_t temp=GPIO_ReadValue(2);
	if(((temp>>11)&0x01)==0)
	{
		//Key Pressed
		uint8_t countOfTrue=0;
		for(uint8_t count=0;count<10;count++)
		{
			if(((GPIO_ReadValue(2)>>11)&0x01)==0)
			  countOfTrue++;
			DelayLow();
		}
		if(countOfTrue==10)
		{
			//Key is OK
			pushCount++;
		  if(pushCount==10)
   			pushCount=0;
		  FIO_ByteSetValue(1,2,segmentTable[pushCount]);
		  FIO_ByteClearValue(1,2,~segmentTable[pushCount]);		
		
		  while(((GPIO_ReadValue(2)>>11)&0x01)==0);
		}
		
	}

}
	
}
