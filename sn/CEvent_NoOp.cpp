/*! =========================================================================
      
      @file    CEvent_NoOp.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_NoOp.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_NoOp::CEvent_NoOp(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_NoOp)
{
}


/*  _________________________________________________________________________ */
CEvent_NoOp::~CEvent_NoOp(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_NoOp::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
  // This event must do nothing. Don't screw with it, okay?
}