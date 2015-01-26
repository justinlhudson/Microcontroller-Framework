/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: Body file.
 * 
 *-----------------------------------------------------------------------------
 */

#include "Service/include/ThreadAbstract.hpp"
#include "../include/Semaphore.hpp"
using namespace Service;

Semaphore::Semaphore():
_semaphore(NULL), _flag(0)
{  
  Create();
}

Semaphore::~Semaphore()
{
  Destroy();
}

void Semaphore::Create(void)
{ 
  bool status = false;
  if(_semaphore != NULL) //semaphore already exists, destroy it
    Destroy();
  // create and initialize the new semaphore
  SEMAPHORE_OPEN(_semaphore, status);
  (void)status;
}

void Semaphore::Destroy(void)
{ 

}

bool Semaphore::SectionExit(void)
{
  bool status = false;

  status = SEMAPHORE_POST(_semaphore);

  _flag--;
  if(_flag < 0)  //pre-caution
    _flag = 0;

  return status;
}

bool Semaphore::SectionEnter(uintsys timeout)
{
  const uint8 RETRIES = 10;
  bool status = false;  // status flag
  uint8 counter = RETRIES;  // counter for retries

  do
  {
    if(timeout > 0)
      status = SEMAPHORE_TRY_WAIT(_semaphore, timeout);  //timeout is in msec
    else
      status = SEMAPHORE_WAIT(_semaphore);

    if(status == false)
      Delay(0); //yeild, might be released after other task execute
  }
  while((counter-- > 0) && (status == false));

  // if all else fails this will hold process from continueing, if failed to do semaphore
  _flag++;
  if(counter <= 0)
  {
    while(_flag > 0)
    {
      if(timeout == 0)
        Delay(0);
      else
      {
        Delay(timeout);
        break;
      }
    }
  }

  return(status);
}

