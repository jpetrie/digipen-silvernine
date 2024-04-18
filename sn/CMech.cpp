/*! =========================================================================
      
      @file    CMech.cpp
      @brief   Implementation of mech class.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "CMech.h"

#include "CTagFactory.h"
#include "CTag_mech.h"


/*                                                         internal constants
----------------------------------------------------------------------------- */

namespace
{
  const float      ikSyncBarWidth  = 5.0f;
  const float      ikSyncBarOffset = 30.0f;
  const COLORQUAD  ikSyncBarColor(0.0f,0.0f,1.0f,0.6f);
};


/*                                                           function members
----------------------------------------------------------------------------- */

CMech::CMech(const std::string &tag)
/*! @brief Default constructor.

    @param tag  The name of the tag to load data from.
*/
: mIdleSeqIdx(0)
{
  if(tag.length() > 0)
    LoadFromTag(tag);

  mSync = 100.0;
  mCurSync = 100.0;
 
}

CMech::~CMech(void)
/*! @brief Deconstructor
*/
{
  delete mSprite;
}

void CMech::LoadFromTag(const std::string &tag)
/*! @brief Reinitializes a mech from the specified tag.

    @param tag  The name of the tag to load data from.
*/
{
CTag_mech *tTag = dcast< CTag_mech* >(CTagMgr->Unarchive(kTag_mech,tag));

  if(0 != tTag)
  { 
    // Initialize object and sprite data.
    CObject::LoadFromTag(tTag->objeTag);
    mSprite = new CSprite(mWorldX,mWorldY,0,0,tTag->sprcTag,true,0,0,0);
    
    // Initialize mech data.
    mIdleSeqIdx = tTag->idleSeqncIndx;
    
    // Speeds and modifiers.
    mSpeed = tTag->baseSpeed;
    mTerrainMods[kTerrainGrass] = tTag->speedModGrass;
    mTerrainMods[kTerrainPavement] = tTag->speedModPavement;
    mTerrainMods[kTerrainShallowWater] = tTag->speedModShallowWater;
    mTerrainMods[kTerrainDeepWater] = tTag->speedModDeepWater;
    mTerrainMods[kTerrainBrush] = tTag->speedModBrush;
    mTerrainMods[kTerrainRocky] = tTag->speedModRocky;
    mTerrainMods[kTerrainWalkingImpassable] = tTag->speedModGroundImpass;
    mTerrainMods[kTerrainFlyingImpassable] = tTag->speedModAirImpass;
    
    // Ranges.
    mRadarRange = tTag->radarRadius;
    mVisionRange = tTag->visionRadius;
    
    // Load attacks.
    mAttacks.clear();
    for(unsigned int i = 0; i < tTag->mentCnt; ++i)
      mAttacks.push_back(CAttack(tTag->mentAttacks[i]));
    
    
    // Build sync bar.
    mSyncBar = new CRect(0.0f,0.0f,ikSyncBarWidth,mHeight);
    mSyncBar->SetInteriorColor(ikSyncBarColor);
    mSyncBar->SetBorderColor(0.0f,0.0f,0.0f,0.0f);
    mSyncBar->SetZOrder(0.0f);
    mSyncBar->SetVisible(false);
    
    kind = 0;
    if(tag == "mechscut") kind = 0;
    if(tag == "mechgrnt") kind = 1;
    if(tag == "mechsnip") kind = 2;
    if(tag == "mechbmfu") kind = 3;
    
    mSprite->SetVisible(false);
  }
  
  CTagMgr->Release(tTag);
}


/*  _________________________________________________________________________ */
void CMech::SetPosition(float x,float y)
/*! @brief Sets the world position of the mech.

    This method is functionally similar to CObject::SetPosition() (with all of
    its caveats). It is overloaded only to ensure the mech's sync bar is
    correctly updated.

    @param x  X coordinate in the world.
    @param y  Y coordinate in the world.
*/
{
  // Call base function.
  CObject::SetPosition(x,y);
	
  // Update status bar rectangles.
  mSyncBar->SetWorldX(mWorldX + mRadius + ikSyncBarOffset);
  mSyncBar->SetWorldY(mWorldY);
	mSyncBar->SetZOrder(mWorldY);
}


/*  _________________________________________________________________________ */
void CMech::TakeDamage(EDamageType type,float amount)
/*! @brief Takes damage.

    This method is functionally similar to CObject::TakeDamage() except that
    it will also handle the sync damage type.
    
    @param type    Type of damage.
    @param amount  Amount to damage. 
*/
{
float tSyncScale;

  if(type != kDamageSync)
  {
    // Scale damage based on how fully synced we are.
    amount *= ((mCurSync / mSync)) < .25 ? .25 : ((mCurSync / mSync));
  }

  if(type == kDamageSync)
    mCurSync -= amount * mDamageMods[kDamageSync];
  else
    CObject::TakeDamage(type,amount);
    
  // Clamp.
  nsl::clampval(mCurSync,0.0f,mSync);
    
  // Now update status rectangles.
  tSyncScale = mCurSync / mSync;
  mSyncBar->SetHeight(tSyncScale * mHeight);
}

void CMech::Destroy(void)
{
 CObject::Destroy();
}


void CMech::ShowStatusBars(bool on)
{
  CObject::ShowStatusBars(on);
  
  if(DoesDrawStatus())
    mSyncBar->SetVisible(on);
}
    

void CMech::ShowSelectionRect(bool on)
{
  CObject::ShowSelectionRect(on);
}