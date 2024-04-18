/*! =========================================================================
      
      @file    CEvent_DestroyProjectile.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CProjectileGroup.h"
#include "CEvent_DestroyProjectile.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_DestroyProjectile::CEvent_DestroyProjectile(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_DestroyProjectile)
{
}


/*  _________________________________________________________________________ */
CEvent_DestroyProjectile::~CEvent_DestroyProjectile(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_DestroyProjectile::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
  /* HANDLER CODE GOES HERE */
	try{

	if(This)
	{
		if(/*CGame->RequestState()->projectiles.size() == 0 || */CGame->RequestState()->projGroups.size() == 0)
			return;
		CProjectileGroup* gr;
		gr = This->Group();
		std::vector<CProjectile*>::iterator it;
		it = std::find(This->Group()->mGroup.begin(), This->Group()->mGroup.end(), This);//whacked; 4th iter
		if(it != This->Group()->mGroup.end())
			This->Group()->mGroup.erase(it);
		delete This;
		if(gr->mGroup.size() == 0)
		{
			std::vector<CProjectileGroup*>::iterator it2;
			it2 = std::find(CGame->RequestState()->projGroups.begin(), CGame->RequestState()->projGroups.end(), gr);
			if(it2 != CGame->RequestState()->projGroups.end())
				CGame->RequestState()->projGroups.erase(it2);
			delete gr;
		}
	}
	}
	catch(...)
	{
		nlTHROW("Destroy projectile event failed.");
	}
}