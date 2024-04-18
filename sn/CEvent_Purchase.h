/*! =========================================================================
      
      @file    CEvent_Purchase.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_PURCHASE_H_
#define _C_EVENT_PURCHASE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_Purchase = nlFOURCODE('p','u','r','c');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_Purchase : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_Purchase(void);
    ~CEvent_Purchase(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    /* PROPERTY DATA GOES HERE */
};


#endif  /* _C_EVENT_PURCHASE_H_ */
