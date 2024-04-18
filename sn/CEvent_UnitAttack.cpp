/*! =========================================================================
      
      @file    CEvent_UnitAttack.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CProjectile.h"

#include "CEvent_UnitAttack.h"
#include "CEvent_CreateProjectile.h"
#include "CPacket_RequestUnitAttack.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_UnitAttack::CEvent_UnitAttack(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_UnitAttack)
{
}


/*  _________________________________________________________________________ */
CEvent_UnitAttack::~CEvent_UnitAttack(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_UnitAttack::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
if(!CGame->NetGame())
{
  if(!ground)
  {
    ground_x = target->X();
    ground_y = target->Y();
  }

  for(unsigned int i = 0; i < units.size(); ++i)
  {
  float  mind = units[i]->Mech()->GetAttack(units[i]->PrimedAttack()).MinDistance();
  float  maxd = units[i]->Mech()->GetAttack(units[i]->PrimedAttack()).MaxDistance();
  
    // First test if the unit can use its current attack from where it is.
    if(nsl::pt_in_ellipse(units[i]->X(),units[i]->Y(),maxd,maxd / 2.0f,ground_x,ground_y))
    {
      if(!nsl::pt_in_ellipse(units[i]->X(),units[i]->Y(),mind,mind / 2.0f,ground_x,ground_y))
      {
        if(units[i]->Sync() >= units[i]->Mech()->GetAttack(units[i]->PrimedAttack()).SyncCost())
        {
          units[i]->Mech()->GetAttack(units[i]->PrimedAttack()).Execute(units[i],ground_x,ground_y,target);
          units[i]->Mech()->TakeDamage(kDamageSync,units[i]->Mech()->GetAttack(units[i]->PrimedAttack()).SyncCost());
          
        }
      }
      else
      {
        // Must move to get to safe distance.
       // units[i]->RememberNeedsToAttack();
        
      }
    }
    else
    {
      // Must move to be within range, so start him moving to the target.
      units[i]->needsAttack = units[i]->PrimedAttack();
      units[i]->MovePathDest(ground_x,ground_y);
    }
  }
}
else
{
	if(CGame->RequestState()->RequireAttackValidation)
	{
		CPacket_RequestUnitAttack * mReq = rcast<CPacket_RequestUnitAttack *>(NetworkManager->MakePacket(kPacket_RequestUnitAttack));

		mReq->ground = ground;
		mReq->ground_x = ground_x;
		mReq->ground_y = ground_y;
		mReq->target = target;
		mReq->units = units;

		CGame->GetServSock().Send(*mReq);

		CGame->RequestState()->RequireAttackValidation = true;
	
	}
	else
	{
		 if(!ground)
  {
    ground_x = target->X();
    ground_y = target->Y();
  }

  for(unsigned int i = 0; i < units.size(); ++i)
  {
  float  mind = units[i]->Mech()->GetAttack(units[i]->PrimedAttack()).MinDistance();
  float  maxd = units[i]->Mech()->GetAttack(units[i]->PrimedAttack()).MaxDistance();
  
    // First test if the unit can use its current attack from where it is.
    if(nsl::pt_in_ellipse(units[i]->X(),units[i]->Y(),maxd,maxd / 2.0f,ground_x,ground_y))
    {
      if(!nsl::pt_in_ellipse(units[i]->X(),units[i]->Y(),mind,mind / 2.0f,ground_x,ground_y))
      {
        if(units[i]->Sync() >= units[i]->Mech()->GetAttack(units[i]->PrimedAttack()).SyncCost())
        {
          units[i]->Mech()->GetAttack(units[i]->PrimedAttack()).Execute(units[i],ground_x,ground_y,target);
          units[i]->Mech()->TakeDamage(kDamageSync,units[i]->Mech()->GetAttack(units[i]->PrimedAttack()).SyncCost());
          
        }
      }
      else
      {
        // Must move to get to safe distance.
        ///units[i]->RememberNeedsToAttack();
        
      }
    }
    else
    {
      // Must move to be within range, so start him moving to the target.
      units[i]->needsAttack = units[i]->PrimedAttack();
      units[i]->MovePathDest(ground_x,ground_y);
    }
  }
		CGame->RequestState()->RequireAttackValidation = true;
	
	}
}
}