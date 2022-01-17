/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION           (1U)
#define PORT_CFG_SW_MINOR_VERSION           (0U)
#define PORT_CFG_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * number of pins in microcontroller
 */
#define MICROCONTROLLER_PINS_NUM            (28)   
   
/*******************************************************************************
*           switch ON/OFF evelopment Error Detection, and optional API's       *
********************************************************************************/

/* Switches the Development Error Detection and Notification on or off*/
#define PORT_DEV_ERROR_DETECT          (STD_ON)

/* enable / disable the use of the function Port_SetPinDirection()*/
#define PORT_SET_PIN_DIRECTION_API     (STD_ON)

/* enable / disable the use of the function Port_SetPinMode()*/
#define PORT_SET_PIN_MODE_API           (STD_ON)

/* enable / disable the API to read out the modules version information*/
#define PORT_VERSION_INFO_API           (STD_ON)


#endif