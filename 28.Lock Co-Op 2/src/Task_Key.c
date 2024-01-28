#include "Task_Key.h"

#include "kbd.h"
#include "task_Refresh.h"
#include "lpc17xx_gpio.h"

uint8_t keyCur=0;
uint8_t passEnter[3];
const   uint8_t MainPass[]={1,4,7};

uint8_t key;
void Task_Key(RunMail_Type runMail,uint8_t *paramsData)
{
  switch(Task_GetStepParam(paramsData))
  {
   case 0:
   {		 	
		 key=kbd_read();
		 Task_Delay_ms(50,1);
	 }break;
	 case 1:
	 {
		 uint8_t temp=kbd_read();
		 if(temp==16)
			 Task_Delay_ms(10,2);//On Release
		 else if(temp==key)
			 Task_Delay_ms(50,1);	
     else
			 Task_Delay_ms(10,0);	
	 }break;
	 case 2:
	 {
		 if(key<10)
		 {
			 ShowData_Segment(keyCur,key);
			 passEnter[keyCur]=key;
			 keyCur++;
			 if(keyCur==3)
				 keyCur=0;
		 }
		 else
		 {
			switch(key)
			{
				case 10:
				case 11:
				case 12:
				{
				
					
				}break;
				case 13:
				{
					uint8_t count;
					uint8_t correct=0;
					for(count=0;count<3;count++)
					{
						if(passEnter[count]==MainPass[count])
						  correct++;
					}
					if(correct==3)
					{
						//Pass is OK
						GPIO_SetValue(0,(1<<26));
						GPIO_ClearValue(2,(1<<12));
					}
					else
					{
						//Pass is wrong					
						GPIO_SetValue(2,(1<<12));
						GPIO_ClearValue(0,(1<<26));
					}
				}break;
				case 14:
				case 15:
				{
					
				}break;
		  }
	   }
		 Task_Delay_ms(100,0);
	 }break;
 }
}