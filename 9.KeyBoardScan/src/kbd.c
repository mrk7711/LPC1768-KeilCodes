#include "KBD.h"

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"

void kbd_delay()
{
  uint8_t count;
	for(count=0;count<25;count++)
	  __ASM("NOP");
}

//Matrix Keyboard Functions
void kbd_init()
{
	PINSEL_CFG_Type pinConfig;
	
  pinConfig.Portnum=KBD_Port;
	pinConfig.Funcnum=PINSEL_FUNC_0;	
	pinConfig.OpenDrain=PINSEL_PINMODE_NORMAL;
	pinConfig.Pinmode=PINSEL_PINMODE_PULLUP;		
	
	
	pinConfig.Pinnum=PINSEL_PIN_0+(KBD_PIN_Part*8);
	PINSEL_ConfigPin(&pinConfig);	
	
	pinConfig.Pinnum=PINSEL_PIN_1+(KBD_PIN_Part*8);
	PINSEL_ConfigPin(&pinConfig);	
	
	pinConfig.Pinnum=PINSEL_PIN_2+(KBD_PIN_Part*8);
	PINSEL_ConfigPin(&pinConfig);	
	
	pinConfig.Pinnum=PINSEL_PIN_3+(KBD_PIN_Part*8);
	PINSEL_ConfigPin(&pinConfig);	

	GPIO_SetDir(KBD_Port,(1<<(0+(KBD_PIN_Part*8))) |
											 (1<<(1+(KBD_PIN_Part*8))) |
											 (1<<(2+(KBD_PIN_Part*8))) |
											 (1<<(3+(KBD_PIN_Part*8))) ,0);
											 
  GPIO_SetDir(KBD_Port,(1<<(4+(KBD_PIN_Part*8))) |
											 (1<<(5+(KBD_PIN_Part*8))) |
											 (1<<(6+(KBD_PIN_Part*8))) |
											 (1<<(7+(KBD_PIN_Part*8))) ,1);

}

static uint8_t kbd_get()
{
	uint8_t kbd_in;

	//scanning first row.
	FIO_ByteSetValue(KBD_Port,KBD_PIN_Part,0xE0);
	FIO_ByteClearValue(KBD_Port,KBD_PIN_Part,0x1F);
	kbd_delay();
	kbd_in=FIO_ByteReadValue(KBD_Port,KBD_PIN_Part) & 0x0F;

	if(kbd_in!=0x0F)
	{
	 switch(kbd_in)
	 {
		case 0x0E:return 0;
		case 0x0D:return 1;
		case 0x0B:return 2;
		case 0x07:return 3;
	 }  
	}

	//scanning second row.
	FIO_ByteSetValue(KBD_Port,KBD_PIN_Part,0xD0);
	FIO_ByteClearValue(KBD_Port,KBD_PIN_Part,0x2F);
	kbd_delay();
	kbd_in=FIO_ByteReadValue(KBD_Port,KBD_PIN_Part) & 0x0F;
	if(kbd_in!=0x0f)
	{
	 switch(kbd_in)
	 {
		case 0x0E:return 4;
		case 0x0D:return 5;
		case 0x0B:return 6;
		case 0x07:return 7;
	 }  
	}
	//scanning third row.
	FIO_ByteSetValue(KBD_Port,KBD_PIN_Part,0xB0);
	FIO_ByteClearValue(KBD_Port,KBD_PIN_Part,0x4F);
	kbd_delay();
	kbd_in=FIO_ByteReadValue(KBD_Port,KBD_PIN_Part) & 0x0F;
	if(kbd_in!=0x0F)
	{
	 switch(kbd_in)
	 {
		case 0x0E:return 8;
		case 0x0D:return 9;
		case 0x0B:return 10;
		case 0x07:return 11;
	 }  
	}
	
	//scanning fourth row.
	FIO_ByteSetValue(KBD_Port,KBD_PIN_Part,0x70);
	FIO_ByteClearValue(KBD_Port,KBD_PIN_Part,0x8F);
	kbd_delay();
	kbd_in=FIO_ByteReadValue(KBD_Port,KBD_PIN_Part) & 0x0F;
	if(kbd_in!=0x0F)
	{
	 switch(kbd_in)
	 {
		case 0x0E:return 12;
		case 0x0D:return 13;
		case 0x0B:return 14;
		case 0x07:return 15;
	 }  
	}
return 16;
} 

uint8_t kbd_read()
{
	uint8_t temp=kbd_get();
	FIO_ByteSetValue(KBD_Port,KBD_PIN_Part,0xF0);
  return temp;
}
