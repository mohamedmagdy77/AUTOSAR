/******************************************************************************
 *
 * Module: Heat
 *
 * File Name: Heat.c
 *
 * Description: Source file for running light, heater, and fan of the microwave.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/
#include "Dio.h"
#include "Heat.h"

/*********************************************************************************************
*                            Toggles a led                                                   *
**********************************************************************************************/
void fan_on_off(uint8 level){
    Dio_WriteChannel(DioConf_FAN_CHANNEL_ID_INDEX, level);
}

void heater_on_off(uint8 level){
    Dio_WriteChannel(DioConf_HEATER_CHANNEL_ID_INDEX, level);
}

void light_on_off(uint8 level){
    Dio_WriteChannel(DioConf_LIGHT_CHANNEL_ID_INDEX, level);
}
  