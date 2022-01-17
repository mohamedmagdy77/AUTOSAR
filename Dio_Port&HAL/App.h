 /******************************************************************************
 *
 * Module: application
 *
 * File Name: App.h
 *
 * Description: Header file for Application Tasks.
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#ifndef APP_H_
#define APP_H_

#include "Std_Types.h"

/*******************************************************************************
*                                Task delays                                   *
********************************************************************************/
#define READ_PASS_DELAY      0
#define Button_Task_DELAY    0
#define Led_Task_DELAY       2
#define App_Task_DELAY       3
#define COMPARE_PASS_DELAY   0

/*******************************************************************************
*                                Task periods                                   *
********************************************************************************/
#define READ_PASS_PERIOD     5
#define Button_Task_PERIOD   1
#define Led_Task_PERIOD      2
#define App_Task_PERIOD      3
#define COMPARE_PASS_PERIOD  0

/*******************************************************************************
*                                Task indexes in TCB                           *
********************************************************************************/
#define READ_PASS_INDEX      0
#define Button_Task_INDEX    1
#define Led_Task_INDEX       2
#define App_Task_INDEX       3

/* Description: Task executes once to initialize all the Modules */
extern void Init_Task(void);

/* Description: Task executes every 20 Mili-seconds to check the button state */
extern void Button_Task(void);

/* Description: Task executes every 40 Mili-seconds to refresh the LED */
extern void Led_Task(void);

/* Description: Task executes every 60 Mili-seconds to get the button status and toggle the led */
extern void App_Task(void);

extern void read_pass(void);

extern void compare_pass(void);

#endif /* APP_H_ */
