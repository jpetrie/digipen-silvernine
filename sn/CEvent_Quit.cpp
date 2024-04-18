/*! =========================================================================
      
      @file    CEvent_Quit.cpp
      @brief   Quit the game.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_Quit.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_Quit::CEvent_Quit(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_Quit)
{
}


/*  _________________________________________________________________________ */
CEvent_Quit::~CEvent_Quit(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_Quit::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
  PostQuitMessage(0);
}