/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description:
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _S_SEMPAHORE_H_ //if not defined
#define _S_SEMPAHORE_H_ //define

// FreeRTOS
#include "FreeRTOS.h"
#include "semphr.h" 

#include "Types.h"
/*
  Note: Mutexes can be applied only to threads in a single process and do not
  work between processes as do semaphores. 
*/

#define SEMAPHORE_HANDLE                      xSemaphoreHandle

#define SEMAPHORE_OPEN(sem, stat)             { vSemaphoreCreateBinary(sem); if(sem != NULL) stat = true; }
#define SEMAPHORE_POST(sem)                   xSemaphoreGive(sem) != pdTRUE ? false : true
#define SEMAPHORE_WAIT(sem)                   xSemaphoreTake( sem, (portTickType)0 ) != pdTRUE ? false : true
#define SEMAPHORE_TRY_WAIT(sem, value)        xSemaphoreTake( sem, (portTickType)(value/portTICK_RATE_MS) ) != pdTRUE  ? false : true

#endif
  
