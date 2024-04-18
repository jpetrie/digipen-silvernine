/*! =========================================================================
      
      @file    CEvent_HostNetworkGame.h
      @brief   Specification for the HostNetworkGame Event
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_HOSTNETWORKGAME_H_
#define _C_EVENT_HOSTNETWORKGAME_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"
#include "CDatagram.h"
#include "CNetworkMgrS.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_HostNetworkGame = nlFOURCODE('h','n','t','g');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_HostNetworkGame : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_HostNetworkGame(void);
    ~CEvent_HostNetworkGame(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
};


#endif  /* _C_EVENT_HOSTNETWORKGAME_H_ */
