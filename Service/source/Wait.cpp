/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/04/11>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: Body File.
 * 
 *-----------------------------------------------------------------------------
 */

#include "../include/Wait.hpp"
using namespace Service;

Wait::Wait_t Wait::_map[MAX_TAGS];

Wait::Wait()
{
  for(uint8 i=0;i<MAX_TAGS;i++)
    Create(i); 
}

Wait::~Wait()
{

}

bool Wait::Sleep(uint8 tag, uintsys timeout, uint8 precision)
{
  bool status = true;

  _lock.SectionEnter();
  {
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
  }
  _lock.SectionExit();

  return status;
}

void Wait::Wakeup(uint8 tag)
{
  _lock.SectionEnter();
  {
    _map[tag].flag = true;
  }
  _lock.SectionExit();
}

bool Wait::Create(uint8 tag)
{
  bool status = true;

  _lock.SectionEnter();
  {
    Wait_t wait;

    wait.flag = false;
    _map[tag] = wait;
  }
  _lock.SectionExit();

  return status;
}

