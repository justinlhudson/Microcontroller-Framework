#include "../include/Trace.hpp"
#include "../include/SubjectObserverAbstract.hpp"
using namespace Service;

SubjectAbstract::SubjectAbstract()
{
  _observersSize = 0;
  _observersSizeMax = MAX_OBSERVERS;//maxObservers;

  for(uint8 i=0;i<_observersSizeMax;i++)
    _observers[i] = NULL;
}

SubjectAbstract::~SubjectAbstract()
{ 
}

bool SubjectAbstract::Attach(ObserverAbstract *observer)
{
  bool status = true;

  if(_observersSize < _observersSizeMax)
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
