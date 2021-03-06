#include "../include/Trace.hpp"
#include "../include/SubjectObserverAbstract.hpp"
using namespace Service;

SubjectAbstract::SubjectAbstract()
{
  _observersSize = 0;

  for(uint8 i = 0;i < MAX_OBSERVERS;i++)
    _observers[i] = NULL;
}

SubjectAbstract::~SubjectAbstract()
{ 
}

bool SubjectAbstract::Attach(ObserverAbstract *observer)
{
  bool status = true;

  if(_observersSize < MAX_OBSERVERS)
    _observers[_observersSize++] = observer;
  else
    status = false;

  return status;
}

void SubjectAbstract::Detach(ObserverAbstract *observer)
{
  for(uint8 i=0;i<_observersSize;i++)
    if(_observers[i] == observer)
      _observers[i] = NULL;
}

void SubjectAbstract::Notify(void *value)
{
  for(uint8 i=0;i<_observersSize;i++)
    if(_observers[i] != NULL)
    {
      ObserverAbstract *ptr = _observers[i];
      ptr->Update(value);
    }
}
