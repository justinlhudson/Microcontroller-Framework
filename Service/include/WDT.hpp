/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _WDT_HPP_
#define _WDT_HPP_

#include "System/include/Types.h"

namespace Service
{
  /// <summary>
  /// Watch Dog Timer
  /// </summary>
  class WDT
  {
    public:
     
      /// <summary>
      /// On
      /// </summary>
      /// <remarks>timeout is set during this call</remarks>
      static void On(void);

      /// <summary>
      /// Off
      /// </summary>
      /// <remarks>prescale set to 0</remarks>
      static void Off(void);

      /// <summary>
      /// When to check "Reset" was called
      /// </summary>
      /// <param name="timeout">
      /// 16,32,64,128,250,500,1000,2000,4000,8000 msec.
      /// </param>
      static void Interval(uint16);

      /// <summary>
      /// Called to reset countdown to show system is not locked up.
      /// </summary>
      static void Reset(void);

    private:   
       
      static uint16 m_timeout;
      static bool m_flag;
  };
};

#endif
