/*! =========================================================================
      
      @file    CEvent_LevelEnd.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_LEVELEND_H_
#define _C_EVENT_LEVELEND_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_LevelEnd = nlFOURCODE('l','v','l','e');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_LevelEnd : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_LevelEnd(void);
    ~CEvent_LevelEnd(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    bool win;
};


#endif  /* _C_EVENT_LEVELEND_H_ */
