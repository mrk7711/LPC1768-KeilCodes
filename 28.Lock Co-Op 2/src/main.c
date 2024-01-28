#include "TaskHandle.h"

#include "hardware.h"

#include "Task_Refresh.h"
#include "Task_Key.h"

int main()
{	
	HW_Init();
	
	Task_RegisterNew(Task_Refresh);
	Task_RegisterNew(Task_Key);
	
	Task_RunCoOperativeSystem();
	
}
