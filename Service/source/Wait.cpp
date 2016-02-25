#include "../include/Wait.hpp"
using namespace Service;

Wait::Wait_t Wait::_map[MAX_TAGS];

Wait::Wait()
{
  for(uint8 i=0; i<MAX_TAGS; i++)
    Create(i);
}

Wait::~Wait()
{

}

bool Wait::Sleep(uint8 tag, uintsys timeout, uint8 precision)
{
  bool status = true;

  intsys decrement = timeout;  //to have negative
  while(!_map[tag].flag)
  {
    if(timeout == 0)
    {
      ;
    }
    else
    {
      if(decrement <= 0)
        break;

      decrement = decrement - precision;
    }
    Delay(precision);
  }

  return status;
}

void Wait::Wakeup(uint8 tag)
{
  _map[tag].flag = true;
}

void Wait::Create(uint8 tag)
{
  Wait_t wait;

  wait.flag = false;
  _map[tag] = wait;
}

