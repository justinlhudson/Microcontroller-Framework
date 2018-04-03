/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _EEPROM_HPP_
#define _EEPROM_HPP_

extern "C"
{
  #include "System/include/Types.h"
}

namespace Service
{
  /// <summary>
  /// Static Class
  /// </summary>
  class EEPROM
  {
    public:

      /// <summary>
      /// Write to EEPROM
      /// </summary>
      /// <param name="data" />
      /// <param name="address" />
      static void Store(int8, uintsys);

      /// <summary>
      /// Read from EEPROM
      /// </summary>
      /// <param name="address" />
      /// <returns>u/int8 value stored</returns>
      static int8 Load(uintsys);

      /// <summary>
      /// Write to EEPROM
      /// </summary>
      /// <param name="data" />
      /// <param name="length" />
      /// <param name="address" />
      static void Store(const int8*, int8, uintsys);

      /// <summary>
      /// Read from EEPROM
      /// </summary>
      /// <param name="data">return values to buffer pointer</param>
      /// <param name="length" />
      /// <param name="address" />
      static void Load(int8*, int8, uintsys);

      /// <summary>
      /// Get/Set
      /// </summary>
      /// <param name="size">
      /// number of bytes to consider to be a chunk. 
      /// if zero just returns current value, else will set to new value.
      /// </param>
      /// <returns>bytes in 1 chunk</returns>
      /// <remarks>usaually try to be set at 1 line of EEPROM, is the default</remarks>
      static uint16 ChunkSize(uint16 size = 0);

      /// <summary>
      /// Read Chunk from EEPROM
      /// </summary>
      /// <param name="data">return values to buffer</param>
      /// <param name="chunk" />
      static void LoadChunk(int8*, uint16);

      /// <summary>
      /// Store Chunk to EEPROM
      /// </summary>
      /// <param name="data" />
      /// <param name="chunk" />
      static void StoreChunk(const int8*, uint16);

    private:

      static uint16 _chunkSize;
  };
};

#endif