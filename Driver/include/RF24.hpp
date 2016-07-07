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

#include "Core/include/Configuration.h"

#include "Service/include/Trace.hpp"
#include "Service/include/SPI.hpp"
using namespace Service;

namespace Driver
{
  /// <summary>
  /// RF24 Wifi
  /// </summary>
  /// <remarks></remarks>
  class RF24
  {
    public:
      /// <summary>
      /// Constructor
      /// </summary>
      /// <param name="port>port for pins/param>
      /// <param name="enablePin">chip enable pin/param>
      /// <param name="selectPin">SPI chip select pin</param>
      RF24(uint8, uint8, uint8);
      ~RF24(void);

    protected:
      
    private:
      SPI *_spi;
      uint8 _rxBuffer[RF24_BUFFER_LENGTH];
      uint8 _txBuffer[RF24_BUFFER_LENGTH];

      uint8 _enablePin;
      uint8 _selectPin;
      reg8 *_port;
      reg8 *_ddr;
  };
};
#endif
