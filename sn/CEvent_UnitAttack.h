/*! =========================================================================
      
      @file    CEvent_UnitAttack.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_UNITATTACK_H_
#define _C_EVENT_UNITATTACK_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_UnitAttack = nlFOURCODE('a','t','t','a');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_UnitAttack : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_UnitAttack(void);
    ~CEvent_UnitAttack(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    bool                   ground;    // True if attack is ground (XY) based, false if unit based.
    float                  ground_x;  // X coordinate of ground attack.
    float                  ground_y;  // Y coordinate of ground attack.
    CUnit                 *target;    // Target of unit based attack.
    std::vector< CUnit* >  units;     // Units doing the attacking.
};


#endif  /* _C_EVENT_UNITATTACK_H_ */
