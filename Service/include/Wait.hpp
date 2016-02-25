/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/04/11>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _WAIT_HPP_
#define _WAIT_HPP_

#include <stdio.h>

extern "C"
{
  #include "System/include/Thread.h"
  #include "System/include/Types.h"
}

#include "Core/include/Configuration.h"

#include "Trace.hpp"
#include "Semaphore.hpp"
using namespace Service;

namespace Service
{   
  /// <summary>
  /// Suspend for Wait condition operations.
  /// </summary>
  class Wait
  {
    public:

      /// <summary>
      /// Constructor/Descructor
      /// </summary>
      Wait();
      ~Wait();

      /// <summary>
      /// Put process to sleep (i.e. suspend).
      /// </summary>
      /// <param name="tag">
      /// number of conditon to wait for
      /// </param>
      /// <param name="timeout">
      /// if not defined will sleep until "Wakeup", or is msec. time value to wait.
      /// </param>
      /// <param name="precision">
      /// how often to check for time elapsed (note: smaller value uses more processor time).
      /// </param>
      /// <returns>false if failed</returns>
      bool Sleep(uint8 tag, uintsys timeout=0, uint8 precision=5);

      /// <summary>
      /// Invokes a "Sleep" task to wakeup (i.e. resume).
      /// </summary>
      /// <param name="tag">
      /// number of tag conditon to wakeup
      /// </param>
      void Wakeup(uint8);

    protected:


    private:
      struct Wait_t
      {      
        bool flag; 
      };

      static const uint8 MAX_TAGS = WAIT_TAGS_MAX;
      static Wait_t _map[];

      Trace *_trace;
      Semaphore _lock;

      void Create(uint8);

  };
};
#endif
