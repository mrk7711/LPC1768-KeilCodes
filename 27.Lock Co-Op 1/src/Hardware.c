#include "Hardware.h"

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"

#include "kbd.h"

void HW_Init()
{
	/*---7 Segment Data---*/
	FIO_ByteSetDir(1,2,0xff,1);
	
	/*---7 Segment Digits---*/
	GPIO_SetDir(0,(1<<1),1);
	GPIO_SetDir(0,(1<<2),1);
	GPIO_SetDir(0,(1<<3),1);
	
	kbd_init();
}
