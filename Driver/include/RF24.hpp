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
  /// <remarks>2.4GHz-2.4835GHz</remarks>
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

      inline void Standby(bool active) { active == true ? PORT_SET(*_port,(1<<_enablePin)): PORT_CLR(*_port,(1<<_enablePin)); DELAY_MS(5); }

      // rx on/off
      void Listen(bool);
      // tx complete
      bool isSent(void);
      // have data to read
      bool isAvailable(void);
      // scanning network for RX signal
      bool Detected(void);

      // 1- 125
      void SetAddress(const uint8*); // 5 bytes
      void SetChannel(uint8);

      static uint8 GetMaxChannel(void);

      static float GetFrequency(uint8);

      static uint8 GetPayloadSize(void);

      uint8 WritePayload(const uint8*, uint8 length=RF24::GetPayloadSize(), uint8 operation=NULL);
      uint8 ReadPayload(uint8*, uint8 length=RF24::GetPayloadSize());

      // tx & rx
      void Clear(void);

    protected:

    private:
      // is dynamic to allow talking with muiplte chips without wasting memory until needed
      SPI* _spi;

      uint8 _enablePin;  // ce
      reg8 *_port;
      reg8 *_ddr;

      // rf24
      void Configure(void);

      uint8 ReadRegister(uint8);
      uint8 ReadRegister(uint8, uint8*, uint8);

      uint8 WriteRegister(uint8, uint8);
      uint8 WriteRegister(uint8, const uint8*, uint8);

      // ON/OFF
      void Power(bool);
  };
};
#endif
