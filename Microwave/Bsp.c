/******************************************************************************
 * Module: Baord Support Package
 *
 * File Name: Bsp.c
 *
 * Description: Source file for ISRs.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#include "Co_Scheduler.h"

/* SysTick Timer ISR*/
void SysTick_Handler(void)
{
	/* Function from the co-operative sheduler*/
    SHC_IRQ();
}