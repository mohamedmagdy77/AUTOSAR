/******************************************************************************
 * Module: SysTick
 *
 * File Name: SysTick_Regs.h
 *
 * Description: Header file for SysTick registers.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#ifndef SYSTICK_REGS_H
#define SYSTICK_REGS_H

#include "Std_Types.h"

/*****************************************************************************
systic
*****************************************************************************/
#define SYST_CSR                  (*((volatile uint32 *)0xE000E010))
#define SYST_RVR                  (*((volatile uint32 *)0xE000E014))
#define SYST_CVR                  (*((volatile uint32 *)0xE000E018))
#define SYST_CALIB                (*((volatile uint32 *)0xE000E01C))

#endif