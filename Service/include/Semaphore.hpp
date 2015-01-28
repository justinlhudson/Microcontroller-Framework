/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <stdio.h>
#include <string.h>

extern "C"
{
  #include "System/include/Types.h"
  #include "System/include/Semaphore.h"
}

namespace Service
{
  /// <summary>
  /// OS Dependent Semaphore (i.e. mutex) Operations.
  /// </summary>
  class Semaphore
  {
    public:

      /// <summary>
      /// Constructor
      /// </summary>
      /// <remarks>
      /// Single valued semaphore.
      /// </remarks>
      Semaphore();

      /// <summary>
      /// Destructor
      /// </summary>
      ~Semaphore();

      /// <summary>
      /// Lock critical section.
      /// </summary>
      /// <param name="timeout">
      /// Max. time in msec. to hold lock.
      /// </param>
      /// <returns>True if lock made, False if failed.</returns>
      /// <remarks>
      /// Defaults if no input paramenters.  Default is lock until released.
      /// Will timeout after to many faluires, but will retry.
      /// </remarks>
      bool SectionEnter(uintsys timeout = 0);

      /// <summary>
      /// Release lock.
      /// </summary>
      /// <returns>True if release was success, False if failed.</returns>
      /// <remarks>
      /// Will timeout after to many faluires, but will retry.
      /// </remarks>
      bool SectionExit(void);

    protected:

      /// <summary>
      /// Setup a new semaphore.
      /// </summary>
      /// <remarks>Destroy will be called if needed.</remarks>
      void Create(void);

      /// <summary>
      /// Destroy current semaphore setup.
      /// </summary>
      void Destroy(void);

    private:

      SEMAPHORE_HANDLE _semaphore;
      uint16 _flag;

  };
};
#endif

