/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#include "../include/WDT.hpp"
using namespace Service;

extern "C" 
{
#include "System/include/WDT.h"
}

uint16 WDT::m_timeout = 0;  //default => 8sec
bool WDT::m_flag = false;  // on/off

void WDT::Interval(uint16 timeout)
{    
  m_timeout = timeout;
  WDT::Reset();
}

void WDT::Reset(void)
{
  if((m_timeout != 0) && (m_flag == true))
    WDT_Reset();
}

void WDT::On(void)
{  
  WDT_On(m_timeout);
  m_flag = true;
}

void WDT::Off(void)
{
  WDT_Off();
  m_flag = false;
}

