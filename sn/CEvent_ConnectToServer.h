/*! =========================================================================
      
      @file    CEvent_ConnectToServer.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_CONNECTTOSERVER_H_
#define _C_EVENT_CONNECTTOSERVER_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_ConnectToServer = nlFOURCODE('c','t','s','v');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_ConnectToServer : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_ConnectToServer(void);
    ~CEvent_ConnectToServer(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    /* PROPERTY DATA GOES HERE */
};


#endif  /* _C_EVENT_CONNECTTOSERVER_H_ */
