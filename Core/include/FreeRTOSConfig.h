/*
    FreeRTOS V6.0.5 - Copyright (C) 2010 Real Time Engineers Ltd.
*/

#ifndef _FREERTOS_CONFIG_H_
#define _FREERTOS_CONFIG_H_

#include <avr/io.h>
#include "Configuration.h"

/*-----------------------------------------------------------
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

// 1 => preemptive: Kernel will decided when to suspend and let other tasks run
// 0 => coorperative: Kernel will wait for task to "yeild" before running another
#define configUSE_PREEMPTION		0

// The idle task is responsible for freeing memory allocated by the RTOS to tasks 
// that have since been deleted. "void vApplicationIdleHook( void );" 
#define configUSE_IDLE_HOOK			0

// Good place for timers to be implemented
// "void vApplicationTickHook( void );"
#define configUSE_TICK_HOOK			0

#define configCPU_CLOCK_HZ			( ( unsigned long ) F_CPU)

// Rate at which kernel processes, faster rate means kernel takes more CPU time.
// Muiltiple gives 1% of total CPU time to kernel
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 ) // every 1ms

#define configMAX_PRIORITIES		( 8 )

// The size of the stack used by the idle task. 
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 256 )

//The total amount of RAM available to the kernel (think of * # of tasks).
#define configTOTAL_HEAP_SIZE   ( (size_t ) (configMINIMAL_STACK_SIZE * 3 * CREATE_TASKS) )

// Manely used for debugging , includes endline
// Note: hardcoded name so do not change.
#define configMAX_TASK_NAME_LEN   ( 4 )

// Set to 1 if you wish the trace visualisation functionality to be available, or 0 if
// the trace functionality is not going to be used. If you use the trace functionality
// a trace buffer must also be provided. 
#define configUSE_TRACE_FACILITY  0

// Defining configUSE_16_BIT_TICKS as 0 causes portTickType to be defined (typedef'ed)
// as an unsigned 32bit type. 
// Using a 16 bit type will greatly improve performance on 8 and 16 bit architectures,
// but limits the maximum specifiable time period to 65535 'ticks'. Therefore, assuming
// a tick frequency of 250Hz, the maximum time a task can delay or block when a 16bit
// counter is used is 262 seconds, compared to 17179869 seconds when using a 32bit counter. 
#define configUSE_16_BIT_TICKS    1

// When configIDLE_SHOULD_YIELD is set to 1 the idle task will yield immediately should
// any other task at the idle priority be ready to run
#define configIDLE_SHOULD_YIELD   0
 
// configQUEUE_REGISTRY_SIZE defines the maximum number of queues and semaphores that can be
// registered. Only those queues and semaphores that you want to view using a kernel aware
// debugger need be registered. 
#define configQUEUE_REGISTRY_SIZE	      0

// Co-routine definitions.
#define configUSE_CO_ROUTINES           0
#define configMAX_CO_ROUTINE_PRIORITIES ( 8 )

// used in applications that have different levels of priority for interrupts 
/* 
#define configKERNEL_INTERRUPT_PRIORITY 
#define configMAX_SYSCALL_INTERRUPT_PRIORITY
*/ 

// Set the following definitions to 1 to include the API function, or zero
// to exclude the API function.
#define INCLUDE_vTaskPrioritySet		0
#define INCLUDE_uxTaskPriorityGet		0
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend			0
#define INCLUDE_vTaskDelayUntil			0
#define INCLUDE_vTaskDelay				1

#define INCLUDE_xTaskGetSchedulerState  1

#endif
