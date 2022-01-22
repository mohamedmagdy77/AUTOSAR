/******************************************************************************
 * Module: Buttons
 *
 * File Name: Buttons.h
 *
 * Description: Header file to read Buttons.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#ifndef BUTTONS_H
#define BUTTONS_H

#include "Std_Types.h"

#define PRESSED 		(STD_LOW)
#define NOT_PRESSED 	(STD_HIGH)

uint8 read_start_sw(void);

uint8 read_stop_sw(void);

uint8 read_door_sw(void);

uint8 read_weight_sw(void);

#endif