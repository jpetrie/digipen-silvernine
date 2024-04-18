/*! =========================================================================
      
      @file    CEventSession.h
      @brief   Interface to event session base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTSESSION_H_
#define _C_EVENTSESSION_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventSession
/*! @brief Event session class.

    An event session represents a period of time during which simulation events
    occur and are handled. There are two types of things that can happen
    during the lifetime of an event session: an event, and an update. When
    these things occur is controlled by the session manager (a singleton of type
    CSessionMgrS).
    
    Updates are only processed at the beginning of a frame of time specified
    in (and tweakable from) the session manager. Updates happen via the
    ProcessUpdates() method.
    
    Events (subclasses of CEvent) are handled internally by the session (e.g.,
    the Handle() method of the CEvent is called) as often as possible.
*/
{
  // contracts
  nlCONTRACT_NOCOPY(CEventSession);
  
  
  public:
    // ct and dt
             CEventSession(void);
    virtual ~CEventSession(void);
    
    // lifetime
    bool Alive(void) const { return (mAlive); }
    void Alive(bool a)     { mAlive = a; }
    
    // processing
            void ProcessEvents(void);
    virtual void ProcessUpdates(void) = 0;
    
    // event insertion
    void InsertEvent(CEvent *evt);

  
  private:
    // typedefs
    typedef std::queue< CEvent* >  TEventQueue;
    
    
    // data members
    bool         mAlive;   // Is the session alive?
    TEventQueue  mEvents;  // Events waiting for processing.
};


#endif  /* _C_EVENTSESSION_H_ */
