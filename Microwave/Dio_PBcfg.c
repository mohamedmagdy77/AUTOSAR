 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Dio Driver
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#include "Dio.h"

/*
 * Module Version 1.0.0
 */
#define DIO_PBCFG_SW_MAJOR_VERSION              (1U)
#define DIO_PBCFG_SW_MINOR_VERSION              (0U)
#define DIO_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define DIO_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Dio_PBcfg.c and Dio.h files */
#if ((DIO_PBCFG_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((DIO_PBCFG_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION)\
 ||  (DIO_PBCFG_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION)\
 ||  (DIO_PBCFG_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/*******************************************************************************
 *                    PB structure used with Dio_Init API                      *
 *******************************************************************************/
const Dio_ConfigType Dio_Configuration = {
    /* ports initialization*/
    {DioConf_KEYPAD_PORT_NUM},
    
    /* chanells initialization*/
    {{DioConf_LCD_RS_PORT_NUM   , DioConf_LCD_RS_CHANNEL_NUM   },
     {DioConf_LCD_EN_PORT_NUM   , DioConf_LCD_EN_CHANNEL_NUM   },
     {DioConf_START_SW_PORT_NUM , DioConf_START_SW_CHANNEL_NUM },
	 {DioConf_STOP_SW_PORT_NUM  , DioConf_STOP_SW_CHANNEL_NUM  },
	 {DioConf_DOOR_SW_PORT_NUM  , DioConf_DOOR_SW_CHANNEL_NUM  },
	 {DioConf_WEIGHT_SW_PORT_NUM, DioConf_WEIGHT_SW_CHANNEL_NUM},
	 {DioConf_FAN_PORT_NUM      , DioConf_FAN_CHANNEL_NUM      },
	 {DioConf_HEATER_PORT_NUM   , DioConf_HEATER_CHANNEL_NUM   },
	 {DioConf_LIGHT_PORT_NUM    , DioConf_LIGHT_CHANNEL_NUM    },},
	
    /* group initialization*/  
    { {DioConf_LCD_GROUP_MASK, DioConf_LCD_GROUP_OFFSET, DioConf_LCD_GROUP_PORT} }
};








