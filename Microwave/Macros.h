/******************************************************************************
 *
 * Module: Macros
 *
 * File Name: Macros.h
 *
 * Description: Header file for macros that do bit operation on registers.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#ifndef MACROS_H
#define MACROS_H

/* Set a certain bit in a register */
#define SET_BIT(REG, BIT)     (REG|=(1<<BIT))

/* Clear a certain bit in a register */
#define CLEAR_BIT(REG, BIT)   (REG&=(~(1<<BIT)))

/* Toggle a certain bit in a register */
#define TOGGLE_BIT(REG, BIT)  (REG^=(1<<BIT))

/* Get a certain bit in a register */
#define GET_BIT(REG, BIT)     ((REG>>BIT) & 0X01)

/* convert a number from integer to character*/
#define INT_TO_CHAR(X) 		  (X+48)

/* convert a number from character to integer*/
#define CHAR_TO_INT(X) 		  (X-48)

#endif