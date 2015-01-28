extern "C"
{
  #include "System/include/Tools.h"
}

#include "../include/ThreadPool.hpp"
using namespace Service;

//init static members
ThreadPool* ThreadPool::_instance = 0;
//define singleton instance (to call contructor)
static ThreadPool _singleton;

const uintsys ThreadPool::MaxSize = THREAD_POOL_SIZE;

ThreadPool::ThreadPool(ThreadPool::Priority priority):
 _count(0), _active(0), _run(true), _suspend(true)
{
  _trace = Trace::Instance();
  
  for(uintsys i=0;i<THREAD_POOL_WORKERS;i++)
  {
    THREAD_HANDLE handle;
    THREAD_CREATE(ThreadPool::EntryPoint, this, (ThreadPriority)priority, &handle);

    _handles[i] = handle;
  }

  _suspend = false;
}

ThreadPool::~ThreadPool()
{
  _run = false;
}

ThreadPool* ThreadPool::Instance() 
{
  if(_instance == 0)
    _instance = &_singleton;
  return _instance;
}

bool ThreadPool::IsAlive()
{
  bool status = true;

  for(uintsys i=0;i<THREAD_POOL_WORKERS;i++)
  {
    if(!IS_THREAD_ALIVE(_handles[i]))
      status = false;
  }

  return(_run && status);
}

void ThreadPool::Wait(uintsys timeOut)
{
  while(_active > 0)
  {
    if(timeOut <= 0)
      Delay(5);
    else
    {
      Delay(timeOut);
      break;
    }
  }
}

void ThreadPool::Resume()
{
  _suspend = false;
}

void ThreadPool::Suspend()
{
  _suspend = true;
}

void ThreadPool::Add(Item_t item)
{
  _lock.SectionEnter();
  {     
    if(_count < THREAD_POOL_SIZE)
    {
      _count++;
      _queue[_count-1] = item;
    }
  }
  _lock.SectionExit();
}

//static entry point for thread
THREAD_FUNCTION ThreadPool::EntryPoint(THREAD_ARGS handler)
{
  ThreadPool *thread = (ThreadPool*)handler;  //cast
  thread->Process();
}

//thread pool manager
void ThreadPool::Process()
{
  while(_run)
  {
    if(!_suspend)
    {
      Item_t item;
      uint8 count = 0;

      _lock.SectionEnter();
      {
        count = _count;
        if(count > 0)
        {
          _active++;
          _count--;

          item = _queue[0]; //get first item like queue
          //shift down, for first item next run
          for(uintsys i=0;i<count;i++)
            _queue[i] = _queue[i+1];
        }
      }
      _lock.SectionExit();

      if(count > 0)
      {
        item.Function(item.Args);  //run function until completed 

        _lock.SectionEnter();
        {
          _active--;
        }
        _lock.SectionExit();
      }
    }

    Delay(5);
  }
  THREAD_EXIT();
}
