/*-----------------------------------------------------------------------------
 * 
 * Released: <2009/11/28>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: Used to tracing via level setting relavent application
 *              information for display and file archiving.
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _TRACE_HPP_
#define _TRACE_HPP_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

extern "C"
{
  #include "System/include/Types.h"
  #include "System/include/Tools.h"
}

#include "Core/include/Configuration.h"

#include "USART.hpp"
#include "Semaphore.hpp"
#include "ThreadAbstract.hpp"
#include "SubjectObserverAbstract.hpp"
using namespace Service;

namespace Service
{

  #define TRACE_NEWLINE      "\r\n"
  #define TRACE_LINE()      Trace::Instance()->Log(Trace::Debug, "\n\r~"); Trace::Instance()->Log(Trace::Debug, LINE); Trace::Instance()->Log(Trace::Debug, "~ \n\r")
  /// <summary>
  /// Trace Operations
  /// 
  /// Is a thread runner, to handle incoming data...
  /// </summary>
  /// <remarks>used like "printf" and mapped to external port (i.e. USART).</remarks>
  class Trace : public SubjectAbstract, private ThreadAbstract
  {
    public:
      
      /// <summary>
      /// Constant max. value for message string length.
      /// </summary>
      static const uint32 MaxLength;

      /// <summary>
      /// Defines trace level of when to log/display or not.
      /// </summary>
      enum Option
      {
        All=128, Fatal=1, Error=2, Warning=3, Info=4, Debug=5, Operation = -1, None = -128
      };
      
      /// <summary>
      /// Constructor/Destructor.
      /// </summary>
      Trace(uint8 usart=0, uint32 baud=TRACE_BAUD_RATE);
      ~Trace();
      
      /// <summary>
      /// Defines singletion.
      /// </summary>
      /// <returns>object pointer</returns>
      static Trace *Instance();

      /// <summary>
      /// Trace level logging.
      /// </summary>
      /// <param name="level">option type</param>
      /// <param name="format">string</param>
      /// <param name="args">values associated with "format"</param>
      /// <remarks>operates like printf in C</remarks>
      /// <returns>status if operation completed succesful == true</returns>
      bool Log(Option, const int8* format, ...);

      /// <summary>
      /// Set trace level
      /// </summary>
      /// <param name="level">option type</param>
      /// <remarks>can be changed at anytime.</remarks>
      void Level(Option);

      /// <summary>
      /// Set to show on console.
      /// </summary>
      /// <param name="onOff">true=display, false=no display</param>
      /// <remarks>still send to log file based on level value.</remarks>
      void Display(bool);

    protected:

    private:

      static Trace *_instance;

      USART *_usart;

      Semaphore _lock;

      Option _level;
      bool _display;

      void Activate();
      void Deactivate();

      void Execute();
  };
};
#endif
