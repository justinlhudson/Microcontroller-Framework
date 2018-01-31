/*-----------------------------------------------------------------------------
 *
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 *
 * Description: Body File.
 *
 *-----------------------------------------------------------------------------
 */

extern "C"
{
  #include "System/include/Tools.h"
}

#include "../include/Operation.hpp"
using namespace Application;

Operation::Operation(void)
{
  _trace = Trace::Instance();
  _threadPool = ThreadPool::Instance();
}

Operation::~Operation(void)
{

}

/*
Operation::Message Operation::Command(Message message)
{
  // ToDo:  switch for commands and for some place in thread pool for completion
  if(strcmp(message.Command, "someCommand") == 0)
  {
      if(strcmp(message.Operation, "doThis") == 0)
      {
        //message.Response =;
      }
  }
  return message;
}
*/

void Operation::Process(void)
{
  // Todo:  actually start to do stuff....
  Delay(250);
}
