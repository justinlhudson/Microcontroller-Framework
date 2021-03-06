#include "System/include/Tools.h"

#include "../include/Trace.hpp"
using namespace Service;

//init static members
Trace* Trace::_instance = NULL;
//define singleton instance (to call contructor)
static Trace _singleton;

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
  if(_instance == NULL)
    _instance = &_singleton;
  return _instance;
}

void Trace::Activate()
{
  #if defined(TRACE_LEVEL)
    _level = (Trace::Option)TRACE_LEVEL;  //from compiler variable input
  #else
    _level = All;
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
  if(_level >= level)
  {
    _lock.SectionEnter();
    {
      intsys length = 0;
      int8 buffer[USART_BUFFER_LENGTH]; // faster/better on controller to not have to define each time to just set max
      memset(buffer,NULL_CHAR,ARRAY_SIZE(buffer));

      va_list args;
      va_start(args, format);
      length = vsnprintf(buffer, ARRAY_SIZE(buffer), format, args);
      //perror (buffer);
      va_end(args);

      if(_display)
      {
        for(intsys i=0; i < length; i++)
        {
           int8 buf = buffer[i];
           _usart->Send(buf);
        }
      }
    }
    _lock.SectionExit();
  }

  return true;
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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
    Notify((void*)result);
#pragma GCC diagnostic pop

  }

  Delay(25);
}

