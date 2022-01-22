 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.h
 *
 * Description: Post build Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Dio.h files */
#if ((DIO_PBCFG_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION)\
 ||  (DIO_PBCFG_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION)\
 ||  (DIO_PBCFG_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION))
  #error "The SW version of Port_PBcfg.c does not match the expected version"
#endif

/* Post build structure used with Port_Init API */
const Port_ConfigType pins_config_structure = {
    PORTA, PIN0, OUTPUT, OFF    , STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTA PIN0: 17*/
    PORTA, PIN1, OUTPUT, OFF    , STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTA PIN1: 18*/
    PORTA, PIN2, OUTPUT, OFF    , STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTA PIN2: 19*/
    PORTA, PIN3, OUTPUT, OFF    , STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTA PIN3: 20*/
    PORTA, PIN4, OUTPUT, OFF, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTA PIN4: 21*/
    PORTA, PIN5, OUTPUT, OFF    , STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTA PIN5: 22*/
                                                                        
    PORTB, PIN0, INPUT , PULL_UP, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTB PIN0: 29*/
    PORTB, PIN1, INPUT , PULL_UP, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTB PIN1: 30*/
    PORTB, PIN2, INPUT , PULL_UP, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTB PIN2: 33*/
    PORTB, PIN3, INPUT , PULL_UP, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTB PIN3: 34*/
    PORTB, PIN4, OUTPUT, OFF, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTB PIN4: 44*/
    PORTB, PIN5, OUTPUT, OFF, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTB PIN5: 43*/
    PORTB, PIN6, OUTPUT, OFF, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTB PIN6: 42*/
    PORTB, PIN7, INPUT , OFF, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTA PIN7: 41*/
                                                                        
    PORTC, PIN0, OUTPUT, OFF, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTC PIN0: 40*/
    PORTC, PIN1, OUTPUT, OFF, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTC PIN1: 39*/
    PORTC, PIN2, OUTPUT, OFF, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTC PIN2: 38*/
    PORTC, PIN3, OUTPUT, OFF, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTC PIN3: 37*/
    PORTC, PIN4, INPUT, PULL_UP, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTC PIN4: 14*/
    PORTC, PIN5, INPUT, PULL_UP, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTC PIN5: 13*/
    PORTC, PIN6, INPUT, PULL_UP, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTC PIN6: 12*/
    PORTC, PIN7, INPUT, PULL_UP, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTA PIN7: 11*/
                                                                        
    PORTD, PIN0, INPUT, OFF, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTD PIN0: 25*/
    PORTD, PIN1, INPUT, OFF, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTD PIN1: 26*/
    PORTD, PIN2, INPUT, OFF, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTD PIN2: 27*/
    PORTD, PIN3, INPUT, OFF, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTD PIN3: 28*/
                                                                        
    PORTE, PIN0, INPUT, OFF, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTE PIN0: 35*/
    PORTE, PIN1, INPUT, OFF, STD_LOW, GPIO, DIR_CHANGEABLE, MODE_CHANGEABLE,          /* PORTE PIN1: 36*/
};
   
































   
   