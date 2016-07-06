#include "../include/SPI.hpp"
using namespace Service;

extern "C"
{
  #include "System/include/SPI.h"
}

SPI::SPI(uint32 clock, uint8 mode, BitOrder bitOrder)
{
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