/*! =========================================================================
      
      @file    CEvent_JoinNetworkGame.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_JOINNETWORKGAME_H_
#define _C_EVENT_JOINNETWORKGAME_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"
#include "CDatagram.h"
#include "CNetworkMgrS.h"
#include "CPacket_QueryForNetGames.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_JoinNetworkGame = nlFOURCODE('j','n','g','m');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_JoinNetworkGame : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_JoinNetworkGame(void);
    ~CEvent_JoinNetworkGame(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    /* PROPERTY DATA GOES HERE */
};


#endif  /* _C_EVENT_JOINNETWORKGAME_H_ */
