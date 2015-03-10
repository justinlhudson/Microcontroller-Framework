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

  //ToDo:  setup controller pins for all the fun
}

Operation::~Operation(void)
{

}

Operation::Message Operation::Command(Message message)
{
  //ToDo:  switch for commands and for some place in thread pool for completion
  if(strcmp(message.Command, "steer") == 0)
  {
      if(strcmp(message.Operation, "left") == 0)
      {
        /*
        case "left":
        case "right":
        // Value will be a range or time value?
        default:
          message.Response = "NOK";
          break;
          */
      }
  }
      /*
    case "speed":
      switch(message.Operation)
      {
        case "up":
        case "down":
        // Value will be a range or time value?
        default:
          message.Response = "NOK";
          break;
      }
    case "sensor":
      switch(message.Operation)
      {
        case "center":
        case "left":
        case "right":
        // might just return value and scan entire time?
        default:
          message.Response = "NOK";
          break;
      }
    default:
      message.Response = "NOK";
      break;
  }
  */
  return message;
}

void Operation::Process(void)
{
  //ToDo:  controller operations, none command operations
  // have sensor scan for obsticles and send message if someting seen?
}