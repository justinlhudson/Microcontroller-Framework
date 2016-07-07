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
#define THREAD_POOL_WORKERS                               2
#define THREAD_POOL_SIZE                                  9

// Defines number of tasks to be ready to create by changing heap size allocated.
// Note: This is in addition to current framework setup/operations.
// monitor (i.e. WDT), application, idle task, relativeTime, thread pool (X)
#define CREATE_TASKS                                      (4 + THREAD_POOL_WORKERS)

#define CPU_FREQUENCY_HZ                                  (FREQUENCY)

// Used to Trace Logging (uin8 max) 9600 (normal), 115200 (greater 2x), 2000000 (2mb max on 16mhz)
#define TRACE_BAUD_RATE                                   115200

#define TRACE_LEVEL                                       Trace::Debug

// MAX = 256
#define USART_BUFFER_LENGTH                               128
#define RF24_BUFFER_LENGTH                                32

//Subject/Observer
#define MAX_CLASS_OBSERVERS                               16

//WDT ms.
#define WDT_TIMER_TIMEOUT                                 2000

//Wait
//Max. amount of wait conditions
#define WAIT_TAGS_MAX                                     CREATE_TASKS

// Defined usarts active/setup
#define USARTS                                            1

#endif
