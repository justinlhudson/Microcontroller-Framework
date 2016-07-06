#include "../include/USART.hpp"
using namespace Service;

extern "C"
{
  #include "System/include/USART.h"
}

uint8 USART::_flag = 0x00;  //so not to start more then once, init static variable

USART::USART(uint8 usart, uint32 baud)
{
  // keep track if usart alrady taken for usage
  if(!(_flag & (0x01 << usart))) // not already defined
  {
    _flag |= (0x01 << usart);
    _usart = usart;

    Initialize(baud);
  }
}

USART::~USART(void)
{
  //clear flag(s) when destroy object
  _flag &= ~(0x01 << _usart);
}

bool USART::IsAvailable(void)
{
  return USART_IsAvailable(_usart);
}

int8 USART::Receive(void)
{
  return USART_Receive(_usart);
}

void USART::Send(int8 value)
{
  USART_Send(_usart, value);
}

void USART::Send(const int8 *cString, uintsys length)
{
  //don't Receive stuck if it is a bad string, will cycle around to zero and overflow
  for(uintsys i=0;i<length;i++)
    Send(cString[i]);
}

void USART::Send(int32 value)
{
  int8 temp[10] = {'\0'};
  itoa(value, temp, 10); // base 10
  for(uint8 i=0; i<10; i++)
    Send(temp[i]);
}

//three decimal place accuracy
void USART::Send(float value)
{
  int32 tempI1 = 0;
  int32 tempI2 = 0;

  tempI1 = (int32)value;
  tempI2 = (int32)((value - tempI1) * 1000); // move decimal up

  Send(tempI1);
  Send('.');

  if(tempI2 < 100)
    Send('0');
  if(tempI2 < 10)
    Send('0');

  Send(tempI2);
}

void USART::Initialize(uint32 baud)
{
  USART_Initialize(_usart,baud);
}

void USART::Reset()
{
  USART_Reset(_usart);
}

