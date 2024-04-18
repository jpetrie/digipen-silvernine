/*! =========================================================================
      
      @file    CEvent_StartMP.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_STARTMP_H_
#define _C_EVENT_STARTMP_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_StartMP = nlFOURCODE('s','t','m','p');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_StartMP : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_StartMP(void);
    ~CEvent_StartMP(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    /* PROPERTY DATA GOES HERE */
};


#endif  /* _C_EVENT_STARTMP_H_ */
