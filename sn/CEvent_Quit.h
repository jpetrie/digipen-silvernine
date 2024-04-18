/*! =========================================================================
      
      @file    CEvent_Quit.h
      @brief   Quit the game.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_QUIT_H_
#define _C_EVENT_QUIT_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_Quit = nlFOURCODE('q','u','i','t');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_Quit : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_Quit(void);
    ~CEvent_Quit(void);
    
    // handling
    void Handle(CGameState *data);
};


#endif  /* _C_EVENT_QUIT_H_ */
