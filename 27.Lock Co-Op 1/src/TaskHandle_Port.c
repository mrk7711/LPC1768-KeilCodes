#include "TaskHandle_Port.h"

#include "TaskHandle.h"
#include "lpc17xx_systick.h"

void Task_TickInit(void)
{
	//Initialize System Tick with 1ms time interval
	SYSTICK_InternalInit(1);
	//Enable System Tick interrupt
	SYSTICK_IntCmd(ENABLE);
	//Enable System Tick Counter
	SYSTICK_Cmd(ENABLE);
}

void SysTick_Handler(void)
{ 
	SYSTICK_ClearCounterFlag();
  Task_IncTick();
}
