/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/08/04>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: Main entry point!
 * 
 *-----------------------------------------------------------------------------
 */

#include <stdlib.h>
#include <string.h>

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#elif defined(__AVR_ATmega328P__)
#endif

extern "C"
{
  #include "System/include/Types.h"
  #include "System/include/Definitions.h"
  #include "System/include/Tools.h"
  #include "System/include/Thread.h"
  #include "System/include/Power.h"
}

#include "Core/include/Configuration.h"

#include "Service/include/WDT.hpp"
#include "Service/include/Trace.hpp"
using namespace Service;

#include "Component/include/RelativeTimeClock.hpp"
using namespace Component;

#include "../include/Application.hpp"
using namespace Core;

// Prototypes
void Initialize(void);
void ShowSystemUsage(void);

THREAD_FUNCTION Monitor(THREAD_ARGS);

#if TEST >= 0
  THREAD_FUNCTION Testing(THREAD_ARGS);
#endif

intsys main(void)
{
  Initialize();

  THREAD_HANDLE monitor;
  THREAD_CREATE(Monitor, NULL, ThreadPriorityLowest, &monitor);

#if TEST > 0
  THREAD_HANDLE testing;
  THREAD_CREATE(Testing, NULL, ThreadPriorityNormal, &testing);
#else
  Application application; // static
#endif

  // let things (pins values and what not) settle (feels good)
  DELAY_MS(125);

  // Note:  Used for auto search correct port for USB coms.
  // App. simply looks for label value to come through...
  Trace::Instance()->Log(Trace::Operation, "%s \n\r", "Initialize...");

  ShowSystemUsage();

  Delay(250);  // if connecting for tracing give some time to see traces

  Trace::Instance()->Log(Trace::Info,"\n\rReady...\n\r");

  THREAD_SCHEDULER(); //is a locking function 

  /*
  while(true)
  {
    Delay(0);
  }
  */

  Trace::Instance()->Log(Trace::Info,"\n\rDone!\n\r");

  THREAD_CLOSE(monitor);
#if TEST > 0
  THREAD_CLOSE(testing);
#endif
  return 0;
}

void Initialize(void)
{
//  CPU_Calibrate(EEPROM::Load(INTERNAL_EEPROM_SIZE));

  Trace::Instance()->Display(true);
  Trace::Instance()->Level(TRACE_LEVEL);

  WDT::Interval(WDT_TIMER_TIMEOUT);
  WDT::On();
}

THREAD_FUNCTION Monitor(THREAD_ARGS args)
{
  while(true)
  {
    WDT::Reset();  // kick the dog!
    
    { //Time
      RelativeTimeClock::TimeSpan_t timeSpan = RelativeTimeClock::Instance()->Get();

      Trace::Instance()->Log(Trace::Debug," %d/%d:%d:%d:%d ", \
                               timeSpan.Year,timeSpan.Day,timeSpan.Hour,timeSpan.Minute,timeSpan.Second);
    }

    Delay((double)(WDT_TIMER_TIMEOUT*0.75));  //keeps timing with RTOS withing 25% range else reboot
  }
}

void ShowSystemUsage(void)
{
  memory_usage_t usage;
  MemoryUsage(&usage);
  Trace::Instance()->Log(Trace::Info,"Memory usage (bytes)\n\r");
  Trace::Instance()->Log(Trace::Info,
                         " .data: %d\n\r .bss: %d\n\r .heap: %d\n\r .stack: %d\n\r",
                         usage.data_size, usage.bss_size, usage.heap_size, usage.stack_size);
}

#if TEST > 0
  #if TEST == 1
    #include "Test/Service/source/ThreadAbstract_Test.cpp"
  #endif
  #if TEST == 2
    #include "Test/Service/source/ThreadPool_Test.cpp"
  #endif

  THREAD_FUNCTION Testing(THREAD_ARGS args)
  {
    bool result = false;

    #if TEST == 1
      result |= main_Test(NULL,NULL);
    #endif
    #if TEST == 2
      result |= main_Test(NULL,NULL);
    #endif
  }
#endif
