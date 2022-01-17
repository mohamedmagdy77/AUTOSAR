 /******************************************************************************
 *
 * Module: Os
 *
 * File Name: Os.c
 *
 * Description: Source file for Os Scheduler.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#include "Os.h"
#include "App.h"
#include "Button.h"
#include "Led.h"
#include "Co_Scheduler.h"
#include "Gpt.h"

/* Enable IRQ Interrupts ... This Macro enables IRQ interrupts by clearing the I-bit in the PRIMASK. */
#define Enable_Interrupts()    asm("CPSIE I")

/* Disable IRQ Interrupts ... This Macro disables IRQ interrupts by setting the I-bit in the PRIMASK. */
#define Disable_Interrupts()   asm("CPSID I")


/*******************************************************************************
* Service Name: Os_start
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: calles inside main.
********************************************************************************/
void Os_start(void)
{
    /* Global Interrupts Enable */
    Enable_Interrupts();
    
    /* 
     * Set the Call Back function to call SHC_IRQ function
     * this function will be called every SysTick Interrupt (20ms)
     */
    SysTick_SetCallBack(SHC_IRQ);
    
    SCH_Init();

    /* Execute the Init Task */
    Init_Task();
    
    /* Start SysTickTimer to generate interrupt every 20ms */
    SCH_Start();

    /* Start the Os Scheduler */
    SCH_Dispatch_Tasks();
}


