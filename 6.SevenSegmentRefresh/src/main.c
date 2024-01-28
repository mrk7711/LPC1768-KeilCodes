#include "lpc17xx_gpio.h"

const uint8_t segmentTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};


void Delay()
{
   for(uint16_t count=0;count<UINT16_MAX;count++)
	    for(uint8_t count2=0;count2<0;count2++)
	     {
				 
			 }
}

int main()
{	
	uint8_t myNum=0,countOfDelay=0;
	
	FIO_ByteSetDir(1,2,0xFF,1);
	GPIO_SetDir(0,(1<<1)|(1<<2)|(1<<3),1);
	
	
		
while(1)
{		
	GPIO_ClearValue(0,(1<<3));
	GPIO_SetValue(0,(1<<1));
	FIO_ByteSetValue(1,2,segmentTable[myNum]);
	FIO_ByteClearValue(1,2,~segmentTable[myNum]);
	Delay();
	GPIO_ClearValue(0,(1<<1));
	GPIO_SetValue(0,(1<<2));
	FIO_ByteSetValue(1,2,segmentTable[1]);
	FIO_ByteClearValue(1,2,~segmentTable[1]);
	Delay();
	GPIO_ClearValue(0,(1<<2));
	GPIO_SetValue(0,(1<<3));
	FIO_ByteSetValue(1,2,segmentTable[2]);
	FIO_ByteClearValue(1,2,~segmentTable[2]);
	Delay();
	
	countOfDelay++;
	if(countOfDelay==30)
	{
		countOfDelay=0;
		myNum++;
		if(myNum==10)
			myNum=0;
	}

}
	
}
