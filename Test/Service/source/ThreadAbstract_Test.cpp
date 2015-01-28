#include "System/include/Types.h"

#include "Service/include/Trace.hpp"
#include "Service/include/ThreadAbstract.hpp"
using namespace Service;

class ThreadAbstract_Test0 : public ThreadAbstract
{
  public:

    intsys Init;
    intsys Count;

    ThreadAbstract_Test0(): ThreadAbstract() //call base class
    { 
      Init = 0;
      Count = 0;
    }  

    virtual void PreExecute()
    { 
      Init = 1;
      Trace *trace = Trace::Instance();
      trace->Log(Trace::Debug,"ThreadAbstract_Test.cpp, PreExecute - Setup\n");
    };

    virtual void Execute() 
    {      
      if(Init == 1)
        Init = 2;
      Count++;
      Delay(1);
    }
};

class ThreadAbstract_Test1 : public ThreadAbstract
{
  public:

    intsys Init;
    intsys Count;

    ThreadAbstract_Test1(): ThreadAbstract() //call base class
    { 
      Init = 0;
      Count = 0;
    }  

    virtual void PreExecute()
    {
      Init = 1;
      Trace *trace = Trace::Instance();
      trace->Log(Trace::Debug,"ThreadAbstract_Test.cpp, PreExecute - Setup\n");
    };

    virtual void Execute()
    {
      if(Init == 1)
        Init = 2;

      Count++;
      Delay(1);
    }
};

intsys main_Test(intsys argc, int8 *argv[])
{
  Trace *trace = Trace::Instance();
  bool result = false;  //init. passed
  intsys value = 0;

  ThreadAbstract_Test0 *thread_Test0 = new ThreadAbstract_Test0();
  ThreadAbstract_Test1 *thread_Test1 = new ThreadAbstract_Test1();

  thread_Test0->Start(ThreadAbstract::Below);
  thread_Test1->Start(ThreadAbstract::Above);

  Delay(10);
  if(thread_Test0->Init != 2 && thread_Test1->Init != 2)
  {
    trace->Log(Trace::Info,"ThreadAbstract_Test.cpp, Main - Virtual methods not called \n");
    result = true;
  }
  else
    trace->Log(Trace::Info,"ThreadAbstract_Test.cpp, Main - Startup \n");

  // Check threads are alive
  int count = 0;
  while(!thread_Test0->IsAlive() && !thread_Test1->IsAlive() && count++ < 25)
  {
    Delay(10);
  }

  if(count >= 25)
  {
    result = true;
    trace->Log(Trace::Info,"ThreadAbstract_Test.cpp, Main - NOT Alive \n");
  }
  else
    trace->Log(Trace::Info,"ThreadAbstract_Test.cpp, Main - Alive \n");

  count = 0;
  while(thread_Test0->Count < 25 && thread_Test1->Count < 25 && count++ < 25)
    Delay(10);

  if(thread_Test0->Count < 20 && thread_Test1->Count < 20)
  {
    result = true;
    trace->Log(Trace::Info,"ThreadAbstract_Test.cpp, Main - Not Running \n");
  }
  else
    trace->Log(Trace::Info,"ThreadAbstract_Test.cpp, Main - Running \n");

  // Suspend & Resume
  thread_Test0->Suspend();
  Delay(10);
  value = thread_Test0->Count;
  Delay(10);

  if(value != thread_Test0->Count)
  {
    trace->Log(Trace::Info,"ThreadAbstract_Test.cpp, Main - Not suspended \n");  
    result = true; //failed
  }
  else
    trace->Log(Trace::Info,"ThreadAbstract_Test.cpp, Main - Suspended \n");

  thread_Test0->Resume();
  trace->Log(Trace::Info,"ThreadAbstract_Test.cpp, Main - Resumed \n");
  Delay(10);

  thread_Test0->Stop();
  thread_Test1->Stop();
  Delay(10);

  if(thread_Test0->IsAlive() && thread_Test1->IsAlive())
  {
    result = true;
    trace->Log(Trace::Info,"ThreadAbstract_Test.cpp, Main - Still alive, should be dead \n");
  }

  if(result)
    trace->Log(Trace::Warning,"\nThreadAbstract_Test.cpp - FAILED \n");
  else
    trace->Log(Trace::Info,"\nThreadAbstract_Test.cpp - Passed \n");

  delete thread_Test0;
  delete thread_Test1;

  return(intsys)result;
}
