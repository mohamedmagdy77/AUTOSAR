 /******************************************************************************
 *
 * Module: Application
 *
 * File Name: App.c
 *
 * Description: Source file for Application Tasks.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#include "App.h"
#include "Heat.h"
#include "Buttons.h"
#include "Dio.h"
#include "Port.h"
#include "Co_Scheduler.h"
#include "my_keypad.h"
#include "lcd.h"
#include "delay.h"
#include "Macros.h"

STATIC uint8 time_loc_LCD[6] = {0, 1, 3, 4, 6, 7};
STATIC uint8 time_setting[6];
STATIC uint32 time_setting_sec;
uint8 StopButton_State = NOT_PRESSED;

/* Description: Task executes once to initialize all the Modules */
void Init_Task(void)
{
    /* Initialize all pins */
    Port_Init(&pins_config_structure);
    
    /* Initialize Dio Driver */
    Dio_Init(&Dio_Configuration);
    
    LCD_init();
    LCD_send_string(0, 0, "Time Settings:");
    LCD_send_string(1, 0, "**:**:** ");
    
    SCH_Add_Task(ReadTime_Task, READ_TIME_DELAY, READ_TIME_PERIOD);
}


/* Description: Task executes after setting the time every 100 Milli seconds */
void StartHeating_Task(void)
{
	if(read_door_sw() == PRESSED && read_weight_sw() == PRESSED && read_start_sw() == PRESSED){
		LCD_send_string(0, 0, "Timer:          ");
		SCH_Add_Task(Counting_Task, Counting_Task_DELAY, Counting_Task_PERIOD);
		fan_on_off(STD_ON);
		heater_on_off(STD_ON);
		light_on_off(STD_ON);
	}
}

/* Description: Task cheks stop button every 100 Milli seconds */
void StopButton_Task(void){
	StopButton_State = read_stop_sw();
	if(StopButton_State == PRESSED){
		StopHeating();
	}
}

/* Description: Reserts time settings and stops heating */
void StopHeating(void)
{
	uint8 i;
	fan_on_off(STD_OFF);
	heater_on_off(STD_OFF);
	light_on_off(STD_OFF);
	SCH_Stop();
	
	if(StopButton_State == NOT_PRESSED){
		for (i = 0; i < 3; i++){
			LCD_clear();
			Delay_ms(400);
			LCD_send_string(0, 0, "Time Ended");
			Delay_ms(400);
		}
	}
	
	for (i = 0; i < SCH_MAX_TASKS; i++){
        SCH_Delete_Task(i);
    }
	
	LCD_clear();
	LCD_send_string(0, 0, "Time Settings:");
    LCD_send_string(1, 0, "**:**:** ");
    
	SCH_Add_Task(ReadTime_Task, READ_TIME_DELAY, READ_TIME_PERIOD);
	SCH_Start();
}

/* Description: refreshing time on LCD every second*/
void Counting_Task(void){
	time_setting_sec--;
	uint8 i;
	uint32 temp = time_setting_sec;
	time_setting[0] = temp/36000;
	temp = temp%36000;
	time_setting[1] = temp/3600;
	temp = temp%3600;
	time_setting[2] = temp/600;
	temp = temp%600;
	time_setting[3] = temp/60;
	temp = temp%60;
	time_setting[4] = temp/10;
	temp = temp%10;
	time_setting[5] = temp;
	for(i=0; i<6; i++){
		LCD_send_char_xy(SETTING_TIME_LOC, time_loc_LCD[i], INT_TO_CHAR(time_setting[i]));
	}
	if(time_setting_sec <= 0){
		Delay_ms(1000);
		StopHeating();
	}
}

/* Description:  Task executes every 100 Mili-seconds to get the time*/
void ReadTime_Task(void){
	STATIC uint8 count = 0;
    uint8 val = keypadfind();
    if(NO_INPUT != val){
        time_setting[count] = CHAR_TO_INT(val);
        LCD_send_char_xy(SETTING_TIME_LOC, time_loc_LCD[count], val);
		count++;
    }
    if(count == 6){
		time_setting_sec = time_setting[0]*36000 + time_setting[1]*3600 + time_setting[2]*600 +
						   time_setting[3]*60 + time_setting[4]*10 + time_setting[5];
		SCH_Add_Task(StartHeating_Task, StartHeating_Task_DELAY, StartHeating_Task_PERIOD);
		SCH_Add_Task(StopButton_Task,    StopButton_Task_DELAY   , StopButton_Task_PERIOD   );
		SCH_Delete_Task(READ_TIME_INDEX);
		count = 0;
    }
}

