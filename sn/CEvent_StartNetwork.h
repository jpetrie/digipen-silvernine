/*! =========================================================================

      @file    CEvent_StartNetwork.h
      @brief   yay
      
    ========================================================================= */
    
/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_STARTNETWORK_H_
#define _C_EVENT_STARTNETWORK_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"

#include "CUnit.h"
#include "CSocket.h"
#include "CNetworkMgrS.h"

/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_StartNetwork = nlFOURCODE('s','t','n','t');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_StartNetwork : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_StartNetwork(void);
    ~CEvent_StartNetwork(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    bool IAmServer;		// Are we the server?
};


#endif  /* _C_EVENT_STARTNETWORK_H_ */
