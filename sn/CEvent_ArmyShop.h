/*! =========================================================================
      
      @file    CEvent_ArmyShop.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_ARMYSHOP_H_
#define _C_EVENT_ARMYSHOP_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */


// ID
const CEvent::ID  kEvent_ArmyShop = nlFOURCODE('a','s','h','p');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_ArmyShop : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_ArmyShop(void);
    ~CEvent_ArmyShop(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    /* PROPERTY DATA GOES HERE */
};


#endif  /* _C_EVENT_ARMYSHOP_H_ */
