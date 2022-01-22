/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Regs.h
 *
 * Description: Registers for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#ifndef PORT_REG_H
#define PORT_REG_H

#include "Std_Types.h"

/*******************************************************************************
 *                              Module Definitions                             *
 *******************************************************************************/

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C

typedef struct{
    uint32 DATA;
    uint32 DIR;
    uint32 IS;
    uint32 IBE;
    uint32 IEV;
    uint32 IM;
    uint32 RIS;
    uint32 MIS;
    uint32 ICR;
    uint32 AFSEL;
    uint32 Reserved1[55];
    uint32 DR2R;
    uint32 DR4R;
    uint32 DR8R;
    uint32 ODR;
    uint32 PUR;
    uint32 PDR;
    uint32 SLR;
    uint32 DEN;
    uint32 LOCK;
    uint32 CR;
    uint32 AMSEL;
    uint32 PCTL;
    uint32 ADCCTL;
    uint32 DMACTL;
}GPIO_TypeDef;
 
#define GPIOA ((GPIO_TypeDef*)0X400043FC)
#define GPIOB ((GPIO_TypeDef*)0X400053FC)
#define GPIOC ((GPIO_TypeDef*)0X400063FC)
#define GPIOD ((GPIO_TypeDef*)0X400073FC)
#define GPIOE ((GPIO_TypeDef*)0X400243FC)
#define GPIOF ((GPIO_TypeDef*)0X400253FC)

#define RCGCGPIO    (*((volatile uint32 *)0x400FE108))

#endif