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

#ifndef APP_H
#define APP_H

#include "Std_Types.h"

#define SETTING_TIME_LOC 1

/*******************************************************************************
*                                Task delays                                   *
********************************************************************************/
#define READ_TIME_DELAY            0
#define StartHeating_Task_DELAY    1
#define StopButton_Task_DELAY      2
#define Counting_Task_DELAY		   50

/*******************************************************************************
*                                Task periods                                   *
********************************************************************************/
#define READ_TIME_PERIOD           5
#define StartHeating_Task_PERIOD   5
#define StopButton_Task_PERIOD     5
#define Counting_Task_PERIOD	   50

/*******************************************************************************
*                                Task indexes in TCB                           *
********************************************************************************/
#define READ_TIME_INDEX            0
#define StartHeating_Task_INDEX    1
#define StopButton_Task_INDEX      2


/* Description: Task executes once to initialize all the Modules */
void Init_Task(void);

void StartHeating_Task(void);

void StopButton_Task(void);

void StopHeating(void);

void Counting_Task(void);

void ReadTime_Task(void);

#endif /* APP_H */
