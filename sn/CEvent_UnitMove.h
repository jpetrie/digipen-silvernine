/*! =========================================================================
      
      @file    CEvent_UnitMove.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_UNITMOVE_H_
#define _C_EVENT_UNITMOVE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_UnitMove = nlFOURCODE('u','m','o','v');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_UnitMove : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_UnitMove(void);
    ~CEvent_UnitMove(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    std::vector< CUnit* > units;
    float                 x;
    float                 y;
};


#endif  /* _C_EVENT_UNITMOVE_H_ */
