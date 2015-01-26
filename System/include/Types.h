/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <avr/io.h>

//defines
#if !defined(NULL)
  #define NULL                          0
#endif

#define END_CHAR                        '\0'

typedef void object;
//system int
typedef int intsys;
typedef unsigned int uintsys;

//defined in stdio.h
typedef char                            int8;
typedef unsigned char                   uint8;
typedef int                             int16;
typedef unsigned int                    uint16;
typedef long                            int32;
typedef unsigned long                   uint32;
typedef long long                       int64;
typedef unsigned long long              uint64;

#if !defined(NOP)
  #define NOP                           asm volatile ("nop"::)
#endif

//bool
#if defined(__cplusplus)
  enum boolean
  {
    no = 0, yes=1,
    off = 0, on=1
  };
#else
  //if C, there is no bool
  #if !defined(bool)
    typedef unsigned char     bool;
    enum boolean 
    {
      false=0, true=1,
      no = 0, yes=1,
      off = 0, on=1
    };
  #endif
#endif

typedef volatile uint8_t     reg8;

//Note: PROGMEM stores in flash

//EEPROM Memory Storage
//(i.e. const char variable[] PROGMEM = { } )  

///  ***  C++ Class Support *** ///

#ifdef __cplusplus
  inline void* operator new(uint16 size)
  {
    if(size == 0)
      size= 1;

    void *pMem = NULL;
    while(pMem == NULL) //infinit loop to keep trying
      pMem = malloc(size);

    return pMem;
  }; 

  inline void* operator new(uint16 size, void *ptr) 
  { 
    if(size == 0)
      size= 1;

    void *pMem = NULL;
    if(ptr != NULL)
    {
      while(pMem == NULL) //infinit loop to keep trying
        pMem = realloc(ptr,size);
    }

    return pMem;
  };

  inline void operator delete(void *ptr) 
  { 
    if(ptr != NULL)
      free(ptr);
  };

  inline void* operator new[](uint16 size) 
  { 
    if(size == 0)
      size= 1;

    void *pMem = NULL;
    while(pMem == NULL) //infinite loop to keep trying
      pMem = malloc(size);

    return pMem;
  };

  inline void* operator new[](uint16 size, void *ptr)
  { 
    if(size == 0)
      size= 1;

    void *pMem = NULL;
    if(ptr != NULL)
    {
      while(pMem == NULL)  //infinite loop to keep trying
        pMem = realloc(ptr,size);
    }

    return pMem;
  };

  inline void operator delete[](void *ptr)
  { 
    if(ptr != NULL)
      free(ptr);
  };
/*
  // this is applicable if using virtual inheritance.
  __extension__ typedef int __guard __attribute__((mode (__DI__)));

  int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
  void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
  void __cxa_guard_abort (__guard *) {}; 

  // this is applicable if using pure virtual inheritance.
  void __cxa_pure_virtual(void) {}; 
*/
#else
  /*
    // this is applicable if using virtual inheritance.
  __extension__ typedef int __guard __attribute__((mode (__DI__)));

  extern "C" int __cxa_guard_acquire(__guard *);
  extern "C" void __cxa_guard_release (__guard *);
  extern "C" void __cxa_guard_abort (__guard *);

  // this is applicable if using pure virtual inheritance.
  extern "C" void __cxa_pure_virtual(void); 
  */
#endif

#endif
