/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _TOOLS_H
#define _TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <avr/io.h> 
#include <avr/pgmspace.h>

#include "Types.h"

//makes anything into a string
#define STRING(s)                      #s

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
// will give line number of where "LINE" is placed (cool!)
#define LINE __FILE__ ":" TOSTRING(__LINE__)

#define SHIFT_L(type,X,Y)              ( (X) << (sizeof(type) * 8) * (Y) )
#define SHIFT_R(type,X,Y)              ( (X) >> (sizeof(type) * 8) * (Y) )

//if value is not safe, will not change value of answer.
#define SAFE_DIVIDE(numerator, divisor, answer) \
  { \
    if(divisor != 0); \
      answer = numberator / divisor; \
  } \

// Intiger TO Ascii
#define ITOA(i,a)                      { snprintf(a, ARRAY_SIZE(a), "%d", i); }

#define IS_EVEN(x)                     (x%2==0)

#define ARRAY_SIZE(a)                  (sizeof( a ) / sizeof( a[0] ))

#define PORT_CHECK(arg, val)            ((arg) & (val))

#define PORT_SET(arg,val)               ((arg) |=  (val))
#define PORT_CLR(arg,val)               ((arg) &= ~(val))
#define PORT_TOGGLE(arg,val)            ((arg) ^=  (val))

#define PORT_HIGH(arg,val)              PORT_SET(arg,val)
#define PORT_LOW(arg,val)               PORT_CLR(arg,val)

/*
  Used as Generic Swap
  Note: Be careful if swapping a struct with pointers,
        will not copy where the pointer point.
 */
inline void Swap(void *v1, void *v2, uint32 size)
{
  int8 *buffer = (int8*)malloc(size);
  memcpy(buffer,v1,size);
  memcpy(v1,v2,size);
  memcpy(v2,buffer,size);
  free(buffer);
}

/*
  Used as Generic Copy of memory
  Note: Be careful if copying a struct with pointers, 
        will not copy where the pointer points.
 */
inline void CopyDeep(void *destination, void *source, uint32 size)
{
  memcpy(destination, source, size);
}

#ifdef __cplusplus
extern "C"
{
#endif

  typedef struct 
  {
    uint32    data_size;
    uint32    bss_size;
    uint32    heap_size;
    uint32    stack_size;
    uint32    available;
  } memory_usage_t;

  //NOTE: The dynamic memory management portion of the C runtime needs the
  //      2 additional bytes for tracking the allocated memory.
  inline void MemoryUsage(memory_usage_t *usage) 
  {
    extern int8 *__bss_end, *__bss_start;
    extern int8 *__data_end, *__data_start;
    extern int8 *__brkval;
    //extern int8 *__malloc_heap_end;
    extern int8 *__heap_start;
    extern int8 *_end;
    extern int8 *__stack; 
    //extern size_t __malloc_margin;

    usage->data_size = (int)&__data_end - (int)&__data_start;
    usage->bss_size = (int)&__bss_end - (int)&__bss_start;
    usage->heap_size = (int)&__heap_start - (int)&__brkval;
    usage->stack_size = (int)*_end - (int)&__stack;
    usage->available =  (RAMEND - (int)&__data_start);  //entire space
    usage->available -= usage->data_size + usage->bss_size + usage->heap_size + usage->stack_size;  //used space
  }

#ifdef __cplusplus
};
#endif

#endif
