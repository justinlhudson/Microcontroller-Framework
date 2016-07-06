#include "../include/SPI.hpp"
using namespace Service;

extern "C"
{
  #include "System/include/SPI.h"
}

SPI::SPI(uint32 clock, uint8 mode, BitOrder bitOrder)
{
  switch (mode)
  {
    case 0:
      mode = SPI_MODE0;
      break;
    case 1:
      mode = SPI_MODE1;
      break;
    case 2:
      mode = SPI_MODE2;
      break;
    case 3:
      mode = SPI_MODE3;
      break;
    default:
      mode = SPI_MODE0;
      break;
  }

  SPI_Initialize(clock, mode, bitOrder);
}

SPI::~SPI(void)
{
  SPI_DeInitialize();
}

uint8 SPI::Transfer(uint8 value)
{
  return SPI_Transfer_Single(value);
}

void SPI::Transfer(uint8* buffer, uint16 count)
{
  SPI_Transfer(buffer, count);
}