/*! =========================================================================
      
      @file    CEvent_ArmySelectUnit.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_ARMYSELECTUNIT_H_
#define _C_EVENT_ARMYSELECTUNIT_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_ArmySelectUnit = nlFOURCODE('a','u','s','l');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_ArmySelectUnit : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_ArmySelectUnit(void);
    ~CEvent_ArmySelectUnit(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    int unit_index;
};


#endif  /* _C_EVENT_ARMYSELECTUNIT_H_ */
