/*-----------------------------------------------------------------------------
 *
 * Released: <2010/08/04>
 * Modified: <YEAR/MONTH/DAY>
 *
 * Description: Under Work!
 *
 *-----------------------------------------------------------------------------
 */

#ifndef _PWM_HPP_
#define _PWM_HPP_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

extern "C"
{
  #include "System/include/Types.h"
}

#include "Service/include/Trace.hpp"
using namespace Service;

namespace Driver
{
  /// <summary>
  /// PWM Controller.
  /// </summary>
  /// <remarks></remarks>
  class PWM
  {
    public:

      /// <summary>
      /// Constructor for PWM using 8-bit timer.
      /// </summary>
      /// <param name="timer"/>
      PWM(uint8 timer=2);
      ~PWM(void);

      /// <summary>
      /// Speed range by value
      /// </summary>
      /// <param name="motor">0 or 1<param>
      /// <param name="speed">0 - 255 ?<param>
      void Speed(uint8, uint8);

    protected:

    private:
      uint8 _timer;

  };
};

#endif
