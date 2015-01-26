/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/03/22>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: Defines an abstraction layer for creating threads in for other
 *              OS systems and/or distributions.
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _THREAD_H_ //if not defined
#define _THREAD_H_ //define

// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
//#include "croutine.h"

#include "Types.h"
#include "Definitions.h"

// Start the real time kernel. 
// NOTE:  Is a blocking call, should be done after main init.
#define THREAD_SCHEDULER()                vTaskStartScheduler()
#define THREAD_SCHEDULER_SUSPEND_ENTER()  vTaskSuspendAll()
#define THREAD_SCHEDULER_SUSPEND_EXIT() \
{ \
  if(!xTaskResumeAll()) \
    taskYIELD(); \
} \

#define THREAD_HANDLE                     xTaskHandle
#define THREAD_FUNCTION                   void
#define THREAD_ARGS                       void*

// Define priority options.
enum ThreadPriority
{
  ThreadPriorityStandard             =   tskIDLE_PRIORITY + 3,

  ThreadPriorityLowest               =   tskIDLE_PRIORITY + 1,
  ThreadPriorityBelow                =   tskIDLE_PRIORITY + 2,
  ThreadPriorityNormal               =   tskIDLE_PRIORITY + 4,
  ThreadPriorityAbove                =   tskIDLE_PRIORITY + 5,
  ThreadPriorityHighest              =   tskIDLE_PRIORITY + 6,

  ThreadPriorityRealTime             =   tskIDLE_PRIORITY + 7
};

// Lets go for value of msec but if value is <= 0 will yeild process (let go
// until schedual comes around again to thread).
// NOTE: This is releative to when the counter gets called, as missing interupts will cause
// this to be not absolute.
inline void Delay(uintsys msec)
{ 
  uintsys counter = msec;  // give negative value
  uint8 const DELAY_MAX = 0xFF;

  if(xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED)  // if RTOS not running
  {
    if(counter != 0)
    {
      while(counter >= DELAY_MAX)  // keeps from getting unsigned under 0 (e.g. making big number)
      {
        DELAY_MS(counter);
        counter -= DELAY_MAX;
      }
  
      if(counter > 0)
        DELAY_MS(counter);
    }    
  }
  else
  {
    if(counter != 0)
    {
      while(counter >= DELAY_MAX)  // keeps from getting unsigned under 0 (e.g. making big number)
      {
        vTaskDelay((portTickType)(DELAY_MAX / portTICK_RATE_MS));
        counter -= DELAY_MAX;
      }
  
      if(counter > 0)
        vTaskDelay((portTickType)(counter / portTICK_RATE_MS));
    }
    else
      taskYIELD();  //portYIELD();
  }
}

// Ex: THREAD_CREATE((THREAD_FUNCTION)function, (THREAD_ARGS)NULL,
//                  (ThreadPriority)Priority::Normal, (THREAD_HANDLE)&handle);  
#define THREAD_CREATE(function, args, priority, handle) \
  { \
    xTaskCreate(function, (const char*)"NAME", configMINIMAL_STACK_SIZE, (THREAD_ARGS)args, (unsigned portBASE_TYPE)priority, handle); \
  } \

// Ex: THREAD_ALIVE((THREAD_HANDLE)handle);
inline bool IS_THREAD_ALIVE(THREAD_HANDLE handle)
{
  bool result = false;
  if(handle != NULL)  //if created, assume is alive
    result = true;
  return result;
}

// Ex: THREAD_CLOSE((THREAD_HANDLE)handle)
#define THREAD_CLOSE(handle)         { vTaskDelete(handle); }
#define THREAD_EXIT()                { THREAD_CLOSE(NULL); }

#endif

