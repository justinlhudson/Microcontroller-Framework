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

#include "../include/Command.hpp"
#include "../include/Operation.hpp"
using namespace Application;

Operation operation;
Command command;

void Echo(object* value)
{
  intsys iptr = (intsys)value;  //cast objects
  int8 input = (int8)iptr;

  int8 status = 0;
  Command::Message message = command.Encode(input, &status);

  if (status != 0)
  {
    message = operation.Commander(message);
    int8* message_str = command.Decode(message);
    Trace::Instance()->Log(Trace::Operation, "%s, \r\n", message_str);
  }
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
