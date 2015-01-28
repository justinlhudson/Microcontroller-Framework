/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/08/04>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: Under Work!
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _MOTOR_HPP_
#define _MOTOR_HPP_

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
  /// Motor Controller.
  /// </summary>
  /// <remarks></remarks>
  class Motor
  {
    public:
      
      /// <summary>
      /// Constructor for PWM using 8-bit timer.
      /// </summary>
      /// <param name="timer"/> 
      Motor(uint8 timer=2);
      ~Motor(void);

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
