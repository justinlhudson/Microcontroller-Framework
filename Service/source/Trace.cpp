#include "System/include/Tools.h"

#include "../include/Trace.hpp"
using namespace Service;

//init static members
Trace* Trace::_instance = 0;
//define singleton instance (to call contructor)
static Trace _singleton;

const uint32 Trace::MaxLength = USART_BUFFER_LENGTH;

/*
#if BOARD_TYPE == BOARD_ARDUINO_UNO
  Trace::Trace(uint32 baud) : SubjectAbstract(), ThreadAbstract(),
    _level(Trace::None), _display(true)
  {
    Serial.begin((long)baud);
    while (!Serial) { ; } // wait for serial port to connect.

    Activate();
  }
#else
*/
Trace::Trace(uint8 usart, uint32 baud) : SubjectAbstract(), ThreadAbstract(),
_level(Trace::None), _display(true)
{
  _usart = new USART(usart, baud);
  Activate();
}
//#endif

Trace::~Trace()
{  
  Deactivate();
  delete _usart;
}

Trace* Trace::Instance()
{
  if(_instance == 0)
    _instance = &_singleton;
  return _instance;
}

void Trace::Activate()
{ 
  #if defined(TRACE_LEVEL)
    _level = (Trace::Option)TRACE_LEVEL;  //from compiler variable input
  #else
    _level = Debug;
  #endif
    _display = true;

  Start(ThreadAbstract::Above);  //because buffer size is big is not higher
}

void Trace::Deactivate()
{

}

//printf("%s",buffer);
bool Trace::Log(Trace::Option level, const int8* format, ...)
{
  bool status = true;
  if(_level >= level)
  {
    _lock.SectionEnter();
    { 
      int32 length = 0;
      int8 buffer[Trace::MaxLength]; // faster/better on controller to not have to define each time to just set max
      memset(buffer,'\0',ARRAY_SIZE(buffer));

      va_list args;
      va_start(args, format);
      length = vsnprintf(buffer, ARRAY_SIZE(buffer), format, args);
      //perror (buffer);
      va_end(args);

      if(_display)
      {
        for(uintsys i=0;i<length;i++)
        {
           _usart->Send(buffer[i]);
        }
      }
    }
    _lock.SectionExit();
  }

  return status;
}

void Trace::Level(Trace::Option level)
{
  _level = level;
}

void Trace::Display(bool onOff)
{
  _display = onOff;
}

void Trace::Execute()
{
  while(_usart->IsAvailable())
  {
    int8 result = _usart->Receive();
    Notify((void*)result);
  }

  Delay(25);
}

