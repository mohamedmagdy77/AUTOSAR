/******************************************************************************
 *
 * Module: Platform Types
 *
 * File Name: Platform_Types.h
 *
 * Description: Header file that contains all platform dependent types and symbols.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/* Vendor ID*/
#define STD_TYPES_VENDOR_ID		    (7891U)

/*
* Module version 1.0.0
*/
#define PLATFORM_TYPES_SW_VERSION_MAJOR 	1
#define PLATFORM_TYPES_SW_VERSION_MINOR 	0
#define PLATFORM_TYPES_SW_VERSION_PATCH 	0

/*
* AUTOSAR version 4.0.3
*/
#define PLATFORM_TYPES_AR_REALEASE_MAJOR_VERSION 	4
#define PLATFORM_TYPES_AR_REALEASE_MINOR_VERSION 	0
#define PLATFORM_TYPES_AR_REALEASE_PATCH_VERSION 	3

#ifndef TRUE
  #define TRUE 				1
#endif
#ifndef FALSE
  #define FALSE 			0
#endif
	
#define boolean				unsigned char
	
#define uint8		    	unsigned char
#define uint16		    	unsigned short
#define uint32		    	unsigned long
#define uint64		    	unsigned long long
#define sint8		    	signed char
#define sint16		    	signed short
#define sint32		    	signed long
#define sint64		    	signed long long
	
#define uint8_least			unsigned long
#define uint16_least    	unsigned long
#define uint32_least    	unsigned long
#define sint8_least     	signed long
#define sint16_least    	signed long
#define sint32_least    	signed long
	
#define float32				float
#define float64				double
	
#define CPU_TYPE_8			8
#define CPU_TYPE_16			16
#define CPU_TYPE_32			32
	
#define MSB_FIRST			0
#define LSB_FIRST			1
	
#define HIGH_BYTE_FIRST		0
#define LOW_BYTE_FIRST		1

#define CPU_TYPE			CPU_TYPE_32	
#define CPU_BIT_ORDER 		LSB_FIRST
#define CPU_BYTE_ORDER		LOW_BYTE_FIRST

#define SYS_CLK				(3000000U)


#endif