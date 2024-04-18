/*! =========================================================================
      
      @file    CEvent_UnitDestroy.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_UnitDestroy.h"
#include "CEvent_CreateProjectile.h"

#include "CEvent_CreateProjectile.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_UnitDestroy::CEvent_UnitDestroy(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_UnitDestroy)
{
}


/*  _________________________________________________________________________ */
CEvent_UnitDestroy::~CEvent_UnitDestroy(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_UnitDestroy::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
  unit->Dead(true);
  
   //Drop a random ability.

  int idx = rand() % unit->Mech()->mAttacks.size();
  
  
  CEvent_CreateProjectile *tEvt = (CEvent_CreateProjectile*)CGame->MakeEvent(kEvent_CreateProjectile);
  tEvt->tag = unit->Mech()->mAttacks[idx].AmmoName().c_str();
  tEvt->ammoFor = unit->Mech()->mAttacks[idx].AttackName().c_str();


  tEvt->destX = tEvt->originX = unit->X();
  tEvt->destY = tEvt->originY = unit->Y();
  tEvt->life = -1;
//<<<<<<< .mine
  tEvt->owner = 0;
  tEvt->target = 0;
  CGame->PostEvent(tEvt);
//=======
//  CGame->PostEvent(tEvt);*/
//>>>>>>> .r82
}