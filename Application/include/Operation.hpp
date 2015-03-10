/*-----------------------------------------------------------------------------
 * 
 * Released: <20XX/XX/XX>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description:
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _OPERATION_HPP_
#define _OPERATION_HPP_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

extern "C"
{
  #include "System/include/Types.h"
}
#include "Service/include/ThreadPool.hpp"
#include "Service/include/Semaphore.hpp"
#include "Service/include/Trace.hpp"
using namespace Service;

namespace Application
{
  class Operation
  {
    public:

      /// <summary>
      /// Define message type
      /// </summary>
      /// <remarks>
      /// </remarks>
      struct Message
      {
          int8 Command[8];
          int8 Operation[8];
          int8 Value[32];
          int8 Response[8];
      };

      Operation(void);
      ~Operation(void);

      Message Command(Message);
      void Process();

    protected:

    private:
     
      Trace *_trace;
      ThreadPool *_threadPool;
  };
};
#endif
