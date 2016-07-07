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
      /// Defines bitorder configuration.
      /// </summary>
      enum BitOrder
      {
         LSBFIRST=0, MSBFIRST=1
      };

      /// <summary>
      /// Constructor
      /// </summary>
      /// <param name="clock">matches closest</param>
      /// <param name="mode">0,1,2,3</param>
      /// <param name="bitOrder">LSB, MSB</param>
      SPI(uint32 clock=4000000, uint8 mode=0, BitOrder bitorder=SPI::MSBFIRST);

      /// <summary>
      /// Destructor
      /// </summary>
      ~SPI(void);

      /// <summary>
      /// Transfer
      /// </summary>
      /// <param name="value">in</param>
      /// <returns>out</param>
      uint8 Transfer(uint8);

      /// <summary>
      /// Transfer
      /// </summary>
      /// <param name="buffer">in/out arrary</param>
      /// <param name="length"></param>
      void Transfer(uint8*, uint16);

    private:

  };
};
#endif
