/*-----------------------------------------------------------------------------
 *
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 *
 * Description: Body File.
 *
 *-----------------------------------------------------------------------------
 */

#include <stdlib.h>

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

Command::Message Operation::Commander(Command::Message message)
{
  // ToDo:  switch for commands and for some place in thread pool for completion

  strcpy(message.Response, "NOK");
  if(strcmp(message.Command, "motor") == 0)
  {
      if(strcmp(message.Operation, "clockwise") == 0)
      {
        int8 value = (int8)atoi(message.Value);
        strcpy(message.Response, "OK");
      }
      else if(strcmp(message.Operation, "counterclockwise") == 0)
      {
        strcpy(message.Response, "OK");
      }
  }
  // update result to requester knows was success
  return message;
}

void Operation::Process(void)
{
  // Todo:  actually start to do stuff....
  Delay(250);
}
