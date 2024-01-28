#include "lpc17xx_gpio.h"

#include "kbd.h"

const uint8_t segmentTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void DelayRefresh()
{
   for(uint32_t count=0;count<UINT16_MAX+40000;count++);  //6.4mS	    
}

int main()
{	
	uint8_t keyShowP1=0,keyShowP2=0,countOfDelay=0;
	
	/*---7 Segment Data---*/
	FIO_ByteSetDir(1,2,0xff,1);
	
	/*---7 Segment Digits---*/
	GPIO_SetDir(0,(1<<1),1);
	GPIO_SetDir(0,(1<<2),1);
	GPIO_SetDir(0,(1<<3),1);
	
	kbd_init();
	
	GPIO_SetValue(0,(1<<1));
	
	
while(1)
{			
	countOfDelay++;
	if(countOfDelay==35)
	{
		uint8_t myKey;
		countOfDelay=0;
	  myKey=kbd_read();
	  if(myKey!=16)
	  {
  		//Key Pressed
	  	keyShowP2=myKey%10;
  		keyShowP1=myKey/10;		
  	}
  }
	
  GPIO_ClearValue(0,(1<<3));
	GPIO_SetValue(0,(1<<1));
	FIO_ByteSetValue(1,2,segmentTable[keyShowP1]);
	FIO_ByteClearValue(1,2,~segmentTable[keyShowP1]);
	DelayRefresh();
	GPIO_ClearValue(0,(1<<1));
	GPIO_SetValue(0,(1<<2));
	FIO_ByteSetValue(1,2,segmentTable[keyShowP2]);
	FIO_ByteClearValue(1,2,~segmentTable[keyShowP2]);
	DelayRefresh();
	GPIO_ClearValue(0,(1<<2));
	GPIO_SetValue(0,(1<<3));
	FIO_ByteSetValue(1,2,segmentTable[0]);
	FIO_ByteClearValue(1,2,~segmentTable[0]);
	DelayRefresh();	
}
	
}
