/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/04/16>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _RELATIVE_TIME_CLOCK_HPP_
#define _RELATIVE_TIME_CLOCK_HPP_

extern "C"
{
  #include "System/include/Types.h"
}

#include "Service/include/Semaphore.hpp"
#include "Service/include/ThreadAbstract.hpp"
#include "Service/include/SubjectObserverAbstract.hpp"
using namespace Service;

namespace Component
{
  /// <summary>
  /// Relative ~ Time Clock.
  /// </summary>
  /// <remarks>
  /// Is relative, b/c is not exact clock tick. With tempurature
  /// and many other factors contribute to time drifting. For instance,
  /// on a test for 6 hours showed 35 second gain on the microcontroller at 
  /// ambient tempurateure.
  /// 
  /// Is a thread runner...
  /// </remarks>
  class RelativeTimeClock : protected ThreadAbstract
  {
    public:

      /// <summary>
      /// TimeSpan Structure Type
      /// </summary>
      struct TimeSpan_t
      {
        uint8  Second;
        uint8  Minute;
        uint8  Hour;
        uint16 Day;
        uint8  Year;

        TimeSpan_t()
        {
          Second=0;
          Minute=0;
          Hour=0;
          Day=0;
          Year=0;
        }
      };

      /// <summary>
      /// Constructor/Destructor.
      /// </summary>
      RelativeTimeClock();
      ~RelativeTimeClock();

      /// <summary>
      /// Defines singletion.
      /// </summary>
      /// <returns>object pointer</returns>
      static RelativeTimeClock *Instance();

      /// <summary>
      /// Active
      /// </summary>
      void On(void);

      /// <summary>
      /// Deactive
      /// </summary>
      void Off(void);

      /// <summary>
      /// Zero out clock and internal counter
      /// </summary>
      void Reset(void);

      /// <summary>
      /// Set start time
      /// </summary>
      /// <param name="timeout">
      /// seconds, minutes, hours, days
      /// </param>
      /// <returns></returns>
      bool Set(TimeSpan_t);

      /// <summary>
      /// Get elapsed time from set time.
      /// </summary>
      /// <returns> current time from set and/or reset</returns>
      TimeSpan_t Get(void);

    private:

      static RelativeTimeClock *_instance;

      TimeSpan_t _timeSpan;
      bool _active;

      void Execute(void);
  };
};

#endif
