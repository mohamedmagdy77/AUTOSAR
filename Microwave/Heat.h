/******************************************************************************
 *
 * Module: Heat
 *
 * File Name: Heat.h
 *
 * Description: Header file for running light, heater, and fan of the microwave.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/
#ifndef HEAT_H
#define HEAT_H

#include "Std_Types.h"

void fan_on_off(uint8 level);

void heater_on_off(uint8 level);

void light_on_off(uint8 level);

#endif