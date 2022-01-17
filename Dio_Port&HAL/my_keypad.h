/******************************************************************************
 *
 * Module: keypad
 *
 * File Name: my_keypad.c
 *
 * Description: Source file for keypad Driver.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#ifndef MY_KEYPAD_H
#define	MY_KEYPAD_H

#include "Dio_Regs.h"
#include "Std_Types.h"
#include "Dio.h"

/**
* - 1 makes keypadfind function blocks the system until a button is pressed.
* - 0 checks if a button is pressed, if not it returns "NOT_PRESSED".
*/
#define KEYPAD_BLOCKING  STD_OFF
#define NOT_PRESSED      STD_LOW
#define ROW				 4
#define COLUMN			 4

#define write_port GPIO_PORTC_DATA_REG
#define read_port  GPIO_PORTC_DATA_REG

uint8 keypadfind(void);


#endif	/* MY_KEYPAD_H */

