/*! =========================================================================
      
      @file    CEvent_UnitDestroy.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_UNITDESTROY_H_
#define _C_EVENT_UNITDESTROY_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_UnitDestroy = nlFOURCODE('u','d','i','e');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_UnitDestroy : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_UnitDestroy(void);
    ~CEvent_UnitDestroy(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    CUnit *unit;
};


#endif  /* _C_EVENT_UNITDESTROY_H_ */
