/*! =========================================================================

      @file    CEvent_UnitSelect.h
      @brief   yay
      
    ========================================================================= */
    
/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_UNITSELECT_H_
#define _C_EVENT_UNITSELECT_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"

#include "CUnit.h"

/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_UnitSelect = nlFOURCODE('u','s','e','l');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_UnitSelect : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_UnitSelect(void);
    ~CEvent_UnitSelect(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    CUnit *unit;
};


#endif  /* _C_EVENT_UNITSELECT_H_ */
