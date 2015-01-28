#include "../include/WDT.hpp"
using namespace Service;

extern "C"
{
  #include "System/include/WDT.h"
}

uint16 WDT::_timeout = 0;  //default => max
bool WDT::_flag = false;  // on/off

void WDT::Interval(uint16 timeout)
{
  _timeout = timeout;
  WDT::Reset();
}

void WDT::Reset(void)
{
  if((_timeout != 0) && (_flag == true))
    WDT_Reset();
}

void WDT::On(void)
{
  WDT_On(_timeout);
  _flag = true;
}

void WDT::Off(void)
{
  WDT_Off();
  _flag = false;
}
