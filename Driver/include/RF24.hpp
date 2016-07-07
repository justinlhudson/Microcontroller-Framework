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

      // rx on/off
      void Listen(bool);

      // 1- 125
      void SetChannel(uint8);

      uint8 GetPayloadSize(void);

      uint8 WritePayload(const uint8*, uint8, uint8 operation=NULL);
      uint8 ReadPayload(uint8*, uint8);

    protected:
      
    private:
      SPI* _spi;
      uint8* _rxBuffer;
      uint8* _txBuffer;

      uint8 _enablePin;  // ce
      uint8 _selectPin;  // csn
      reg8 *_port;
      reg8 *_ddr;

      // rf24
      void Configure(void);

      // HIGH, LOW
      inline void EnablePin(uint8 value) { value == 1 ? PORT_SET(*_port,(1<<_enablePin)) : PORT_CLR(*_port,(1<<_enablePin)); };
      inline void SelectPin(uint8 value) { value == 1 ? PORT_SET(*_port,(1<<_selectPin)) : PORT_CLR(*_port,(1<<_selectPin)); };

      inline void StartTransacton(void) { SelectPin(LOW); EnablePin(HIGH); DELAY_MS(5); }
      inline void StopTransacton(void) { EnablePin(LOW); SelectPin(HIGH); }

      uint8 ReadRegister(uint8);
      uint8 ReadRegister(uint8, uint8*, uint8);

      uint8 WriteRegister(uint8, uint8);
      uint8 WriteRegister(uint8, const uint8*, uint8);
 
      // ON/OFF
      void Power(bool);

      // tx & rx
      void ClearBuffers(void);

  };
};
#endif
