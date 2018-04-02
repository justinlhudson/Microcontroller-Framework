/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/08/31>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: Global setup for framework.
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

//Note: Timer1 (16-bit) is used for FreeRTOS

//ThreadPool
#define THREAD_POOL_WORKERS                               1
#define THREAD_POOL_SIZE                                  6

// Defines number of tasks to be ready to create by changing heap size allocated.
// Note: This is in addition to current framework setup/operations.
// monitor (i.e. WDT), application, core, idle task, relativeTime, thread pool (X)
#define CREATE_TASKS                                      (5 + THREAD_POOL_WORKERS)

#define CPU_FREQUENCY_HZ                                  (FREQUENCY)

// Used to Trace Logging (uin8 max) 9600 (normal), 115200 (greater 2x), 2000000 (2mb max on 16mhz)
#define TRACE_BAUD_RATE                                   115200

// All=128, Fatal=1, Error=2, Warning=3, Info=4, Debug=5, Operation = -1, None = -128
// Important: matches Trace.h enum
#if defined(TRACE)
  #if TRACE == -128
    #define TRACE_LEVEL                                       Trace::None
  #elif TRACE == -1
    #define TRACE_LEVEL                                       Trace::Operation
  #elif TRACE == 5
    #define TRACE_LEVEL                                       Trace::Debug
  #elif TRACE == 4
    #define TRACE_LEVEL                                       Trace::Info
  #elif TRACE == 3
    #define TRACE_LEVEL                                       Trace::Warning
  #elif TRACE == 2
    #define TRACE_LEVEL                                       Trace::Error
  #elif TRACE == 1
    #define TRACE_LEVEL                                       Trace::Fatal
  #else
    #define TRACE_LEVEL                                       Trace::All
  #endif
#else
  #define TRACE_LEVEL                                         Trace::All
#endif

// MAX = 256
#define USART_BUFFER_LENGTH                               90

//Subject/Observer
#define MAX_CLASS_OBSERVERS                               8

//WDT ms.
// Important, with RTOS timing do not increase above 2 seconds
#define WDT_TIMER_TIMEOUT                                 2000

//Wait
//Max. amount of wait conditions
#define WAIT_TAGS_MAX                                     CREATE_TASKS

// Defined usarts active/setup
#define USARTS                                            1

#endif
