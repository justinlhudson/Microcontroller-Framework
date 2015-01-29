/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/04/16>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#include "../include/RelativeTimeClock.hpp"
using namespace Component;

//init static members
RelativeTimeClock* RelativeTimeClock::_instance = NULL;
//define singleton instance (to call contructor)
static RelativeTimeClock _singleton;

RelativeTimeClock::RelativeTimeClock(void) : ThreadAbstract(),
_active(true)
{
  Reset();
  Start(ThreadAbstract::RealTime);
}

RelativeTimeClock::~RelativeTimeClock(void)
{
  ;
}

RelativeTimeClock* RelativeTimeClock::Instance() 
{
  if(_instance == 0)
    _instance = &_singleton;
  return _instance;
}

void RelativeTimeClock::Reset(void)
{
  memset(&_timeSpan,0,sizeof(RelativeTimeClock::TimeSpan_t));
}

void RelativeTimeClock::On(void)
{
  _active = true;
}

void RelativeTimeClock::Off(void)
{
  _active = false;
}

bool RelativeTimeClock::Set(RelativeTimeClock::TimeSpan_t timeSpan)
{
  bool status = true;

  _timeSpan = timeSpan;

  return status;
}

RelativeTimeClock::TimeSpan_t RelativeTimeClock::Get(void)
{
  return _timeSpan;
}

void RelativeTimeClock::Execute(void)
{
  Delay(995); //~1.00 sec (just under)

  if(_active)
  {  
    _timeSpan.Second++;

    if(_timeSpan.Second > 59)
    {
      _timeSpan.Second -= 60;
      _timeSpan.Minute++;
    }
    
    if(_timeSpan.Minute > 59)
    {
      _timeSpan.Minute -= 60;
      _timeSpan.Hour++;
    }
    
    if(_timeSpan.Hour > 23)
    {
      _timeSpan.Hour -= 24;
      _timeSpan.Day++;
    }
    
    if(_timeSpan.Day > 365)
    {
      _timeSpan.Day -= 365;
      _timeSpan.Year++;
    }
  }
  //send to any subjects
  //Notify((void*)&_timeSpan);
}
