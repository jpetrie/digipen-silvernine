/*! =========================================================================
      
      @file    CEvent_CreateProjectile.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CProjectileGroup.h"
#include "CEvent_CreateProjectile.h"
#include "CGameEngine.h"
#include "CSoundMgrS.h"

/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_CreateProjectile::CEvent_CreateProjectile(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_CreateProjectile), owner(0), target(0)
{
}


/*  _________________________________________________________________________ */
CEvent_CreateProjectile::~CEvent_CreateProjectile(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_CreateProjectile::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
  /* HANDLER CODE GOES HERE */

	Effect e;
	e.PlayEffect("./data/patch/sound collections/mortar.wav", FSOUND_FREE);
	bool isammo = (life == -1) ? true : false;
	CProjectileGroup *p = new CProjectileGroup(tag, owner, originX, originY, destX, destY, isammo);
	//mark the projectiles as given an attack
	for(unsigned int i = 0; i < p->Count(); ++i)
	  (*p)[i]->givesAttack = ammoFor;
	  
	p->SetTarget(target);
	CGame->RequestState()->projGroups.push_back(p);
	//p->SetOwner(owner);

}