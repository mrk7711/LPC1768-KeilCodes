#include "Task_Key.h"

#include "kbd.h"

void Task_Key(RunMail_Type runMail,uint8_t *paramsData)
{
  switch(Task_GetStepParam(paramsData))
  {
   case 0:
   {		 	
		 kbd_read();
	 }break;
 }
}