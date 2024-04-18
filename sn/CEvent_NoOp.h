/*! =========================================================================
      
      @file    CEvent_NoOp.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_NOOP_H_
#define _C_EVENT_NOOP_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_NoOp = nlFOURCODE('n','o','o','p');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_NoOp : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_NoOp(void);
    ~CEvent_NoOp(void);
    
    // handling
    void Handle(CGameState *data);
};


#endif  /* _C_EVENT_NOOP_H_ */
