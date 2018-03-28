/*-----------------------------------------------------------------------------
 *
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 *
 * Description: Body File.
 *
 *-----------------------------------------------------------------------------
 */

extern "C"
{
  #include "System/include/Tools.h"
}

#include "Service/include/EEPROM.hpp"
#include "Service/include/ThreadPool.hpp"
using namespace Service;

#include "../include/Application.hpp"
using namespace Core;


Application::Application(void) : ThreadAbstract(), ObserverAbstract()
{
  _trace = Trace::Instance();
  _trace->Attach(this);

  Start(ThreadAbstract::Highest);
}

Application::~Application(void)
{

}

void Application::Update(object *value)
{
  Input(value);
}

void Application::PreExecute(void)
{
  Setup();
}

void Application::Execute(void)
{
  Loop();
}
