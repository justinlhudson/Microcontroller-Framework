/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/01/21>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _ABSTRACT_SUBJECT_OBSERVER_H_
#define _ABSTRACT_SUBJECT_OBSERVER_H_

#include <stdio.h>

#include "System/include/Types.h"

namespace Service
{
  class SubjectAbstract;

  /// <summary>
  /// Observer class.
  /// </summary>
  class ObserverAbstract
  {
    public:

      /// <summary>
      /// Virtual updater.
      /// </summary>
      /// <param name="value">Method to do update (i.e. callback) on.</param>
      virtual void Update(object *){};

      inline ObserverAbstract& operator=(const ObserverAbstract &source)
      {    
        if(this != &source) //if not itself
        {
          // Deallocate, allocate new space, copy values...
        }
        return *this;
      }

      inline bool operator==(const ObserverAbstract &other) const
      {
        return(*this == other);
      }

      inline bool operator!=(const ObserverAbstract &other) const
      {
        return !(*this == other);
      }

    protected:

      /// <summary>
      /// Constructor.
      /// </summary>
      ObserverAbstract(void){};

      /// <summary>
      /// Virtual Destructor.
      /// </summary>
      /// <remarks>
      /// Making virtual makes sure both desctructors get called from derived
      /// and the base class.
      /// </remarks>
      virtual ~ObserverAbstract(void){}; 

    private:

  };

  /// <summary>
  /// Subject class.
  /// </summary>
  class SubjectAbstract
  {
    public:

      /// <summary>
      /// Virtual attach.
      /// </summary>
      /// <param name="SubjectAbstract">Set observer to do update (i.e. callback) on.</param>
      virtual bool Attach(ObserverAbstract *);

      /// <summary>
      /// Virtual detach
      /// </summary>
      /// <param name="SubjectAbstract">Remove observer to do update (i.e. callback) on.</param>
      virtual void Detach(ObserverAbstract *);

      /// <summary>
      /// Virtual Notify
      /// </summary>
      /// <param name="value">Send value through "Update" method for all attached "Observers".</param>
      virtual void Notify(void *);

    protected:

      /// <summary>
      /// Constructor.
      /// </summary>
      SubjectAbstract();

      /// <summary>
      /// Descructor.
      /// </summary>
      /// <remarks>
      /// Making virtual makes sure both desctructors get called from derived
      /// and the base class.
      /// </remarks>
      virtual ~SubjectAbstract(void);

    private:

      uint8 _observersSizeMax;
      uint8 _observersSize;

      static const uint8 MAX_OBSERVERS = MAX_CLASS_OBSERVERS;

      ObserverAbstract *_observers[MAX_CLASS_OBSERVERS];
  };
};
#endif
