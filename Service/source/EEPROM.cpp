#include <avr/eeprom.h>

// Note: lazy and used lib already included
#include "../include/EEPROM.hpp"
using namespace Service;

#define EEPROM_START                  0

uint16 EEPROM::_chunkSize = 0x0F;  //default chunk size, 1 line of EEPROM

uint16 EEPROM::ChunkSize(uint16 size)
{ 
  if(_chunkSize != 0) 
    _chunkSize = size;

  return _chunkSize;
} 

void EEPROM::LoadChunk(int8 *data, uint16 chunk)
{
  Load(data,_chunkSize,(_chunkSize*chunk)+1);
}
 
void EEPROM::StoreChunk(const int8 *data, uint16 chunk)
{
  Store(data,_chunkSize,(_chunkSize*chunk)+1);
}

void EEPROM::Store(const int8* data, int8 length, uintsys address)
{
  address += EEPROM_START;
  for(uint8 i=0; i<length; i++)
    Store(data[i],address+i);
}

void EEPROM::Load(int8 *data, int8 length, uintsys address)
{
  address += EEPROM_START;
  for(uint8 i=0; i<length; i++)
    data[i] = Load(address+i);
}

void EEPROM::Store(int8 value, uintsys address)
{ 
  eeprom_write_byte((unsigned char *) address, value);
}

int8 EEPROM::Load(uintsys address)
{
  return eeprom_read_byte((unsigned char *) address);
}