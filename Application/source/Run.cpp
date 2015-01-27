/*-----------------------------------------------------------------------------
 * 
 * Released: <2014/01/26>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: Entry point!
 * 
 *-----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "System/include/Types.h"

#include "Service/include/Trace.hpp"
using namespace Service;

#include "Core/include/Application.hpp"
using namespace Core;

void Setup(void)
{
  // your setup code goes here
}

void Loop(void)
{
  // your runtime code goes here
  
  Trace::Instance()->Log(Trace::Info, "@")
  Delay(5);
}
