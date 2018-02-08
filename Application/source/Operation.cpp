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

void Operation::Process(void)
{
  // Todo:  actually start to do stuff....
  Delay(250);
}
