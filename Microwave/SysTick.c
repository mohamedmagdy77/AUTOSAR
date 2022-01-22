/******************************************************************************
 * Module: SysTick
 *
 * File Name: SysTick.c
 *
 * Description: Source file for SysTick Timer.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#include "SysTick_Regs.h"
#include "SysTick.h"

void SysTickInit(uint32 time_ms){
    SYST_CSR  = 0;       /* restart the control status register, and stop SysTick timer*/
    SYST_CVR  = 0;       /* restart the systick current value*/
    SYST_RVR  = 0;       /* restart the systick reload value*/
    SYST_CSR |= 0x06;    /* use internal processor clock to drive the SysTick*/
    uint32 tmr_reload_value = time_ms*(SYSTICK_CLK/1000U);
    if( tmr_reload_value < 0x00FFFFFFU ){
        SYST_RVR = tmr_reload_value-1U;
    }
}

void SysTickStart(void){
    SYST_CSR |= 0x01;    /* start the SysTick timer*/
}

void SysTickStop(void){
    SYST_CSR &= ~0x01;    /* stop the SysTick timer*/
}

inline uint32 SysTickFlag(void){
    return (SYST_CSR&0x10000);
}
