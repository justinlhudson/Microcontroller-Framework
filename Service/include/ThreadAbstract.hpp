/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _ABSTRACT_THREAD_HPP_
#define _ABSTRACT_THREAD_HPP_

#include <stdio.h>

#include "System/include/Types.h"
#include "System/include/Thread.h"

namespace Service
{
  /// <summary>
  /// Base Class Thread Operation.
  /// 
  /// Is a thread runner (obviously)...
  /// </summary>
  class ThreadAbstract
  {
    public:

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
      /// Descructor
      /// </summary>
      virtual ~ThreadAbstract();

      /// <summary>
      /// Start Thread process.
      /// </summary>
      /// <param name="priority">
      /// </param>
      void Start(ThreadAbstract::Priority priority=ThreadAbstract::Normal);

      /// <summary>
      /// Stop thread process.
      /// </summary>
      /// <remarks>
      /// Releses process to system. 
      /// </remarks>
      void Stop();

      /// <summary>
      /// If process and execution is active
      /// </summary>
      /// <returns> true/false </returns>
      bool IsAlive();

      /// <summary>
      /// Suspend execution
      /// </summary>
      /// <remarks>
      /// simply does not call "Exection" function.
      /// </remarks>
      void Suspend();

      /// <summary>
      /// Resume exectuion
      /// </summary>
      void Resume();

    protected:

      /// <summary>
      /// Constructor
      /// </summary>
      ThreadAbstract();

      /// <summary>
      /// Virtual function for pre-execution (callback).
      /// </summary>
      /// <remarks> 
      /// where pre-process/execution thread processing can happen.
      /// </remarks>
      virtual void PreExecute(){};

      /// <summary>
      /// Virtual function for execution (callback).
      /// </summary>
      /// <remarks> 
      /// thread process is runner.
      /// </remarks>
      virtual void Execute(){};

    private:

      THREAD_HANDLE _handle;

      void *_args;
      Priority _priority;

      bool _run;
      bool _suspend;

      THREAD_FUNCTION Process(void*);
      static THREAD_FUNCTION EntryPoint(THREAD_ARGS);

      void* Args() const;
      void Args(void*);
  };
};
#endif
