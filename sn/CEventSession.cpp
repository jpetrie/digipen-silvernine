/*! =========================================================================
      
      @file    CEventSession.cpp
      @brief   Implementation of event session base class.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CSessionMgrS.h"
#include "CEventSession.h"


/*                                                           member functions
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEventSession::CEventSession(void)
/*! @brief Default constructor.
*/
: mAlive(true)
{
  CSessionMgr->nRegisterSession(this);
}


/*  _________________________________________________________________________ */
CEventSession::~CEventSession(void)
/*! @brief Destructor.
*/
{
  CSessionMgr->nUnregisterSession(this);
  
  // Release pending events.
  while(!mEvents.empty())
  {
  CEvent *tEvent = mEvents.front();
  
    delete tEvent;
    mEvents.pop();
  }
}


/*  _________________________________________________________________________ */
void CEventSession::ProcessEvents(void)
/*! @brief Handle all pending events.
*/
{
  while(!mEvents.empty())
  {
  CEvent *tEvent = mEvents.front();
  
    tEvent->Handle(this);
    delete tEvent;
    mEvents.pop();
  }
}


/*  _________________________________________________________________________ */
void CEventSession::InsertEvent(CEvent *evt)
/*! @brief Insert an event.

    No action is taken if evt is null or the session is inactive.
    
    The newly-enqueued event will be handled the next the session manager calls
    ProcessEvents() on this session.
    
    @param evt  The event to insert.
*/
{
  if(mAlive && 0 != evt)
    mEvents.push(evt);
}
