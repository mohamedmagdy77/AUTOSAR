/******************************************************************************
 *
 * Module: keypad
 *
 * File Name: my_keypad.h
 *
 * Description: Header file for keypad Driver.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#include "my_keypad.h"

/*
 * first four pins connected with row >
									  >
									  >
									  >
 * second four pins connected with column ^ ^ ^ ^
*/


STATIC uint8 col_pos, row_pos;
/* the shape of the keypad*/
STATIC uint8 keypad[ROW][COLUMN] = {{'7','8','9','/'}
                                   ,{'4','5','6','*'}
                                   ,{'1','2','3','-'}
                                   ,{'c','0','=','+'}};


uint8 keypadfind(void){
    Dio_WritePort(KEYPAD_INDEX, 0xFF);
    Dio_WritePort(KEYPAD_INDEX, 0xF0);
    col_pos = Dio_ReadPort(KEYPAD_INDEX);
#if (KEYPAD_BLOCKING == STD_ON)
    while(col_pos == 0xF0){
        col_pos = Dio_ReadPort(KEYPAD_INDEX);
    }
#endif
   if(col_pos != 0xF0)
   {
        Dio_WritePort(KEYPAD_INDEX, 0xFF);
        Dio_WritePort(KEYPAD_INDEX, 0xFE);
		row_pos = Dio_ReadPort(KEYPAD_INDEX);
		if(row_pos != 0xFE){
			row_pos = 0;
			while(Dio_ReadPort(KEYPAD_INDEX) != 0xFE){}
			goto label;
		}
        
        Dio_WritePort(KEYPAD_INDEX, 0xFD);
		row_pos = Dio_ReadPort(KEYPAD_INDEX);
        //Delay_ms(5000);
		if(row_pos != 0xFD){
			row_pos = 1;
			while(Dio_ReadPort(KEYPAD_INDEX) != 0xFD){} 
			goto label;
		}
        
        Dio_WritePort(KEYPAD_INDEX, 0xFB);
		row_pos = Dio_ReadPort(KEYPAD_INDEX);
		if(row_pos != 0xFB){
			row_pos = 2;
			while(Dio_ReadPort(KEYPAD_INDEX) != 0xFB){} 
			goto label;
		}
        
        Dio_WritePort(KEYPAD_INDEX, 0xF7);
		row_pos = Dio_ReadPort(KEYPAD_INDEX);
		if(row_pos != 0xF7){
			row_pos = 3;
			while(Dio_ReadPort(KEYPAD_INDEX) != 0xF7){}  
			goto label;
		}
		label:
		switch(col_pos){
			case 0xE0:
				col_pos = 0;
				break;
			case 0xD0:
				col_pos = 1;
				break;
			case 0xB0:
				col_pos = 2;
				break;
			case 0x70:
				col_pos = 3;
				break;
		}
		return keypad[row_pos][col_pos];
	}
	return NOT_PRESSED;
}
