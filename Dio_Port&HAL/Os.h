 /******************************************************************************
 *
 * Module: Os
 *
 * File Name: Os.h
 *
 * Description: Header file for Os Scheduler.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#ifndef OS_H
#define OS_H

#include "Std_Types.h"


/* Description: 
 * Function responsible for:
 * 1. Enable Interrupts
 * 2. Start the Os timer
 * 3. Execute the Init Task
 * 4. Start the Scheduler to run the tasks
 */
void Os_start(void);



#endif /* OS_H_ */
