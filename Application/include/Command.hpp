/*-----------------------------------------------------------------------------
 *
 * Released: <20XX/XX/XX>
 * Modified: <YEAR/MONTH/DAY>
 *
 * Description:
 *
 *-----------------------------------------------------------------------------
 */

#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

extern "C"
{
  #include "System/include/Types.h"
}

#include "Service/include/Semaphore.hpp"
#include "Service/include/Trace.hpp"
using namespace Service;

namespace Application
{
  class Command
  {
    public:

      /// <summary>
      /// Define message type
      /// </summary>
      /// <remarks>
      /// Example:
      ///   Command=motor, Operation=clockwise/counterclockwise, Value=90
      ///   Response=Ok/NOK
      /// </remarks>
      struct Message
      {
          int8 Command[8];
          int8 Operation[8];
          int8 Value[32];  // can be string or number
          int8 Response[8];
      };

      inline Message Encode(int8 input, int8* status)
      {
        static Command::Message message;
        static int8 index = 0;
        static int8 parse = 0;

        *status = 0;

        if (index == 0)
          memset(&message, 0, sizeof(message));  // zero/NULL out message

        if (input  == ',') // seperator in string command
        {
          parse++;
        }
        else if (input == '\r')
        {
          // ignore return code
        }
        else if (input  == '\n') // end of command
        {
          if (parse == 3) // make sure was a correctly formated command
          {
            *status = 1;
            return message;
          }

          index = 0;
          parse = 0;
        }
        else // parse into proper field
        {
          if(parse == 0)
            message.Command[index] = input;
          if(parse == 1)
            message.Operation[index] = input;
          if(parse == 2)
            message.Value[index] = input;
          if(parse == 3)
            message.Response[index] = input;

          index++;
        }
        return message;
      }

      inline int8* Decode(Message message)
      {
        int8 message_str[sizeof(message)];
        memset(&message_str, 0, sizeof(message_str));

        strcpy(message_str, message.Command);
        strcat(message_str, message.Operation);
        strcat(message_str, message.Value);
        strcat(message_str, message.Response);

        return message_str;
      }
  };
};
#endif
