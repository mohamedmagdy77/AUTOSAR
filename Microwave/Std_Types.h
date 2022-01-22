/******************************************************************************
 *
 * Module: Standard Types
 *
 * File Name: Std_Types.h
 *
 * Description: This document specifies the AUTOSAR standard types header file. 
 *				It contains all types that are used across several modules of the basic 
 *  			software and that are platform and compiler independent.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H

/* Vendor ID*/
#define STD_TYPES_VENDOR_ID		    (7891U)

/*
* Module version 1.0.0
*/
#define STD_TYPES_SW_MAJOR_VERSION 	1
#define STD_TYPES_SW_MINOR_VERSION 	0
#define STD_TYPES_SW_PATCH_VERSION 	0

/*
* AUTOSAR version 4.0.3
*/
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION 	4
#define STD_TYPES_AR_RELEASE_MINOR_VERSION 	0
#define STD_TYPES_AR_RELEASE_PATCH_VERSION 	3

#include "Compiler.h"
#include "Platform_Types.h"

#if((STD_TYPES_AR_RELEASE_VERSION_MAJOR != COMPILER_AR_RELEASE_VERSION_MAJOR)\
||  (STD_TYPES_AR_RELEASE_VERSION_MINOR != COMPILER_AR_RELEASE_VERSION_MINOR)\
||  (STD_TYPES_AR_RELEASE_VERSION_PATCH != COMPILER_AR_RELEASE_VERSION_PATCH))
	#error "Std_Types.h and Compiler.h AUTOSAR Versions are not compatiple"
#endif

#if((STD_TYPES_AR_RELEASE_VERSION_MAJOR != PLATFORM_TYPES_AR_RELEASE_VERSION_MAJOR)\
||	(STD_TYPES_AR_RELEASE_VERSION_MINOR != PLATFORM_TYPES_AR_RELEASE_VERSION_MINOR)\
||  (STD_TYPES_AR_RELEASE_VERSION_PATCH != PLATFORM_TYPES_AR_RELEASE_VERSION_PATCH))
	#error "Std_Types.h and Platform_Types.h AUTOSAR Versions are not compatiple"
#endif

/* This type can be used as standard API return type which is shared between 
*  the RTE and the BSW modules.*/
#define Std_ReturnType uint8

/* This type shall be used to request the version of a BSW module*/
typedef struct
{
	uint16 vendorID;
	uint16 moduleID;
	uint8 sw_major_version;
	uint8 sw_minor_version;
	uint8 sw_patch_version;
} Std_VersionInfoType;

#ifndef STATUSTYPEDEFINED
	#define STATUSTYPEDEFINED
	#define E_OK 	0x00
	typedef unsigned char StatusType; /* OSEK compliance */
#endif
#define E_NOT_OK 	0x01

#define STD_HIGH 	0x01 /* Physical state 5V or 3.3V */
#define STD_LOW 	0x00 /* Physical state 0V */

#define STD_ACTIVE 	0x01 /* Logical state active */
#define STD_IDLE 	0x00 /* Logical state idle */

#define STD_ON 		0x01
#define STD_OFF 	0x00



#endif /* STD_TYPES_H */