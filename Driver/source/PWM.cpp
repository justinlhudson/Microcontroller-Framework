extern "C"
{
  #include "System/include/Tools.h"
}

#include "Core/include/Configuration.h"

#include "Core/include/Application.hpp"
using namespace Core;

#include "../include/PWM.hpp"
using namespace Driver;

#define OCRn_PER_SPEED(x)             (x)

Motor::PWM(uint8 timer)
{
  _timer = timer;

  CRITICAL_SECTION_ENTER();
  {
    if(_timer == 2)
    {
      // Fast PWM, Phase Correct, clear
      TCCR2A = (1<<COM2A1)|(0<<COM2A0)|(1<<COM2B1)|(0<<COM2B0)|(0<<WGM21)|(1<<WGM20);
      TCCR2B = (0<<CS22)|(1<<CS21)|(0<<CS20)|(0<<WGM22);  // prescale 8
#if defined(__AVR_ATmega2560__)
      PORT_SET(DDRB, (1<<PB4)); // make pin output
      PORT_SET(DDRH, (1<<PH6));
#endif
    }
  }
  CRITICAL_SECTION_EXIT();
}

Motor::~PWM(void)
{
}

void PWM::Speed(uint8 pwm, uint8 speed)
{
  // if interrupt occurs high byte of 16-bit register is lost,
  // procedure taken from datasheet example.
  uint8 sreg = SREG;

  uint8 value = OCRn_PER_SPEED(speed);

  CRITICAL_SECTION_ENTER();
  {
    if(_timer == 0)
    {
      if(pwm == 0)
        OCR2A = value;
      else if(pwm == 1)
        OCR2B = value;
    }
  }
  CRITICAL_SECTION_EXIT();

  SREG = sreg;
}

