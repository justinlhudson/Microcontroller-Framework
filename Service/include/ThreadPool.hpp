/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/04/06>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _THREAD_POOL_HPP_
#define _THREAD_POOL_HPP_

#include <stdio.h>

#include "System/include/Types.h"
#include "System/include/Thread.h"

#include "Core/include/Configuration.h"

#include "Trace.hpp"
#include "Semaphore.hpp"
using namespace Service;

// Defines number of worker threads in for the pool.
#if !defined(THREAD_POOL_WORKERS)
#define THREAD_POOL_WORKERS 1
#endif
#if !defined(THREAD_POOL_SIZE)
#define THREAD_POOL_SIZE  6
#endif

namespace Service
{
  /// <summary>
  /// Thread Pool Operations.
  /// 
  /// Is a multiple thread runner (obviously)...
  /// </summary>
  class ThreadPool
  {
    public:

      /// <summary>
      /// Max number of functions to hold in queue.
      /// </summary>
      static const uintsys MaxSize;

      /// <summary>
      /// Define priority level for thread. 
      /// </summary>
      /// <remarks>
      /// realtime should never be used, unless rare case.
      /// </remarks>
      enum Priority 
      {
        Standard = ThreadPriorityStandard,

        Lowest = ThreadPriorityLowest,
        Below = ThreadPriorityBelow,
        Normal = ThreadPriorityNormal,
        Above = ThreadPriorityAbove,
        Highest = ThreadPriorityHighest,

        RealTime = ThreadPriorityRealTime
      };

      /// <summary>
      /// Defines function pointer type
      /// </summary>
      typedef void(*ThreadPoolFunction_t)(void *Args);

      /// <summary>
      /// Defines structure type for function pointer and args to add to pool.
      /// </summary>
      struct Item_t
      {
        ThreadPoolFunction_t Function;
        void *Args;
      };

      /// <summary>
      /// Constructor/Descructor
      /// </summary>
      /// <param name="workers">
      /// defines number of threads working for the pool.
      /// </param>
      /// <param name="priority" />      
      ThreadPool(ThreadPool::Priority priority=ThreadPool::Below);

      /// <summary>
      /// Descructor
      /// </summary>
      ~ThreadPool();

      /// <summary>
      /// Defines singletion.
      /// </summary>
      /// <returns>object pointer</returns>
      static ThreadPool *Instance(); 

      /// <summary>
      /// Returns if process and execution is active
      /// </summary>
      /// <returns> true/false </returns>
      bool IsAlive();

      /// <summary>
      /// Spins waiting for thread pool queue to empty or timeout reached.
      /// </summary>
      /// <param name="timeout">
      /// 0 means wait for queue to empty, else wait for queue or timeout.
      /// </param>
      void Wait(uintsys timeOut = 0);

      /// <summary>
      /// Add task to pool.
      /// </summary>
      /// <param name="item">
      /// is work item, with function pointer and args.
      /// </param>
      void Add(Item_t);

      /// <summary>
      /// Suspend execution
      /// </summary>
      /// <remarks>
      /// simply does not call pull from queue function.
      /// </remarks>
      void Suspend();

      /// <summary>
      /// Resume exectuion
      /// </summary>
      void Resume();

    protected:

    private:

      Trace *_trace;

      static ThreadPool *_instance;

      THREAD_HANDLE _handles[THREAD_POOL_WORKERS];

      Semaphore _lock;
      Item_t _queue[THREAD_POOL_SIZE]; // work item

      uint8 _count;
      uint8 _active;

      bool _run;
      bool _suspend;

      void Process();
      static THREAD_FUNCTION EntryPoint(THREAD_ARGS);

  };
};
#endif
