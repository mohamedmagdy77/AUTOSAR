/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.c
 *
 * Description: Source file for LCD Driver.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#include "lcd.h"
#include "delay.h"
#include "Dio.h"

/* no operation for one clock*/
#define NOP() asm("NOP")

/* send commands to LCD to control it's state*/
STATIC void send_cmd(uint8 cmd){
	/* send High nibble first*/
    Dio_WriteChannelGroup(&Dio_Configuration.Groups[DioConf_LCD_GROUP_INDEX], cmd>>4);
    Dio_WriteChannel(DioConf_LCD_RS_CHANNEL_ID_INDEX, STD_LOW);
    Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_HIGH);
    NOP();
    Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_LOW);
    Delay_ms(1);
    
	/* send Low nibble second*/
    Dio_WriteChannelGroup(&Dio_Configuration.Groups[DioConf_LCD_GROUP_INDEX], cmd & 0x0F);
    Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_HIGH);
    NOP();
    Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_LOW);
    Delay_ms(1);
}

/* Initializes LCD state*/
void LCD_init(void){
    Delay_ms(15);
    send_cmd(0x02);     /* display and cursor home*/
    send_cmd(0x28);     /* 2_line mode , 5*7 mode*/
    send_cmd(0x01);     /* clear display*/
    
    send_cmd(0x0c);     /*display on & cursor underline and blink off*/
    send_cmd(0x14);     /* Display / Cursor shift*/
    send_cmd(0x06);		/* Charachter Entry mode*/
    send_cmd(0X80);		/* Set Display address*/
}

/* send character to LCD to current cursor location*/
void LCD_send_char(uint8 chr){
    Dio_WriteChannelGroup(&Dio_Configuration.Groups[DioConf_LCD_GROUP_INDEX], chr>>4);
    Dio_WriteChannel(DioConf_LCD_RS_CHANNEL_ID_INDEX, STD_HIGH);
    Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_HIGH);
    NOP();
    Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_LOW);
    Delay_ms(1);
    
    Dio_WriteChannelGroup(&Dio_Configuration.Groups[DioConf_LCD_GROUP_INDEX], chr & 0x0F);
    Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_HIGH);
    NOP();
    Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_LOW);
    Delay_ms(1);
}

/* send character to LCD to specific cursor location*/
void LCD_send_char_xy(uint8 row,uint8 col, uint8 chr){
	uint8 loc;
    if(row==0){
        loc = 0x80 | (col & 0x0F);
        send_cmd(loc);
    }
    else if(row==1){
        loc = 0xc0 | (col & 0x0F);
        send_cmd(loc);        
    }
	
    Dio_WriteChannelGroup(&Dio_Configuration.Groups[DioConf_LCD_GROUP_INDEX], chr>>4);
    Dio_WriteChannel(DioConf_LCD_RS_CHANNEL_ID_INDEX, STD_HIGH);
    Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_HIGH);
    NOP();
    Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_LOW);
    Delay_ms(1);
    
    Dio_WriteChannelGroup(&Dio_Configuration.Groups[DioConf_LCD_GROUP_INDEX], chr & 0x0F);
    Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_HIGH);
    NOP();
    Dio_WriteChannel(DioConf_LCD_EN_CHANNEL_ID_INDEX, STD_LOW);
    Delay_ms(1);
}

/* send string to LCD to specific cursor location*/
void LCD_send_string(uint8 row,uint8 col, sint8 *string){
    uint8 loc;
    if(row==0){
        loc = 0x80 | (col & 0x0F);
        send_cmd(loc);
    }
    else if(row==1){
        loc = 0xc0 | (col & 0x0F);
        send_cmd(loc);        
    }
    while((*string) != '\0'){
        LCD_send_char(*string);
        string++;
    }
}

/* Clears LCD screen*/
void LCD_clear(void){
    send_cmd(0x01);
}

/* sets LCD cursor on a specific location*/
void LCD_set_cursor(uint8 row,uint8 col){
    uint8 loc;
    if(row==0){
        loc = 0x80 | (col & 0x0F);
        send_cmd(loc);
    }
    else if(row==1){
        loc = 0xc0 | (col & 0x0F);
        send_cmd(loc);        
    }
}
