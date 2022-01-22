 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Dio Driver
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#ifndef DIO_CFG_H
#define DIO_CFG_H

/*
 * Module Version 1.0.0
 */
#define DIO_CFG_SW_MAJOR_VERSION             (1U)
#define DIO_CFG_SW_MINOR_VERSION             (0U)
#define DIO_CFG_SW_PATCH_VERSION             (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define DIO_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/*******************************************************************************
 *                                  Configurations                             *
 *******************************************************************************/
/* Pre-compile option for Development Error Detect */
#define DIO_DEV_ERROR_DETECT                (STD_OFF)

/* Pre-compile option for Version Info API */
#define DIO_VERSION_INFO_API                (STD_ON)

/* Pre-compile option for presence of Dio_FlipChannel API */
#define DIO_FLIP_CHANNEL_API                (STD_ON)

/*******************************************************************************
 *                num of configured ports, chanells, and groups                *
 *******************************************************************************/
/* Number of the configured Dio Ports */
#define DIO_CONFIGURED_PORTS                 (1U)
   
/* Number of the configured Dio Channels */
#define DIO_CONFIGURED_CHANNLES              (9U)
   
/* Number of the configured Dio Groups */
#define DIO_CONFIGURED_GROUPS                (1U)

/*******************************************************************************
 *                           Ports Configurations                              *
 *******************************************************************************/
/* DIO Configured Port ID's  */
#define PORTA                                (Dio_PortType)0 /* PORTA */
#define PORTB                                (Dio_PortType)1 /* PORTB */
#define PORTC                                (Dio_PortType)2 /* PORTC */
#define PORTD                                (Dio_PortType)3 /* PORTD */
#define PORTE                                (Dio_PortType)4 /* PORTE */
#define PORTF                                (Dio_PortType)5 /* PORTF */

#define DioConf_KEYPAD_INDEX                 (Dio_PortType)0
#define DioConf_KEYPAD_PORT_NUM              (PORTC)

   
/*******************************************************************************
 *                           Channels Configurations                           *
 *******************************************************************************/
   
/* Channel Index in the array of structures in Dio_PBcfg.c */
  
#define DioConf_LCD_RS_CHANNEL_ID_INDEX      (uint8)0x00
#define DioConf_LCD_EN_CHANNEL_ID_INDEX      (uint8)0x01

#define DioConf_START_SW_CHANNEL_ID_INDEX    (uint8)0x02
#define DioConf_STOP_SW_CHANNEL_ID_INDEX     (uint8)0x03
#define DioConf_DOOR_SW_CHANNEL_ID_INDEX     (uint8)0x04
#define DioConf_WEIGHT_SW_CHANNEL_ID_INDEX   (uint8)0x05
#define DioConf_FAN_CHANNEL_ID_INDEX    	 (uint8)0x06
#define DioConf_HEATER_CHANNEL_ID_INDEX      (uint8)0x07
#define DioConf_LIGHT_CHANNEL_ID_INDEX       (uint8)0x08

/* DIO Configured Port ID's  */
#define DioConf_LCD_RS_PORT_NUM              (Dio_PortType)0 /* PORTA */
#define DioConf_LCD_EN_PORT_NUM              (Dio_PortType)0 /* PORTA */

#define DioConf_START_SW_PORT_NUM            (Dio_PortType)1 /* PORTB */
#define DioConf_STOP_SW_PORT_NUM             (Dio_PortType)1 /* PORTB */
#define DioConf_DOOR_SW_PORT_NUM             (Dio_PortType)1 /* PORTB */
#define DioConf_WEIGHT_SW_PORT_NUM           (Dio_PortType)1 /* PORTB */
#define DioConf_FAN_PORT_NUM                 (Dio_PortType)1 /* PORTB */
#define DioConf_HEATER_PORT_NUM              (Dio_PortType)1 /* PORTB */
#define DioConf_LIGHT_PORT_NUM               (Dio_PortType)1 /* PORTB */
   
/* DIO Configured Channel ID's */
#define DioConf_LCD_RS_CHANNEL_NUM           (Dio_ChannelType)4 /* PA4 */
#define DioConf_LCD_EN_CHANNEL_NUM           (Dio_ChannelType)5 /* PA5 */

#define DioConf_START_SW_CHANNEL_NUM         (Dio_ChannelType)0 /* PB0 */
#define DioConf_STOP_SW_CHANNEL_NUM          (Dio_ChannelType)1 /* PB1 */
#define DioConf_DOOR_SW_CHANNEL_NUM          (Dio_ChannelType)2 /* PB2 */
#define DioConf_WEIGHT_SW_CHANNEL_NUM        (Dio_ChannelType)3 /* PB3 */
#define DioConf_FAN_CHANNEL_NUM              (Dio_ChannelType)4 /* PB4 */
#define DioConf_HEATER_CHANNEL_NUM           (Dio_ChannelType)5 /* PB5 */
#define DioConf_LIGHT_CHANNEL_NUM            (Dio_ChannelType)6 /* PB6 */  
 
/*******************************************************************************
 *                           Groups Configurations                             *
 *******************************************************************************/
/* Group Index in the array of structures in Dio_PBcfg.c */
#define DioConf_LCD_GROUP_INDEX             (uint8)0x00
   
/* DIO Configured Group Channels ID's  */
#define DioConf_LCD_GROUP_PORT               (Dio_PortType)0 /* PORTA */
#define DioConf_LCD_GROUP_MASK               (uint8)0X0F     /* mask */
#define DioConf_LCD_GROUP_OFFSET             (uint8)0        /* offset */



#endif /* DIO_CFG_H */
