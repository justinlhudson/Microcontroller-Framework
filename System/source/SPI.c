#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "../include/Types.h"
#include "../include/Definitions.h"
#include "../include/Tools.h"

#include "../include/SPI.h"

#include "Core/include/Configuration.h"

static int8 _initilized=0;
//unit8 _sreg;

void SPI_Initialize(uint32 clock, uint8 mode, uint8 bitOrder)
{
  if (!_initilized)
  {
    uint8 spcr;
    uint8 spsr;
    uint8 mask=0;

    // select clock closest to requested rate, see char in datasheet
    if (clock >= CPU_FREQUENCY_HZ / 2)
      mask = (1<<SPI2X)|(0<<SPR1|0<<SPR0);
    else if (clock >= CPU_FREQUENCY_HZ / 4)
      mask = (0<<SPI2X)|(0<<SPR1|0<<SPR0);
    else if (clock >= CPU_FREQUENCY_HZ / 8)
      mask = (1<<SPI2X)|(0<<SPR1|1<<SPR0);  
    else if (clock >= CPU_FREQUENCY_HZ / 16)
      mask = (0<<SPI2X)|(0<<SPR1|1<<SPR0);
    else if (clock >= CPU_FREQUENCY_HZ / 32)
      mask = (1<<SPI2X)|(1<<SPR1|0<<SPR0);
    else if (clock >= CPU_FREQUENCY_HZ / 64)
      mask = (1<<SPI2X)|(1<<SPR1|1<<SPR0);
    else  // 128 (slowest if not found)
      mask = (0<<SPI2X)|(1<<SPR1|1<<SPR0);;

    //CRITICAL_SECTION_ENTER();
    {
      spcr = (1<<SPE) | (1<<MSTR) | ((bitOrder == 0) ? (1<<DORD) : 0) |
        (mode & (1<<CPOL|1<<CPHA)) | (0<<SPIE) | (mask & (1<<SPR1|1<<SPR0));
      spsr = mask & (1<<SPI2X);
    }
    //CRITICAL_SECTION_EXIT();

    CRITICAL_SECTION_ENTER();
    {
      // Warning: if the SS pin ever becomes a LOW INPUT then SPI
      // SS as output to not influence SPI operations

#if defined(__AVR_ATmega2560__)
      // Output
      PORT_SET(DDRB, (1<<PB0)); // SS
      PORT_SET(DDRB, (1<<PB1)); // SCK
      PORT_SET(DDRB, (1<<PB2)); // MOSI
      // Input
      PORT_CLR(DDRB, (1<<PB3)); // MISO

      // gain exclusive access to SPI
      PORT_SET(PORTB, (1<<PB0));  // SS slow to select chip is connected
#endif

      SPCR=spcr;
      SPSR=spsr;
    }
    CRITICAL_SECTION_EXIT();
  }
  _initilized++;
}

void SPI_DeInitialize(void)
{
  if (_initilized)
    _initilized--;
  else if (_initilized < 0)
    _initilized=0;

  // If there are no more references disable SPI
  if (!_initilized)
  {
    CRITICAL_SECTION_ENTER();
    {
      PORT_CLR(SPCR, (1<<SPE));  // low, release/disable SPI
    }
    CRITICAL_SECTION_EXIT();
  }
}

uint8 SPI_Transfer_Single(uint8 value)
{
  SPDR = value;
  // small delay to allow to send, might skip while
  NOP;
  while ( !(SPSR & (1<<SPIF)) ) ; // wait
  return SPDR;
}

void SPI_Transfer(uint8* buffer, uint16 count)
{
  if (count == 0) return;
  SPDR = *buffer;
  while (--count > 0) 
  {
    uint8 out = *(buffer + 1);
    while ( !(SPSR & (1<<SPIF)) ) ;
    uint8 in = SPDR;
    SPDR = out;
    *buffer++ = in;
  }
  while ( !(SPSR & (1<<SPIF)) ) ;
  *buffer = SPDR;
}
