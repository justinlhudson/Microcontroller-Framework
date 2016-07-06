/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _USART_HPP_
#define _USART_HPP_

extern "C"
{
  #include "System/include/Types.h"
}

#include "Core/include/Configuration.h"

namespace Service
{
  /// <summary>
  /// USART (i.e. Seial) Operations.
  /// </summary>
  class USART
  {
    public:
      /// <summary>
      /// Constructor
      /// </summary>
      /// <param name="usart">number of usart register (e.q. 0,1,...) being used</param>
      /// <param name="baud">rate</param>
      /// <remarks>8 bits, 1 stop, no parity</remarks>
      USART(uint8 usart=0, uint32 baud=9600);

      /// <summary>
      /// Destructor
      /// </summary>
      ~USART(void);

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

      int8 _usart;

      void Initialize(uint32);
      void Reset(void);
  };
};
#endif
