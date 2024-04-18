/*! =========================================================================
      
      @file    CEvent_DetonateProjectile.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CProjectile.h"
#include "CMech.h"
#include "CEvent_DetonateProjectile.h"
#include "CSoundMgrS.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_DetonateProjectile::CEvent_DetonateProjectile(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_DetonateProjectile)
{
}


/*  _________________________________________________________________________ */
CEvent_DetonateProjectile::~CEvent_DetonateProjectile(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_DetonateProjectile::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
  /* HANDLER CODE GOES HERE */
	try
	{
	if(This && HitMe)
	{
		if(This->Speed() > 0)
		{
			if(HitMe->Armor() > 0)
				HitMe->TakeDamage((EDamageType)This->DamageType(), This->Damage());
		}
		Effect e;
		e.PlayEffect("./data/patch/sound collections/bomb_explosion_1.wav", FSOUND_FREE);
		This->Detonate();
		
	}
	}
	catch(...)
	{
		nlTHROW("Detonate projectile event failed.");
	}
}