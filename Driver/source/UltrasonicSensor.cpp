/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/09/03>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: Body File.
 * 
 *-----------------------------------------------------------------------------
 */

extern "C" 
{
  #include "System/include/Definitions.h"
  #include "System/include/Tools.h"
}

#include "Core/include/Configuration.h"
#include "Core/include/Application.hpp"
using namespace Core;

#include "../include/UltrasonicSensor.hpp"
using namespace Driver;

/*
  Formula: time in us. for speed of sound at specific tempurature over us. to second conversion.
*/

// usec to seconds * speed of sound base on tempurature, half the distance (there adn back)
#define DISTANCE_METERS(time,tempurature)     ( (time / 1000000) * (331.5 + (0.6 * tempurature)) / 2 )

UltrasonicSensor::UltrasonicSensor(int8 port, uint8 pin, int8 tempurature, float error)
{  
  _tempurature = tempurature;
  _error = error;

  _pin = pin;

  //output, set low
  switch(port)
  {
    case 'A':
      break;
      _port = &PORTA;
      _ddr = &DDRA;
    case 'C':
      _port = &PORTC;
      _ddr = &DDRC;
      break;
    case 'D':
      _ddr = &DDRD;
      _port = &PORTD;
      break;
    default:
      break;
  }

}

UltrasonicSensor::~UltrasonicSensor(void)
{
}

// bit bang this one with tight timing tolerance
float UltrasonicSensor::Ping(void)
{
  uint32 i = 0;
  uint16 time = 0;

  PORT_SET(*_ddr, (1<<_pin));      // make pin output
  PORT_LOW(*_port, (1<<_pin));     // low to start
  DELAY_US(2);                     // stabalize low
  PORT_HIGH(*_port, (1<<_pin));    // high to activate
  DELAY_US(5);                     // delay 5us (2us min, 10us max)
  PORT_LOW(*_port, ~(1<<_pin));    // put pin low
  // for 3 pin
  PORT_CLR(*_ddr, (1<<_pin));      // make pin input
  PORT_CLR(*_port, (1<<_pin));     // pull-up input

  i = 1;
  while(!PORT_CHECK(*_port, (1<<_pin)) && ++i) NOP; // wait for pin high

  i = 1;
  do
  { 
    time++; // how many usec.
    DELAY_US(1);
  }while(PORT_CHECK(*_port, (1<<_pin)) && ++i); // wait for pin low

  float result = DISTANCE_METERS(time, _tempurature) * 100 * (1 + _error); // meters to centimeters

  return result;
}

