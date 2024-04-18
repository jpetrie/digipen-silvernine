/*! =========================================================================
      
      @file    CEvent_LevelBegin.h
      @brief   Loads a level and starts the game.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_LEVELBEGIN_H_
#define _C_EVENT_LEVELBEGIN_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_LevelBegin = nlFOURCODE('l','v','l','b');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_LevelBegin : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_LevelBegin(void);
    ~CEvent_LevelBegin(void);
    
    // handling
    void Handle(CGameState *data);
    
  
  private:
    // level load callback
    static void nLoadCallback(const std::string &task);
};


#endif  /* _C_EVENT_LEVELBEGIN_H_ */
