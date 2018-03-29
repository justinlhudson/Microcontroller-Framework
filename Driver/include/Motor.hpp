/*-----------------------------------------------------------------------------
 *
 * Released: <20XX/XX/XX>
 * Modified: <YEAR/MONTH/DAY>
 *
 * Description:
 *
 *-----------------------------------------------------------------------------
 */

#ifndef _MOTOR_HPP_
#define _MOTOR_HPP_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

extern "C"
{
  #include "System/include/Definitions.h"
  #include "System/include/Types.h"
  #include "System/include/Tools.h"
}

#include "Service/include/Trace.hpp"
using namespace Service;

#define MOTOR_PINS 3

namespace Driver
{
  class Motor
  {
    public:
      inline Motor(uint8 port, uint8 pins[])
      {
        memcpy(_pins, pins, MOTOR_PINS * sizeof *_pins);

        //output, set low
        switch(port)
        {
          case 'C':
            _port = &PORTC;
            _ddr = &DDRC;
            break;
          case 'L':
            _port = &PORTL;
            _ddr = &DDRL;
            break;
          default:
            break;
        }

        CRITICAL_SECTION_ENTER();
        {
          // set pins as OUTPUT and LOW
          for(uint8 i=0; i<MOTOR_PINS; i++)
          {
            uint8 pin = _pins[i];
            PORT_HIGH(*_ddr,(1<<pin));
          }
          Action(Mode::Hold);
        }
        CRITICAL_SECTION_EXIT();
      }

      virtual ~Motor() {};

      enum class Mode : uint8
      {
        Clockwise = 0,
        CounterClockwise = 1,
        Hold = 3,
        Free = 4
      };

      inline virtual void Action(Mode mode, uint16 cycles=1, float duty=1.0)
      {
        // Todo: actually test diretion or swith wires...
        switch(mode)
        {
          case Mode::Clockwise:
            PORT_HIGH(*_port,(1<<_pins[1]));
            PORT_LOW(*_port,(1<<_pins[2]));
            PWM(cycles, duty);
          break;
          case Mode::CounterClockwise:
            PORT_LOW(*_port,(1<<_pins[1]));
            PORT_HIGH(*_port,(1<<_pins[2]));
            PWM(cycles, duty);
          break;
          case Mode::Hold:
            PORT_HIGH(*_port,(1<<_pins[0]));
            PORT_HIGH(*_port,(1<<_pins[1]));
            PORT_HIGH(*_port,(1<<_pins[2]));
          break;
          case Mode::Free:
          default:
            PORT_LOW(*_port,(1<<_pins[0]));
            PORT_LOW(*_port,(1<<_pins[1]));
            PORT_LOW(*_port,(1<<_pins[2]));
          break;
        }
      }

    protected:
      uint8 _pins[MOTOR_PINS];
      volatile reg8 *_port;
      volatile reg8 *_ddr;

      // Bit Bang PWM...
      // Example: Duty = 100 ~= 10%
      inline void PWM(uint16 cycles, float duty)
      {
         if(cycles == 0)
           return;
         uint16 hz = 1000; // 1Khz
         for(uint8 x=0; x<=cycles;x++)
         {
            // time specific critical, so lock process
            //CRITICAL_SECTION_ENTER();
            {
              PORT_HIGH(*_port,(1<<_pins[0])); // on
              //DELAY_MS((uint16)hz*duty);
              Delay((uint16)hz*duty); // Approximately % duty cycle @ 1KHz
              PORT_LOW(*_port,(1<<_pins[0])); // off
            }
            //CRITICAL_SECTION_EXIT();
            if(cycles > 1)
              Delay((uint16)(hz - (hz*duty)));
            else
              break;
        }
      }
  };
};
#endif
