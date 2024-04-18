/*! =========================================================================
      
      @file    CEvent_ArmySelectUnit.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_ArmySelectUnit.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_ArmySelectUnit::CEvent_ArmySelectUnit(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_ArmySelectUnit)
{
}


/*  _________________________________________________________________________ */
CEvent_ArmySelectUnit::~CEvent_ArmySelectUnit(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_ArmySelectUnit::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
  CGame->RequestState()->teams[0]->AddActiveUnit(CGame->RequestState()->teams[0]->GetUnit(unit_index));
}