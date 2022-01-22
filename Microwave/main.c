/******************************************************************************
 * Module: main
 *
 * File Name: main.c
 *
 * Description: Source file for main code.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#include "App.h"
#include "Co_Scheduler.h"

/* Enable Interrupts */
#define Enable_Interrupts()    asm("CPSIE I")

/* Disable Interrupts */
#define Disable_Interrupts()   asm("CPSID I")

int main(void)
{
    /* Global Interrupts Enable */
    Enable_Interrupts();
    
	/* initialize sheduler */
    SCH_Init();

    /* Execute the Init Task */
    Init_Task();
    
    /* Start sheduler */
    SCH_Start();

    /* Scheduling ready Tasks */
    SCH_Dispatch_Tasks();
}
