/*-----------------------------------------------------------------------------
 * 
 * Released: <2014/01/27>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _SERVO_HPP_
#define _SERVO_HPP_

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
  /// Servo Contoller.
  /// </summary>
  /// <remarks>Model: Parallax #900-00005</remarks>
  class Servo
  {
    public:
           
      /// <summary>
      /// Constructor for PWM using 16-bit timer.
      /// </summary>
      /// <param name="timer">
      /// Which controller timer to use.
      /// </param> 
      /// <remarks> 16-bit timer allows for two servors to be controlled by same timer</remarks>
      Servo(uint8 timer=3);
      ~Servo(void);

      /// <summary>
      /// Degree of servor position 
      /// </summary>
      /// <param name="servo">0 or 2<param>
      /// <param name="value">raw or degree angle<param>
      /// <param name="degree">
      /// true = value is for degrees, else raw 8-bit value
      /// </param>
      void Position(uint8, uint16, bool degree = true);

    protected:
      
    private:    
      uint8 _timer;
  };
};

#endif
