/******************************************************************************
 * Module: bare metal
 *
 * File Name: startup.c
 *
 * Description: This file contains an interrupt vector for Cortex-M written in C.
 * The actual interrupt functions must be provided by the application developer.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#include "std_types.h"

#define SRAM_START  0x20000000U
#define SRAM_SIZE   (1024U * 4U)
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE))

#define STACK_START SRAM_END

/* Enable interupts */
#define EnableInterrupts() asm("CPSIE i")

/* Disable interupts */
#define DisableInterrupts() asm("CPSID i")

extern uint32 _ebss;
extern uint32 _edata;
extern uint32 _etext;
extern uint32 _sbss;
extern uint32 _sdata;

int main(void);

void Default_Handler( void );
void Reset_Handler( void );

void __attribute__ ((weak, alias ("Default_Handler"))) NMI_Handler( void ) 		  ;
void __attribute__ ((weak, alias ("Default_Handler"))) HardFault_Handler( void )  ;
void __attribute__ ((weak, alias ("Default_Handler"))) MemManage_Handler( void )  ;
void __attribute__ ((weak, alias ("Default_Handler"))) BusFault_Handler( void )   ;
void __attribute__ ((weak, alias ("Default_Handler"))) UsageFault_Handler( void ) ;
void __attribute__ ((weak, alias ("Default_Handler"))) SVC_Handler( void )        ;
void __attribute__ ((weak, alias ("Default_Handler"))) DebugMon_Handler( void )   ;
void __attribute__ ((weak, alias ("Default_Handler"))) PendSV_Handler( void )     ;
void __attribute__ ((weak, alias ("Default_Handler"))) SysTick_Handler( void )    ;



/** 
* For lm3s328 microcontroller.
* The vector table is normally located at address 0.
* When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
* If you need to define interrupt service routines,
* make a copy of this file and include it in your project.
* If vector table is not located at address 0, the user has to initialize
* the  NVIC vector table register (VTOR) before using interrupts.
*/


uint32 vector_table[] __attribute__ ((section (".isr_vector"))) =
{
  (uint32)STACK_START,			   /*0  */
  (uint32)&Reset_Handler,            /*1  */
  (uint32)&NMI_Handler,              /*2  */
  (uint32)&HardFault_Handler ,       /*3  */
  (uint32)&MemManage_Handler ,       /*4  */
  (uint32)&BusFault_Handler  ,       /*5  */
  (uint32)&UsageFault_Handler ,      /*6  */
  0,                                   /*7  */
  0,                                   /*8  */
  0,                                   /*9  */
  0,                                   /*10 */
  (uint32)&SVC_Handler       ,       /*11 */
  (uint32)&DebugMon_Handler  ,       /*12 */
  0,                                 /*13 */
  (uint32)&PendSV_Handler    ,       /*14 */
  (uint32)&SysTick_Handler   ,       /*15 */
  0,                                   /*16 */
  0,                                   /*17 */
  0,                                   /*18 */
  0,                                   /*19 */
  0,                                   /*20 */
  0,                                   /*21 */
  0,                                   /*22 */
  0,                                   /*23 */
  0,                                   /*24 */
  0,                                   /*25 */
  0,                                   /*26 */
  0,                                   /*27 */
  0,                                   /*28 */
  0,                                   /*29 */
  0,                                   /*30 */
  0,                                   /*31 */
  0,                                   /*32 */
  0,                                   /*33 */
  0,                                   /*34 */
  0,                                   /*35 */
  0,                                   /*36 */
  0,                                   /*37 */
  0,                                   /*38 */
  0,                                   /*39 */
  0,                                   /*40 */
  0,                                   /*41 */
  0,                                   /*42 */
  0,                                   /*43 */
  0,                                   /*44 */
  0                                    /*45 */
};

/********************************************************************************
*                                     Default Handler                           *
*********************************************************************************/
void Default_Handler( void ){
	while(1){
		
	}
}

/********************************************************************************
*                                     Reset Handler                             *
*********************************************************************************/
void Reset_Handler( void ){
	/* Disable interupts */
	DisableInterrupts();
	
	uint32 i;
	/* size of data section*/
	uint32 size = (uint32)&_edata - (uint32)&_sdata;
	/* destination of data section*/
	uint8 *pDst = (uint8*)&_sdata;
	/* source of data section*/
	uint8 *pSrc = (uint8*)&_etext;
	/* copy data section from Flash to RAM*/
	for(i=0; i<size; i++){
		*pDst++ = *pSrc++;
	}
	
	/* size of bss section*/
	size = (uint32)&_ebss - (uint32)&_sbss;
	/* destination of bss section*/
	pDst = (uint8*)&_sbss;
	/* initialize bss section to zeros*/
	for(i=0; i<size; i++){
		*pDst++ = 0;
	}
	/* Enable interupts */
	EnableInterrupts();
	
	/* call main*/
	main();
}


