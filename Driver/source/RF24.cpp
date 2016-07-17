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

RF24::RF24(uint8 port, uint8 enablePin, uint8 selectPin)
{
  _enablePin = enablePin;

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

  _spi = new SPI(port,selectPin);

  // tx/rx off on start
  Standby(true);
  // wake up!
  Power(true);

  Configure();
}

RF24::~RF24(void)
{
  // do not use power if not running
  Power(false);
  delete _spi;
}

uint8 RF24::GetPayloadSize(void)
{
  return PAYLOAD_SIZE;
}

void RF24::Configure(void)
{
  WriteRegister(EN_AA, 0x00);  //disable auto ACK (plus only), also disables retry

  WriteRegister(SETUP_AW, 0x11);  // 5 byte address (max)

  // RX
  WriteRegister(EN_RXADDR, ReadRegister(EN_RXADDR) | (1>>ERX_P0)); // Enable RX on pipe0

  uint8 setup = ReadRegister(RF_SETUP);
  setup &= ~( (1<<RF_DR_LOW) | (1<<RF_DR_HIGH) );  // 1Mbps = 0b00
  setup |= (1<<RF_PWR_LOW) | (1<<RF_PWR_HIGH); // 0dBm  max! = 0b11
  WriteRegister(RF_SETUP, setup);

  WriteRegister(RX_PW_P0,GetPayloadSize());
}

bool RF24::isAvailable(void)
{
  if (!( ReadRegister(FIFO_STATUS) & (1<<RX_EMPTY) ))
    return true;
  return false;
}

// RPD - receved power level above -64 dBm
// CD - carrier detect line found
bool RF24::Detected(void)
{
  return (ReadRegister(RPD) & 1) | (ReadRegister(CD) & 1);
}

// RX on/off
void RF24::Listen(bool active)
{
  uint8 config = ReadRegister(NRF_CONFIG);

  Standby(false);

  // check if already on
  if(active == false && (config & (1<<PRIM_RX)))
    PORT_TOGGLE(config,(1<<PRIM_RX));
  // check if already off
  else if (active == true && (config & (1<<PRIM_RX)))
    PORT_TOGGLE(config,(1<<PRIM_RX));

  WriteRegister(NRF_CONFIG, &config, 1);

  ClearBuffers();
}

void RF24::ClearBuffers(void)
{
  _spi->Transfer( FLUSH_TX );
  _spi->Transfer( FLUSH_RX );
}

// Note: address is for RX pipe to know is for it else ignores
void RF24::SetAddress(const uint8* address)
{
  WriteRegister(TX_ADDR, address, 5);
  WriteRegister(RX_ADDR_P0, address, 5);
}

// F0= 2400 + RF_CH [MHz]
void RF24::SetChannel(uint8 channel)
{
  if (channel <= MAX_CHANNEL)
  WriteRegister(RF_CHANNEL, channel);
}

uint8 RF24::WritePayload(const uint8* buffer, uint8 length, uint8 operation)
{
  uint8 status;
  length = length < GetPayloadSize() ? length : GetPayloadSize();
  // for padding if data length less then payload
  uint8 blank_length = GetPayloadSize() - length;

  Standby(false);

  if (operation == NULL)
    operation= WRITE_TX_PAYLOAD;
  status = _spi->Transfer( operation );
  while ( length-- )
    _spi->Transfer(*buffer++);
  while ( blank_length-- )
    _spi->Transfer(PADDING);

  return status;
}

uint8 RF24::ReadPayload(uint8* buffer, uint8 length)
{
  uint8 status;
  length = length < GetPayloadSize() ? length : GetPayloadSize();
  // for padding if data length less then payload
  uint8 blank_length = GetPayloadSize() - length;

  Standby(false);

  status = _spi->Transfer( READ_RX_PAYLOAD );
  while ( length-- )
    *buffer++ = _spi->Transfer(DONTCARE);
  while ( blank_length-- )
    _spi->Transfer(DONTCARE);

  return status;
}

uint8 RF24::ReadRegister(uint8 location)
{
  uint8 data[5];
  ReadRegister(location,data,1);
  return data[0];
}

uint8 RF24::ReadRegister(uint8 location, uint8* buffer, uint8 length)
{
  uint8 status;

  status = _spi->Transfer( READ_REGISTER | ( REGISTER_MASK & location ) );
  while ( length-- )
    *buffer++ = _spi->Transfer(DONTCARE);

  return status;
}

uint8 RF24::WriteRegister(uint8 location, uint8 value)
{
  uint8 data[5];
  data[0] = value;

  return WriteRegister(location, data, 1);
}

uint8 RF24::WriteRegister(uint8 location, const uint8* buffer, uint8 length)
{
  uint8 status;

  status = _spi->Transfer( WRITE_REGISTER | ( REGISTER_MASK & location ) );
  while ( length-- )
    _spi->Transfer(*buffer++);

  return status;
}

void RF24::Power(bool active)
{
   uint8 config = ReadRegister(NRF_CONFIG);

   // if not powered up then power up and standy for the radio to initialize
   if ( active == true && !(config & (1<<PWR_UP)) )
   {
      WriteRegister(NRF_CONFIG, config | (1<<PWR_UP));
      DELAY_MS(5); // per datasheet
      Standby(false);
   } else if (active == false)
   {
     Standby(true);
     WriteRegister(NRF_CONFIG,config & ~(1<<PWR_UP));
   }
}
