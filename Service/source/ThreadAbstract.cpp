/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: Body File.
 * 
 *-----------------------------------------------------------------------------
 */

#include "../../System/include/Tools.h"

//#include "../include/IException.hpp"
#include "../include/ThreadAbstract.hpp"
using namespace Service;

ThreadAbstract::ThreadAbstract():
_priority(ThreadAbstract::Normal), _run(false), _suspend(true)
{
  _args = NULL;
}

ThreadAbstract::~ThreadAbstract()
{
  Stop(); //stop execution
}

bool ThreadAbstract::IsAlive()
{
  return(_run && IS_THREAD_ALIVE(_handle));
}

void ThreadAbstract::Start(ThreadAbstract::Priority priority)
{
  if(!_run)
  {
    _run = true;

    _priority = priority;

    Args(NULL);  //not used
    THREAD_CREATE(ThreadAbstract::EntryPoint, this, (ThreadPriority)_priority, &_handle);
  }

  _suspend = false; //start execution
  return;
}

void ThreadAbstract::Stop()
{
  _run = false;
}

void ThreadAbstract::Resume()
{
  _suspend = false;
}

void ThreadAbstract::Suspend()
{
  _suspend = true;
}

void* ThreadAbstract::Args() const
{
  return _args;
}

void ThreadAbstract::Args(void *args)
{
  _args = args;
}

//static entry point for thread
THREAD_FUNCTION ThreadAbstract::EntryPoint(THREAD_ARGS handler)
{
  ThreadAbstract *thread = (ThreadAbstract*)handler;  //cast
  thread->Process( thread->Args() );

  return;
}

THREAD_FUNCTION ThreadAbstract::Process(void *args)
{
  PreExecute();  //virtual
  while(_run)
  {
    if(!_suspend)
    {  
      Execute();  //virtual
      Delay(0);  //give back to scheduler
    }
    else
      Delay(5);
  }

  _run = false;
  THREAD_CLOSE(_handle);
  return;
}

