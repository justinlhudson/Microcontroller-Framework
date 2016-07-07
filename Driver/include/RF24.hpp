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
      /// <param name="port">port for pins/param>
      /// <param name="enablePin">chip enable pin </param>
      /// <param name="selectPin">SPI chip select pin</param>
      RF24(uint8, uint8, uint8);
      ~RF24(void);

    protected:
      
    private:
      SPI *_spi;
      uint8 _rxBuffer[RF24_BUFFER_LENGTH];
      uint8 _txBuffer[RF24_BUFFER_LENGTH];

      uint8 _enablePin;  // ce
      uint8 _selectPin;  // csn
      reg8 *_port;
      reg8 *_ddr;

      // 1= high, 0=low 
      inline void EnablePin(uint8 value) { value == 1 ? PORT_SET(*_port,(1<<_enablePin)) : PORT_CLR(*_port,(1<<_enablePin)); };
      // 1= high, 0=low 
      inline void SelectPin(uint8 value) { value == 1 ? PORT_SET(*_port,(1<<_selectPin)) : PORT_CLR(*_port,(1<<_selectPin)); };

      inline void StartTransacton(void) { SelectPin(0); EnablePin(1); }
      inline void StopTransacton(void) { EnablePin(0); SelectPin(1); }

      /// <summary>
      /// Write register value to chip
      /// </summary>
      /// <param name="location">register/param>
      /// <param name="buffer">data</param>
      /// <param name="length">of buffer</param>
      uint8 WriteRegister(uint8, const uint8*, uint8);
  };
};
#endif
