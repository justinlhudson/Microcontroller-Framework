/*-----------------------------------------------------------------------------
 * 
 * Released: <2016/07/07>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _SPI_H_
#define _SPI_H_

#include "Types.h"

// Init. options...
#define SPI_LSBFIRST 0
#define SPI_MSBFIRST 1

// see data sheet for mode explanation
#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

void SPI_Initialize(uint32,uint8,uint8);
void SPI_DeInitialize(void);
uint8 SPI_Transfer_Single(uint8);
void SPI_Transfer_Muiltiple(uint8*, uint16);

#endif
