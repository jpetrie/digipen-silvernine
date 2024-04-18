/*! =========================================================================
      
      @file    CAttack.cpp
      @brief   Implementation of attack class.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagMgrS.h"

#include "CAttack.h"

#include "CEvent_CreateProjectile.h"

/*                                                         internal constants
----------------------------------------------------------------------------- */

namespace
{
};


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CAttack::CAttack(const std::string &tag)
/*! @brief Default constructor.

    If the tag parameter is allowed to default (to the empty string), the
    object will be initialized to sane (but probably useless) values.

    @param ac   The attack class; determines which tag type to load.
    @param tag  The name of the tag to load data from.?
*/
: mCashCost(0),
  mSyncCost(0.0f),
  mAmmoCost(0),mCurAmmo(0),mMaxAmmo(0),
  mDelay(0),mCurDelay(0),
  mLifetime(0)
{
  if(tag.length() > 0)
    LoadFromTag(tag);
}


/*  _________________________________________________________________________ */
CAttack::~CAttack(void)
/*! @brief Destructor.
*/
{

}


/*  _________________________________________________________________________ */
void CAttack::LoadFromTag(const std::string &tag)
/*! @brief Loads attack data from a tag.

    The ac parameter determines the type of attack tag loaded (either ablp or
    ablm).

    @param ac   The attack class; determines which tag type to load.
    @param tag  The name of the tag to load data from.
*/
{
std::string ftag =tag;

  if(tag[0] == '\n')
    ftag = tag.substr(1);

  std::cout << "Loading attack " << ftag.c_str() << "\n";
  mAttackName = ftag;
  std::string foo = nsl::stformat("data/script/attacks/%s.ats",ftag.c_str());
  ExecuteScript(foo);
}


void CAttack::Execute(CUnit *u,float x,float y,CUnit *target)
{
  if(mCurDelay > 0)
    return;

CEvent_CreateProjectile *evt = scast<CEvent_CreateProjectile*>(CGame->MakeEvent(kEvent_CreateProjectile));
  
  evt->life = mLifetime;
  evt->originX = u->X();
  evt->originY = u->Y();
  evt->destX = x;
  evt->destY = y;
  evt->tag = mProjectileTag;
  evt->owner = u;
  evt->target = target;//FIXME no target field?
  CGame->PostEvent(evt); 
  
  mCurDelay = mDelay;
}

void CAttack::Recharge(void)
{
  if(mCurDelay > 0)
    --mCurDelay;
}