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

#include "../include/Operation.hpp"
using namespace Application;

Operation* operation = new Operation();

void Echo(object* value)
{
  intsys iptr = (intsys)value;  //cast objects
  int8 result = (int8)iptr;

  // report to screen what is being typed
  Trace::Instance()->Log(Trace::Operation,"%s", result);
}

void Setup(void)
{
  // LED on arduino
  PORT_SET(DDRB, (1<<PB7)); // output
  PORT_LOW(PORTB,1<<PB7); // low

  TRACE_LINE();  // example debug with line
}

void Loop(void)
{
  //Trace::Instance()->Log(Trace::Info, "*"); // heartbeat

  //ToDo: run operation queue worker process
  operation->Process();

  Delay(125);
}
