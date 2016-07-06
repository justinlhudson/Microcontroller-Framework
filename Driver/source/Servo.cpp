#include "Core/include/Configuration.h"

#include "Core/include/Application.hpp"
using namespace Core;

#include "../include/Servo.hpp"
using namespace Driver;

/*
  Specification: 50Hz period, 20ms width PWM period, with 1.5ms pulse width
                 for 90 degree, 1.0ms width for 0 degrees, and 2.0ms width
                 for 180 degrees.
*/

/* 
  Fudge Factor: Value taken by inspection using scope with below setup.
                ~1.0ms = 0 degrees, ~1.5ms = 90 degrees, and ~2.0ms = 180
                degrees 450 => 1ms, 700 => 1.5ms, and 2.0ms =>950 for OCRn
                values. Making ~2.8 value increment per degree...
*/

#define MAX_RANGE_DEGREE                (180)
#define OCRn_0_DEGREE                   (275)
#define OCRn_180_DEGREE                 (1050)
#define OCRn_PER_DEGREE(x)              (OCRn_0_DEGREE + ( ((OCRn_180_DEGREE - OCRn_0_DEGREE) / MAX_RANGE_DEGREE) * x) )

Servo::Servo(uint8 timer)
{
  _timer = timer;

  CRITICAL_SECTION_ENTER();
  {
    if(_timer == 2)
    {
      // PWM, Phase Correct, clear with TOP=>ICR
      TCCR3A = (1<<COM3A1)|(0<<COM3A0)|(1<<COM3B1)|(0<<COM3B0)|(1<<WGM31)|(0<<WGM30);
      TCCR3B = (0<<CS32)|(1<<CS31)|(0<<CS30)|(1<<WGM33)|(0<<WGM32);  // prescale 8
      ICR3 = 10000; // formula from data sheet...
#if defined(__AVR_ATmega2560__)
      DDRB  |= (1<<PB6)|(1<<PB7); // make pins output, same for most AVR chips
#endif
    }
  }
  CRITICAL_SECTION_EXIT();
}

Servo::~Servo(void)
{
}

void Servo::Position(uint8 servo, uint16 value, bool degree)
{
  // if interrupt occurs high byte of 16-bit register is lost,
  // procedure taken from datasheet example.
  uint8 sreg = SREG;

  uint16 number = value;
  if(degree)
  {
    //some checks
    if(value > 180)
      value = 180;
    else if(value <= 0)
      value = 0;

    number = OCRn_PER_DEGREE(value);
  }

  CRITICAL_SECTION_ENTER();
  {
    if(_timer == 2)
    {
      if(servo == 0)
        OCR2A = number;
      else if(servo == 1)
        OCR2B = number;
    }
  }
  CRITICAL_SECTION_EXIT();

  SREG = sreg;
}

