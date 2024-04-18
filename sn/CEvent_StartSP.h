/*! =========================================================================
      
      @file    CEvent_StartSP.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_STARTSP_H_
#define _C_EVENT_STARTSP_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_StartSP = nlFOURCODE('s','t','s','p');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_StartSP : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_StartSP(void);
    ~CEvent_StartSP(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    std::string  save;  // Name of saved game to load (empty string for new).
};


#endif  /* _C_EVENT_STARTSP_H_ */
