/*-----------------------------------------------------------------------------
 * 
 * Released: <2014/01/27>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description:
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _ULTRA_SONIC_SENSOR_HPP_
#define _ULTRA_SONIC_SENSOR_HPP_

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
  /// Ultrasonic Distance Sensor
  /// </summary>
  /// <remarks>Model: Parallax #28015</remarks>
  class UltrasonicSensor
  {
    public:
      
      /// <summary>
      /// Constructor/Desctructor
      /// </summary>
      /// <param name="port">A, B, C, or D</param>
      /// <param name="pin">0-7</param>
      /// <param name="counter">
      /// which sytem time counter index to use
      /// </param> 
      /// <param name="tempurature">
      /// ampient tempurature in Celsius (e.g. 22 ~= 70 Fahrenheit)
      /// </param>
      /// <param name="error">percent error or fudge factor</param>
      /// <remarks>
      /// Note: error (fudge factor) can be used to calibrate with
      //  known distance, isntead of determining tempurature or what not for
      /// speed of sound changes.
      /// </remarks>
      UltrasonicSensor(int8 port='C', uint8 pin=0, int8 tempurature=22, float error= -0.10);
      ~UltrasonicSensor(void);

      /// <summary>
      /// Ping (and then get pong)
      /// </summary>
      /// </return>distance in centimeters.<return>
      float Ping(void);

    protected:
      
    private:
      
      int8  _tempurature;
      float _error;

      uint8 _pin;
      reg8 *_port;
      reg8 *_ddr;
  };
};
#endif
