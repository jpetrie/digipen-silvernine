/*! =========================================================================
      
      @file    CEvent_StopNetwork.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_STOPNETWORK_H_
#define _C_EVENT_STOPNETWORK_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_StopNetwork = nlFOURCODE('s','p','n','t');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_StopNetwork : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_StopNetwork(void);
    ~CEvent_StopNetwork(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    /* PROPERTY DATA GOES HERE */
};


#endif  /* _C_EVENT_STOPNETWORK_H_ */
