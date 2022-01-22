/******************************************************************************
 * Module: SysTick
 *
 * File Name: SysTick.h
 *
 * Description: Header file for SysTick Timer.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#ifndef SYSTICK_H
#define SYSTICK_H

#include "Std_Types.h"

#define SYSTICK_CLK 3000000U

void SysTickInit(uint32 time_ms);
void SysTickStart(void);
void SysTickStop(void);
uint32 SysTickFlag(void);

#endif
