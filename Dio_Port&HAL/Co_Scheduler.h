/******************************************************************************
 * Module: Co-operative Scheduler
 *
 * File Name: Co_Sheduler.h
 *
 * Description: header file for Co-operative Scheduler.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#ifndef CO_SHEDULER_H
#define	CO_SHEDULER_H

#include "std_types.h"


/*******************************************************************************
*                           Configurations                                     *
********************************************************************************/
/* system ticks*/
#define OS_BASE_TIME  (20)

/* The maximum number of tasks required at any one time
   during the execution of the program
   MUST BE ADJUSTED FOR EACH NEW PROJECT*/
#define SCH_MAX_TASKS (5)

/* enables (STD_ON) or disables (STD_OFF) error reporting*/
#define SCH_REPORT_ERRORS STD_OFF

/*******************************************************************************
*                           Error Codes                                        *
********************************************************************************/
#define ERROR_SCH_TOO_MANY_TASKS 0
#define ERROR_SCH_CANNOT_DELETE_TASK 0
#define RETURN_ERROR 0
#define RETURN_NORMAL 1

/*******************************************************************************
*                           TCB elements                                       *
********************************************************************************/
typedef struct{
    /* Pointer to the task (must be a 'void (void)' function)*/
    void (* pTask)(void);
    /* Delay (ticks) until the function will (next) be run*/
    /* - see SCH_Add_Task() for further details*/
    uint32 Delay;
    /* Interval (ticks) between subsequent runs*/
    /* - see SCH_Add_Task() for further details*/
    uint32 Period;
    /* Incremented (by scheduler) when task is due to execute*/
    uint8 RunMe;
}sTask;

/*******************************************************************************
*                           Function declarations                              *
********************************************************************************/

void SCH_Init(void);

uint8 SCH_Add_Task(void (* pTask_fun)(void), uint32 Delay_fun, uint32 Period_fun);

void SHC_IRQ(void);

void SCH_Dispatch_Tasks(void);

void SCH_Start(void);

uint8 SCH_Delete_Task(const uint8 TASK_INDEX);


#endif	/* CO_SHEDULER_H */
