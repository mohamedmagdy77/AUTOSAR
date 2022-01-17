/******************************************************************************
 * Module: Co-operative Scheduler
 *
 * File Name: Co_Sheduler.c
 *
 * Description: Source file for Co-operative Scheduler.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

/*******************************************************************************
* NOTES to use this module                                                     *
* 1- modify the two static functions Timer_Init and Timer_Start if nedded      *
* 2- call SCH_IRQ in the used Timer ISR                                        *
********************************************************************************/

#include "Co_Scheduler.h"
#include "Gpt.h"


/* Task Control Block*/
sTask SCH_tasks_G[SCH_MAX_TASKS];

/* error variable*/
uint8 Error_code_G;

/* Keeps track of time since last error was recorded (see below)*/
volatile static uint32 Error_tick_count_G;

/* The code of the last error (reset after ~1 minute)*/
volatile static uint8 Last_error_code_G;


/*******************************************************************************
* modify only these two functions in case of:                                  *
* 1- you used different Timer                                                  *
* 2- you used different microcontroller                                        *
* modify SLEEP() for different microcontroller                                 *
* note: no need to change any thing else in Co_sheduler module                 *
********************************************************************************/
STATIC void Timer_Init(void ){
    SysTick_Init(OS_BASE_TIME);	/* 20 milli second interrupt.*/
}

STATIC void Timer_Start(void){
    SysTick_Start();            /* enable SysTick*/
}

/* sleep instruction*/
#define SLEEP() asm("WFI")

/*******************************************************************************
* Service Name: SCH_Init
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to reset the array of tasks,
*              and configure timer for periodic interrupt.
********************************************************************************/
void SCH_Init(void){
    uint8 i;
    /* reset TCB*/
    for (i = 0; i < SCH_MAX_TASKS; i++){
        SCH_Delete_Task(i);
    }
    /* Reset the global error variable*/
    /* - SCH_Delete_Task() will generate an error code,
       (because the task array is empty)*/
    Error_code_G = 0;
    /* The required SysTick Timer overflow is 0.02 seconds (20 ms)*/
    /* automatic reload available in SysTick Timer*/
    Timer_Init();
}

/*******************************************************************************
* Service Name: SHC_IRQ
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to reset the array of tasks,
*              and enable timer for periodic interrupt.
* Note: This function should be called in the Timer ISR
********************************************************************************/
void SHC_IRQ(void){
    uint8 index;
    for(index=0; index<SCH_MAX_TASKS; index++){
        if(SCH_tasks_G[index].pTask != NULL_PTR){
            if(SCH_tasks_G[index].Delay==0){
                SCH_tasks_G[index].RunMe++;
                if(SCH_tasks_G[index].Period){
                    SCH_tasks_G[index].Delay = SCH_tasks_G[index].Period;
                }
            }
            else{
                SCH_tasks_G[index].Delay -= 1;
            }
        }
    }
}

/*******************************************************************************
* Service Name: SCH_Add_Task
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): - pointer to task
*                  - delay before the first execution of the task
*                  - period between execution of the task
* Parameters (inout): None
* Parameters (out): None
* Return value: Index of the task in the array
* Description: Function to add tasks to the array SCH_tasks_G
********************************************************************************/
uint8 SCH_Add_Task(void (* pTask_fun)(void), uint32 Delay_fun, uint32 Period_fun){
    uint8 index=0;
    while((SCH_tasks_G[index].pTask != NULL_PTR) && (index<SCH_MAX_TASKS)){
        index++;
    }
    if(index == SCH_MAX_TASKS){
        Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
        return SCH_MAX_TASKS;
    }
    SCH_tasks_G[index].pTask = pTask_fun;
    SCH_tasks_G[index].Delay = Delay_fun;
    SCH_tasks_G[index].Period = Period_fun;
    SCH_tasks_G[index].RunMe = 0;
    return index;
}

/*******************************************************************************
* Service Name: SCH_Dispatch_Tasks
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to call the ready tasks from the array SCH_tasks_G
********************************************************************************/
void SCH_Dispatch_Tasks(void){
    uint8 index=0;
    while(1){
        for(index=0; index< SCH_MAX_TASKS; index++){
            if(SCH_tasks_G[index].RunMe > 0){
                if(SCH_tasks_G[index].pTask != NULL_PTR){
                    (*SCH_tasks_G[index].pTask)();
                    SCH_tasks_G[index].RunMe -= 1;
                }
                if(SCH_tasks_G[index].Period == 0){
                    SCH_Delete_Task(index);
                }
            }
        }
        SLEEP();
    }
}

/*******************************************************************************
* Service Name: SCH_Start
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to start the timer of the sheduler
********************************************************************************/
void SCH_Start(void){
    Timer_Start();
}

/*******************************************************************************
* Service Name: SCH_Delete_Task
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): task index in the array SCH_tasks_G
* Parameters (inout): None
* Parameters (out): None
* Return value: either normal or error 
* Description: Function to delaete TCB from SCH_tasks_G
********************************************************************************/
uint8 SCH_Delete_Task(const uint8 TASK_INDEX){
    uint8 Return_code;
    if(SCH_tasks_G[TASK_INDEX].pTask == NULL_PTR){
        Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
        Return_code = RETURN_ERROR;
    }
    else{
        Return_code = RETURN_NORMAL;
    }
    SCH_tasks_G[TASK_INDEX].pTask = NULL_PTR;
    SCH_tasks_G[TASK_INDEX].Delay = 0;
    SCH_tasks_G[TASK_INDEX].Period = 0;
    SCH_tasks_G[TASK_INDEX].RunMe = 0;
    return Return_code;
}

/*******************************************************************************
* Service Name: SCH_Report_Status
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None 
* Description: Function to report errors
********************************************************************************/
#if (SCH_REPORT_ERRORS == STD_ON)
void SCH_Report_Status(void){
    
}
#endif

