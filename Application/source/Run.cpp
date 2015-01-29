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

extern "C"
{
  #include "System/include/Types.h"
  #include "System/include/Tools.h"
  #include "System/include/Definitions.h"
}

#include "Service/include/Trace.hpp"
using namespace Service;

#include "Core/include/Application.hpp"
using namespace Core;

void Echo(object *value)
{
  // debug echoes trace input char at a time

  intsys iptr = (intsys)value;  //cast objects
  int8 result = (int8)iptr;
  Trace::Instance()->Log(Trace::Info,"%s", result);
}

void Setup(void)
{
  // your setup code goes here

  TRACE_LINE();  // example debug with line
}

void Loop(void)
{
  // your runtime code goes here
  
  Trace::Instance()->Log(Trace::Info, "*");
  Delay(5);
}
