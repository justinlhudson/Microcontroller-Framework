/*-----------------------------------------------------------------------------
 * 
 * Released: <2016/07/07>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _SPI_HPP_
#define _SPI_HPP_

extern "C"
{
  #include "System/include/Types.h"
}

#include "Core/include/Configuration.h"

namespace Service
{
  /// <summary>
  /// SPI Operations. Device(s) communication.
  /// </summary>
  class SPI
  {
    public:

      /// <summary>
      /// Constructor
      /// </summary>
      SPI(void);

      /// <summary>
      /// Constructor
      /// </summary>
      /// <param name="usart">number of usart register (e.q. 0,1,...)</param>
      /// <param name="baud">rate</param>
      /// <remarks>8 bits, 1 stop, no parity</remarks>
      SPI(uint8, uint32);

      /// <summary>
      /// Destructor
      /// </summary>
      ~SPI(void);

      /// <summary>
      /// Send
      /// </summary>
      /// <param name="value">single character</param>
      void Send(int8);

      /// <summary>
      /// Send
      /// </summary>
      /// <param name="value">character string</param>
      /// <param name="length">character string length</param>
      void Send(const int8*, uintsys);

      /// <summary>
      /// Send
      /// </summary>
      /// <param name="value">single u/int32</param>
      void Send(int32);

      /// <summary>
      /// Send
      /// </summary>
      /// <param name="value">single float</param>
      /// <remarks>three decimal place accuracy</remarks>
      void Send(float);

      /// <summary>
      /// Input ready/waiting
      /// </summary>
      /// <returns>if character is waiting sent to USART</returns>
      bool IsAvailable(void);

      /// <summary>
      /// Receive
      /// </summary>
      /// <returns>single character</returns>
      /// <remarks>Hint: loop through with "IsAvalable" until empty</remarks>
      int8 Receive(void);

    private:

      static uint8 _flag;

      int8 _spi;

      void Initialize(uint32);
      void Reset(void);
  };
};
#endif
