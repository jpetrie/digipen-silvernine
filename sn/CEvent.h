/*! =========================================================================
      
      @file    CEvent.h
      @brief   Interface to event base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_H_
#define _C_EVENT_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CScriptMgrS.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

// forward declarations
class CGameState;


/*  _________________________________________________________________________ */
class CEvent
/*! @brief Event base class.

    An event is any discrete action that can occur during the course of the
    game, either gameplay-related (viz., a "move this unit" event) or user
    interface-related ("open the options window"). A CEvent subclass contains
    the data describing an event, as well as the process for handling that
    event: the Handle() method.
    
    When an event session processes its pending events, it calls Handle() for
    each event in its queue, passing it a pointer to the session.
    
    Arguments cannot be passed to the constructors of CEvent subclasses; the
    preferred means of sending data with an event is to store the data in
    public member fields (properties).
*/
{ 
  // contracts
  nlCONTRACT_NOCOPY(CEvent);
  
  
  public:
    // typedefs
    typedef nsl::uint32_t  ID;
  
  
    // ct and dt
             CEvent(ID id);
    virtual ~CEvent(void);
    
    // accessors
    ID           Ident(void) const     { return (mID); }
    virtual bool NeedsAuth(void) const { return (false); }
    
    // handling
    virtual void Handle(CGameState *engine) = 0;
  
  
  private:
    const ID  mID;  
};


/*                                                                 prototypes
----------------------------------------------------------------------------- */

// fourcode generator
EXPORT int GetEventCode(char *evt);


#endif  /* _C_EVENT_H_ */
