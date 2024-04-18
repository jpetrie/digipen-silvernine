/*! =========================================================================
      
      @file    CEvent_StartNetworkGame.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_STARTNETWORKGAME_H_
#define _C_EVENT_STARTNETWORKGAME_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_StartNetworkGame = nlFOURCODE('s','t','n','g');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_StartNetworkGame : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_StartNetworkGame(void);
    ~CEvent_StartNetworkGame(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    /* PROPERTY DATA GOES HERE */
};


#endif  /* _C_EVENT_STARTNETWORKGAME_H_ */
