/*-----------------------------------------------------------------------------
 * 
 * Released: <2016/06/04>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description:
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _RF24_HPP_
#define _RF24_HPP_

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
  #include <nRF24L01.h>
  #include <printf.h>
  #include <RF24.h>
  #include <RF24_config.h>

  /// <summary>
  /// RF24 Wifi
  /// </summary>
  /// <remarks></remarks>
  class RF24
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
      // ToDo: fix above commments!!!!!
      RF24(void);
      ~RF24(void);

    protected:
      
    private:
      

      uint8 _pin;
      reg8 *_port;
      reg8 *_ddr;
  };
};
#endif
