extern "C" 
{
  #include "System/include/Definitions.h"
  #include "System/include/Tools.h"
}

#include "Core/include/Configuration.h"
#include "Core/include/Application.hpp"
using namespace Core;

#include "../include/RF24.hpp"
#include "../include/nRF24L01.h"
using namespace Driver;

#define Delay               75

RF24::RF24(uint8 port, uint8 enablePin, uint8 selectPin)
{
  _enablePin = enablePin;
  _selectPin = selectPin;

  //output, set low
  switch(port)
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

  // set pins as OUTPUT
  PORT_SET(*_ddr,(1<<_enablePin));
  PORT_SET(*_ddr,(1<<_selectPin));

  _spi = new SPI();
}

RF24::~RF24(void)
{
  delete _spi;
}

uint8 RF24::GetPayloadSize(void)
{
  return PAYLOAD_SIZE;
}

void RF24::Setup(void)
{
  //begin
}

// start listenting, stop listening, read payload
// write payload
// power up, power down


void RF24::ClearBuffers(void)
{
  StartTransacton();
  _spi->Transfer( FLUSH_TX );
  _spi->Transfer( FLUSH_RX );
  StopTransacton();
}

void RF24::SetChannel(uint8 channel)
{
  if (channel <= MAX_CHANNEL)
  WriteRegister(RF_CHANNEL, channel);
}

uint8 RF24::WritePayload(const uint8* buffer, uint8 length, const uint8 operation)
{
  uint8 status;
  length = length < GetPayloadSize() ? length : GetPayloadSize();
  // for padding if data length less then payload
  uint8 blank_length = GetPayloadSize() - length;

  StartTransacton();
  status = _spi->Transfer( operation );
  while ( length-- )
    _spi->Transfer(*buffer++);
  while ( blank_length-- )
    _spi->Transfer(PADDING);
  StopTransacton();

  return status;
}

uint8 RF24::ReadPayload(uint8* buffer, uint8 length)
{
  uint8 status;
  length = length < GetPayloadSize() ? length : GetPayloadSize();
  // for padding if data length less then payload
  uint8 blank_length = GetPayloadSize() - length;

  StartTransacton();
  status = _spi->Transfer( READ_RX_PAYLOAD );
  while ( length-- )
    *buffer++ = _spi->Transfer(DONTCARE);
  while ( blank_length-- )
    _spi->Transfer(DONTCARE);
  StopTransacton();

  return status;
}

uint8 RF24::ReadRegister(uint8 location, uint8* buffer, uint8 length)
{
  uint8 status;

  StartTransacton();
  status = _spi->Transfer( READ_REGISTER | ( REGISTER_MASK & location ) );
  while ( length-- )
    *buffer++ = _spi->Transfer(DONTCARE);
  StopTransacton();

  return status;
}

uint8 RF24::WriteRegister(uint8 location, uint8 value)
{
  unsigned char data[5];
  data[0] = value;

  return WriteRegister(location, data, 1);
}

uint8 RF24::WriteRegister(uint8 location, const uint8* buffer, uint8 length)
{
  uint8 status;

  StartTransacton();
  status = _spi->Transfer( WRITE_REGISTER | ( REGISTER_MASK & location ) );
  while ( length-- )
    _spi->Transfer(*buffer++);
  StopTransacton();
  
  return status;
}
