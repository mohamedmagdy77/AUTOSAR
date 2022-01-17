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
#include "Button.h"
#include "Led.h"
#include "Dio.h"
#include "Port.h"
#include "Co_Scheduler.h"
#include "my_keypad.h"
#include "lcd.h"


#define PASS_SIZE       (4)
STATIC uint8 real_pass[PASS_SIZE] = "1234";
STATIC uint8 pass[10];
STATIC uint8 pass_counter = 0;

/* Description: Task executes once to initialize all the Modules */
void Init_Task(void)
{
    /* Initialize all pins */
    Port_Init(&pins_config_structure);
    
    /* Initialize Dio Driver */
    Dio_Init(&Dio_Configuration);
    
    LCD_init();
    LCD_send_string(0, 0, "Enter Pass:");
    LCD_set_cursor(1, 0);
    
    SCH_Add_Task(read_pass, READ_PASS_DELAY, READ_PASS_PERIOD);
    SCH_Add_Task(Button_Task, Button_Task_DELAY, Button_Task_PERIOD);
    SCH_Add_Task(Led_Task,    Led_Task_DELAY   , Led_Task_PERIOD   );
    SCH_Add_Task(App_Task,    App_Task_DELAY   , App_Task_PERIOD   );
    
    /* you can delete tasks at run time*/
    /* SCH_Delete_Task(Led_Task_index);*/
}

/* Description: Task executes every 20 Mili-seconds to check the button state */
void Button_Task(void)
{
    BUTTON_refreshState();
}

/* Description: Task executes every 40 Mili-seconds to refresh the LED */
void Led_Task(void)
{
    LED_refreshOutput();
}

/* Description: Task executes every 60 Mili-seconds to get the button status and toggle the led */
void App_Task(void)
{
    static uint8 button_previous_state = BUTTON_RELEASED;
    static uint8 button_current_state  = BUTTON_RELEASED;
	
    button_current_state = BUTTON_getState(); /* Read the button state */
	
    /* Only Toggle the led in case the current state of the switch is pressed
     * and the previous state is released */ 
    if((button_current_state == BUTTON_PRESSED) && (button_previous_state == BUTTON_RELEASED))
    {
        LED_toggle();
    }
	
    button_previous_state = button_current_state;
}

/* Description:  Task executes every 100 Mili-seconds to get the password*/
void read_pass(void){
    uint8 val = keypadfind();
    if(NOT_PRESSED != val && val != 'c'){
        pass[pass_counter] = val;
        LCD_send_char('*');
        pass_counter++;
    }
    else if(val == 'c'){
		SCH_Add_Task(compare_pass, COMPARE_PASS_DELAY   , COMPARE_PASS_PERIOD   );
		SCH_Delete_Task(READ_PASS_INDEX);
    }
}

void compare_pass(void){
    uint8 counter;
    if(pass_counter != PASS_SIZE){
        LCD_clear();
        LCD_send_string(0, 0, "Wrong Password");
    }
    else{
        for(counter = 0; counter < pass_counter; counter++){
          if(pass[counter] != real_pass[counter]){
              LCD_clear();
              LCD_send_string(0, 0, "Wrong Password");
              return;
          }
        }
        LCD_clear();
        LCD_send_string(0, 0, "Right Password");
    }
    
}