
#include "../../../System/include/Types.h"

#include "../../../Service/include/Trace.hpp"
#include "../../../Service/include/ThreadPool.hpp"
#include "../../../Service/include/Semaphore.hpp"
using namespace Service;

#define ADD_RUNS        6

void First(void *args);
void Second(void *args);

intsys FirstCount=0;
intsys FirstResult=0;

intsys SecondCount=0;
intsys SecondResult=0;

Semaphore g_lock;

intsys main_Test(intsys argc, int8 *argv[])
{
  bool result = false;  //set passed
  Trace *trace = Trace::Instance();

  ThreadPool *threadPool = ThreadPool::Instance();

  trace->Log(Trace::Info,"ThreadPool_Test.cpp, Main - Created \n");

  ThreadPool::Item_t item1,item2;

  int64 value = 24;

  item1.Function = &First;
  item1.Args = (void*)value;

  int8 str[] = "ThreadPool_Test.cpp, Main - String added to function\n";
  item2.Function = &Second;
  item2.Args = (void*)str;

  trace->Log(Trace::Info,"ThreadPool_Test.cpp, Main - Created \n");
  for(uintsys i=0;i<ADD_RUNS;i++)
  {
    threadPool->Add(item1);
    threadPool->Add(item2);
  }

  trace->Log(Trace::Info,"ThreadPool_Test.cpp, Main - Tasks added \n");
  threadPool->Wait();

  if(FirstCount != value)
  {
    result = true;
    trace->Log(Trace::Info,"ThreadPool_Test.cpp, Main - Args NOT passed correctly \n");
  }
  else
    trace->Log(Trace::Info,"ThreadPool_Test.cpp, Main - Args passed correctly \n");

  if(FirstResult != ADD_RUNS && SecondResult != ADD_RUNS)
  {
    result = true; //failed
    trace->Log(Trace::Info,"ThreadPool_Test.cpp, Main - Tasks did NOT complete: %d , %d \n",FirstResult,SecondResult);
  }
  else
    trace->Log(Trace::Info,"ThreadPool_Test.cpp, Main - Tasks did complete: %d , %d \n",FirstResult,SecondResult);


  trace->Log(Trace::Info,"ThreadPool_Test.cpp, Main - Delay to put runners to sleep \n");
  Delay(2000);  //allow threads to go to sleep and watch wake up  
  trace->Log(Trace::Info,"ThreadPool_Test.cpp, Main - Wakeup runners \n");

  for(uintsys i=0;i<ADD_RUNS;i++)
  {
    threadPool->Add(item1);
    threadPool->Add(item2);
  }

  trace->Log(Trace::Info,"ThreadPool_Test.cpp, Main - Tasks added \n");
  threadPool->Wait();

  if(FirstResult != 2*ADD_RUNS && SecondResult != 2*ADD_RUNS)
  {
    result = true; //failed
    trace->Log(Trace::Info,"ThreadPool_Test.cpp, Main - Tasks did NOT complete: %d , %d \n",FirstResult,SecondResult);
  }
  else
    trace->Log(Trace::Info,"ThreadPool_Test.cpp, Main - Tasks did complete: %d , %d \n",FirstResult,SecondResult);


  if(!threadPool->IsAlive())
  {
    trace->Log(Trace::Info,"ThreadPool_Test.cpp, Main - Runners are NOT all alive \n");
    result = true;
  }
  else
    trace->Log(Trace::Info,"ThreadPool_Test.cpp, Main - Runners are all alive \n");

  if(result)
    trace->Log(Trace::Warning,"\nThreadPool_Test.cpp - FAILED \n");
  else
    trace->Log(Trace::Info,"\nThreadPool_Test.cpp - Passed \n");

  return(int32)result;
}

void First(void* args)
{  
  Trace *trace = Trace::Instance();
  int64 count = (int64)args;

  trace->Log(Trace::Debug,"ThreadPool_Test.cpp, First - Started \n");

  FirstCount=count;
  while(count--)
  {
    Delay(1);
  }

  g_lock.SectionEnter();
  FirstResult++;
  g_lock.SectionExit();
}

void Second(void* args)
{
  Trace *trace = Trace::Instance();
  trace->Log(Trace::Debug,"ThreadPool_Test.cpp, Second - Started \n");

  trace->Log(Trace::Debug,"ThreadPool_Test.cpp, Second - %s", (int8*)args);

  g_lock.SectionEnter();
  SecondResult++;
  g_lock.SectionExit();
}
