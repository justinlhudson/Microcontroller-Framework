/*-----------------------------------------------------------------------------
 * 
 * Released: <2009/11/28>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: Used as "main" startup for operations, not specific to
 *              controller, but for implementation of desired application(s).
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "System/include/Types.h"

#include "Service/include/Trace.hpp"
#include "Service/include/Semaphore.hpp"
#include "Service/include/ThreadAbstract.hpp"
#include "Service/include/SubjectObserverAbstract.hpp"
using namespace Service;

extern void Setup(void);
extern void Loop(void);

namespace Core
{
  /// <summary>
  /// Specific Runtime Operation(s)
  /// </summary>
  /// <remarks>the reason to use the controller</remarks>
  class Application : protected ThreadAbstract, private ObserverAbstract
  {
    public:
      
      /// <summary>
      /// Constructor/Desctructor
      /// </summary>
      Application(void);
      ~Application(void);

    protected:

    private:
     
      Trace *_trace;

      void Update(object *);

      void PreExecute(void);
      void Execute(void);
  };
};
#endif
