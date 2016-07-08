#include "../include/SPI.hpp"
using namespace Service;

extern "C"
{
  #include "System/include/SPI.h"
}

SPI::SPI(uint8 selectPort, uint8 selectPin, uint32 clock, uint8 mode, BitOrder bitOrder)
{
  _selectPin = selectPin;

  //output, set low
  switch(selectPort)
  {
    case 'A':
      break;
      _port = &PORTA;
      _ddr = &DDRA;
    case 'C':
      _port = &PORTC;
      _ddr = &DDRC;
      break;
    case 'D':
      _ddr = &DDRD;
      _port = &PORTD;
      break;
    default:
      break;
  }

  // set pin as OUTPUT
  PORT_SET(*_ddr,(1<<_selectPin));

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

  _lock.SectionEnter();
  {
    SelectPin(true);
    SPI_Initialize(clock, mode, bitOrder);
    SelectPin(false);
  }
  _lock.SectionExit();
}

SPI::~SPI(void)
{
  _lock.SectionEnter();
  {
    SelectPin(true);
    SPI_DeInitialize();
    SelectPin(false);
  }
  _lock.SectionExit();
}

uint8 SPI::Transfer(uint8 value)
{
  uint8 result=NULL;
  _lock.SectionEnter();
  {
    SelectPin(true);
    result = SPI_Transfer_Single(value);
    SelectPin(false);
  }
  _lock.SectionExit();
  return result;
}

void SPI::Transfer(uint8* buffer, uint16 length)
{
  _lock.SectionEnter();
  {
    SelectPin(true);
    SPI_Transfer_Muiltiple(buffer, length);
    SelectPin(false);
  }
  _lock.SectionExit();
}