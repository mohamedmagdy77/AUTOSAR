/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.h
 *
 * Description: Header file for LCD Driver.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#ifndef LCD_H
#define LCD_H

#include "Std_Types.h"

void LCD_init(void);
void LCD_send_char(uint8 chr);
void LCD_send_char_xy(uint8 row,uint8 col, uint8 chr);
void LCD_send_string(uint8 row, uint8 col, sint8 *string);
void LCD_clear(void);
void LCD_set_cursor(uint8 row,uint8 col);

#endif