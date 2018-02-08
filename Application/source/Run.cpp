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

Operation operation;


void Input(object* value)
{
  intsys iptr = (intsys)value;  //cast objects
  int8 input = (int8)iptr;

  Trace::Instance()->Log(Trace::Operation,"%c", input); //echo
  if(input == '\r') // screen terminal only send '\r' on <enter>
    Trace::Instance()->Log(Trace::Operation,"%c", '\n');
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
  operation.Process();
  Delay(125);  //just in-case function returns do not spin out of control
}
