/*! =========================================================================
      
      @file    CEvent_UnitStop.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_UNITSTOP_H_
#define _C_EVENT_UNITSTOP_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_UnitStop = nlFOURCODE('u','s','t','p');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_UnitStop : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_UnitStop(void);
    ~CEvent_UnitStop(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    std::vector< CUnit* > units;
};


#endif  /* _C_EVENT_UNITSTOP_H_ */
