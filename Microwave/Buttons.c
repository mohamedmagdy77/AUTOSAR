/******************************************************************************
 * Module: Buttons
 *
 * File Name: Buttons.c
 *
 * Description: Source file to read Buttons.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#include "Buttons.h"
#include "Dio.h"

/* Reads Start Button and return it's state*/
uint8 read_start_sw(void){
	return Dio_ReadChannel(DioConf_START_SW_CHANNEL_ID_INDEX);
}

/* Reads Stop Button and return it's state*/
uint8 read_stop_sw(void){
	return Dio_ReadChannel(DioConf_STOP_SW_CHANNEL_ID_INDEX);
}

/* Reads Door state and return it's state*/
uint8 read_door_sw(void){
	return Dio_ReadChannel(DioConf_DOOR_SW_CHANNEL_ID_INDEX);
}

/* Reads if the food is inside or not and return it's state*/
uint8 read_weight_sw(void){
	return Dio_ReadChannel(DioConf_WEIGHT_SW_CHANNEL_ID_INDEX);
}
  
  
