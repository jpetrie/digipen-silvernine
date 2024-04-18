/*! =========================================================================
      
      @file    CEvent_ArmyBegin.h
      @brief   Begins army management.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_ARMYBEGIN_H_
#define _C_EVENT_ARMYBEGIN_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_ArmyBegin = nlFOURCODE('a','r','m','b');

// exception tags
nlVE_TAG(XUnitMaskNotFound);
nlVE_TAG(XWeaponMaskNotFound);
nlVE_TAG(XAbilityMaskNotFound);


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_ArmyBegin : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_ArmyBegin(void);
    ~CEvent_ArmyBegin(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    /* PROPERTY DATA GOES HERE */
};


#endif  /* _C_EVENT_ARMYBEGIN_H_ */
