/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Mohamed Magdy's ID = 7891U :) */
#define PORT_VENDOR_ID    (7891U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)


#include "Macros.h"
#include "Std_Types.h"

#if( PORT_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION\
  || PORT_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION\
  || PORT_AR_RELEASE_PATCH_VERSION != STD_TYPES_AR_RELEASE_PATCH_VERSION)
#error "The Port AR version and Std_Types AR version are not compatible"
#endif
   
#include "Port_Cfg.h"
   
#if( PORT_AR_RELEASE_MAJOR_VERSION != PORT_CFG_AR_RELEASE_MAJOR_VERSION\
  || PORT_AR_RELEASE_MINOR_VERSION != PORT_CFG_AR_RELEASE_MINOR_VERSION\
  || PORT_AR_RELEASE_PATCH_VERSION != PORT_CFG_AR_RELEASE_PATCH_VERSION)
#error "The Port AR version and Port_Cfg AR version are not compatible"
#endif
   
#if( PORT_SW_MAJOR_VERSION != PORT_CFG_SW_MAJOR_VERSION\
  || PORT_SW_MINOR_VERSION != PORT_CFG_SW_MINOR_VERSION\
  || PORT_SW_PATCH_VERSION != PORT_CFG_SW_PATCH_VERSION)
#error "The Port SW version and Port_Cfg SW version are not compatible"
#endif

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/*
 * Description: direction and mode states PIN
 */
#define DIR_CHANGEABLE      0X01
#define DIR_UNCHANGEABLE    0X00

#define MODE_CHANGEABLE     0X01
#define MODE_UNCHANGEABLE   0X00
   
/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
#define PORT_E_PARAM_PIN                    0x0A
#define PORT_E_DIRECTION_UNCHANGEABLE       0x0B
#define PORT_E_PARAM_CONFIG                 0x0C
#define PORT_E_PARAM_INVALID_MODE           0x0D
#define PORT_E_MODE_UNCHANGEABLE            0x0E
#define PORT_E_UNINIT                       0x0F
#define PORT_E_PARAM_POINTER                0x10

   
/*******************************************************************************
*                               Unlock and commit                              *
********************************************************************************/
#define UNLOCK_VALUE    (0x4C4F434B)
#define PD7_COMMIT      (1<<PIN7)
#define PF0_COMMIT      (1<<PIN0)

/*******************************************************************************
*                               Module API ID's                                *
********************************************************************************/

/* Service ID of Port Init*/
#define PORT_INIT_SID                   0x00
   
/* Service ID of Port Set Pin Direction*/
#define PORT_SETPINDIRECTION_SID        0x01
   
/* Service ID of Port Set pin direction*/
#define PORT_REFRESHPORTDIRECTION_SID   0x02

/* Service ID of Port get version info*/
#define PORT_GET_VERSION_INFO_SID       0x03

/* Service ID of Port get version info*/
#define PORT_SETMODE_SID                0x04
   
   
/*******************************************************************************
*                               Module Data Types                              *
********************************************************************************/

/* Data type for the symbolic name of a port pin*/
typedef uint8 Port_PinType;

/* Description: Enum to hold PIN direction*/
typedef enum
{
    INPUT,
    OUTPUT
}Port_PinDirectionType;

/* Different port pin modes*/
typedef uint8 Port_PinModeType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,
    PULL_UP,
    PULL_DOWN
}Port_InternalResistor;


/*******************************************************************************
*                               Mode Types                                     *
********************************************************************************/
#define GPIO        (Port_PinModeType)0
#define UART        (Port_PinModeType)1  
#define UART1       (Port_PinModeType)2
#define SSI         (Port_PinModeType)2
#define I2C         (Port_PinModeType)3
#define CAN0        (Port_PinModeType)3
#define M0_PWM      (Port_PinModeType)4
#define M0_FAULT0   (Port_PinModeType)4
#define M1_PWM      (Port_PinModeType)5
#define M1_FAULT0   (Port_PinModeType)5
#define IDX         (Port_PinModeType)6
#define PHA         (Port_PinModeType)6
#define PHB         (Port_PinModeType)6
#define TXCCP       (Port_PinModeType)7
#define WTXCCP      (Port_PinModeType)7   
#define CAN         (Port_PinModeType)8
#define USB         (Port_PinModeType)8   
#define NMI         (Port_PinModeType)8
#define CO          (Port_PinModeType)9
#define TR          (Port_PinModeType)14
#define ADC         (Port_PinModeType)15

/*******************************************************************************
*                               Port ID's                                      *
********************************************************************************/
#ifndef PORTA
#define PORTA  (Port_PinType)0
#endif

#ifndef PORTB
#define PORTB  (Port_PinType)1
#endif

#ifndef PORTC
#define PORTC  (Port_PinType)2
#endif

#ifndef PORTD
#define PORTD  (Port_PinType)3
#endif

#ifndef PORTE
#define PORTE  (Port_PinType)4
#endif

#ifndef PORTF
#define PORTF  (Port_PinType)5
#endif

/*******************************************************************************
*                               Pin ID's                                      *
********************************************************************************/
#define PIN0  (uint8)0
#define PIN1  (uint8)1
#define PIN2  (uint8)2
#define PIN3  (uint8)3
#define PIN4  (uint8)4
#define PIN5  (uint8)5
#define PIN6  (uint8)6
#define PIN7  (uint8)7

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to --> 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *  3. the direction of pin --> INPUT or OUTPUT
 *  4. the internal resistor --> Disable, Pull up or Pull down
 *  5. the initial value on the pin --> HIGH or LOW
 *  6. the mode of the pin --> ADC, CAN, PWM...
 *  7. direction state of the pin --> changeable or not
 *  8. mode state of the pin --> changeable or not
 */
typedef struct 
{
    Port_PinType port_num;
    uint8 pin_num; 
    Port_PinDirectionType direction;
    Port_InternalResistor resistor;
    uint8 initial_value;
    Port_PinModeType mode;
    uint8 direction_state;
    uint8 mode_state;
}Pin_ConfigType;

/*
 * structure to configure all the pins in the microcontroller
 */
typedef struct 
{
    Pin_ConfigType Ports[MICROCONTROLLER_PINS_NUM];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Initializes the Port Driver module*/
void Port_Init( const Port_ConfigType* ConfigPtr );

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/* Sets the port pin direction*/
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif

/* Refreshes port direction*/
void Port_RefreshPortDirection( void );

#if (PORT_VERSION_INFO_API == STD_ON)
/* Returns the version information of this module*/
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/* Sets the port pin mode*/
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
#endif

/* Post build structure used with Port_Init API*/
extern const Port_ConfigType pins_config_structure;


#endif /* PORT_H */
