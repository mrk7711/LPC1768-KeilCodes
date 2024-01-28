#ifndef TaskHandle_H_
#define TaskHandle_H_

#include <stdint.h>

#define AvailableTask_Max       5

typedef enum
{
 RunMail_Type_Normal=0,
 RunMail_Type_Delay,
}RunMail_Type;

typedef enum
{
  TaskStatus_Type_Active,
  TaskStatus_Type_WaitForDelay,
}TaskStatus_Type;

typedef void (*TaskFunc_t)(RunMail_Type runMail,uint8_t *paramsData);
/*----------------Example Of Task:-----------------------
void App_Task1(RunMail_Type runMail,uint8_t *paramsData)
{
  switch(Task_GetStepParam(paramsData))
  {
   case 0:
   {
		.
		.
		.
		.

------------------------------------------------------*/

typedef struct
{
 TaskFunc_t      Function;
 uint16_t        Delay;
 TaskStatus_Type Status;
 uint8_t         StepOpt;
}Task_t;

uint8_t Task_RegisterNew(TaskFunc_t taskFunc);
void    Task_RunCoOperativeSystem(void);
uint8_t Task_GetStepParam(uint8_t *paramIn);
void    Task_SetNextStepParam(uint8_t nexStep);
void    Task_Delay_ms(uint16_t delms,uint8_t stp);

/*------------------Private Used-------------*/
void Task_IncTick(void);
void Task_TickInit(void);

#endif
