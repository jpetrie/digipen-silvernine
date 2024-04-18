/*! =========================================================================
      
      @file    CObject.cpp
      @brief   Implementation of game object base class.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CObject.h"


/*                                                         internal constants
----------------------------------------------------------------------------- */

namespace
{
  const float      ikArmorBarWidth   = 5.0f;
  const float      ikShieldBarWidth  = 5.0f;
  const float      ikArmorBarOffset  = 10.0f;  // From right edge of unit.
  const float      ikShieldBarOffset = 20.0f;  // From right edge of unit.
  const COLORQUAD  ikSelRectBorder(1.0f,1.0f,0.0f,0.8f);
  const COLORQUAD  ikSelRectInterior(0.0f,0.0f,0.0f,0.0f);
  const COLORQUAD  ikArmorBarColor(0.5f,0.5f,0.5f,0.6f);
  const COLORQUAD  ikShieldBarColor(1.0f,0.0f,0.0f,0.6f);
};


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CObject::CObject(const std::string &tag)
/*! @brief Default constructor.

    If the tag parameter is allowed to default (to the empty string), the
    object will be initialized to sane (but probably useless) values.

    @param tag  The name of the tag to load data from.
*/
: mSprite(0),
  mWorldX(0.0f),mWorldY(0.0f),mDestX(0.0f),mDestY(0.0f),
  mArmor(1.0f),mShields(1.0f),
  mMass(1.0f),mRadius(1.0f),mHeight(1.0f),
  mCurArmor(mArmor),mCurShields(mShields),
  mArmorBar(0),mShieldBar(0),mSelRect(0)
{
  if(tag.length() > 0)
  {
    LoadFromTag(tag);
    
    // Turn this stuff off.
    ShowStatusBars(false);
    ShowSelectionRect(false);
  }
}


/*  _________________________________________________________________________ */
CObject::~CObject(void)
/*! @brief Destructor.
*/
{
  // Note: The mSprite member should NOT be deleted here.
  //       Subclasses are responsible for creating it,
  //       subclasses will release it.
  
  // Release status rectangles, et cetera.
  delete mSelRect;
  delete mArmorBar;
  delete mShieldBar;
}


/*  _________________________________________________________________________ */
void CObject::LoadFromTag(const std::string &tag)
/*! @brief Reinitializes an object from the specified tag.

    This function does not affect the world position of the object or the
    world position of its destination.

    @param tag  The name of the tag to load data from.
*/
{
CTag_obje *tTag = dcast< CTag_obje* >(CTagMgr->Unarchive(kTag_obje,tag));

  if(0 != tTag)
  {
    // Initialize the object.
    mCurArmor = mArmor = nsl::randfloat(tTag->armorLo,tTag->armorHi);
    mCurShields = mShields = nsl::randfloat(tTag->shieldLo,tTag->shieldHi);
    mMass = tTag->mass;
    mRadius = tTag->radius;
    mHeight = tTag->height;
    
    // Store flags.
    mFlags = tTag->flags;
    
    // Store damage mods.
    mDamageMods[kDamageKinetic]    = nsl::randfloat(tTag->dmgKineticLo,    tTag->dmgKineticHi);
    mDamageMods[kDamageExplosive]  = nsl::randfloat(tTag->dmgExplosiveLo,  tTag->dmgExplosiveHi);
    mDamageMods[kDamageBurning]    = nsl::randfloat(tTag->dmgBurningLo,    tTag->dmgBurningHi);
    mDamageMods[kDamageElectrical] = nsl::randfloat(tTag->dmgElectricalLo, tTag->dmgElectricalHi);
    mDamageMods[kDamageSync]       = nsl::randfloat(tTag->dmgSyncLo,       tTag->dmgSyncHi);
    
    // Build status bars/selection rectangle.
    mSelRect = new CRect(0.0f,0.0f,(2.0f * mRadius),mHeight);
    mSelRect->SetInteriorColor(ikSelRectInterior);
    mSelRect->SetBorderColor(ikSelRectBorder);
    mSelRect->SetZOrder(0.0f);
    mSelRect->SetVisible(false);
    mArmorBar = new CRect(0.0f,0.0f,ikArmorBarWidth,mHeight);
    mArmorBar->SetInteriorColor(ikArmorBarColor);
    mArmorBar->SetBorderColor(0.0f,0.0f,0.0f,0.0f);
    mArmorBar->SetZOrder(0.0f);
    mArmorBar->SetVisible(false);
    mShieldBar = new CRect(0.0f,0.0f,ikShieldBarWidth,mHeight);
    mShieldBar->SetInteriorColor(ikShieldBarColor);
    mShieldBar->SetBorderColor(0.0f,0.0f,0.0f,0.0f);
    mShieldBar->SetZOrder(0.0f);
    mShieldBar->SetVisible(false);
  }
  
  CTagMgr->Release(tTag);
}


/*  _________________________________________________________________________ */
void CObject::SetPosition(float x,float y)
/*! @brief Sets the world position of the object.

    SetPosition() does not check to ensure that the specified location is
    meaningful (i.e., within the current map), nor does it update the object's
    movement destination - use SetMoveTarget() to accomplish that.

    @param x  X coordinate in the world.
    @param y  Y coordinate in the world.
*/
{
  nlASSERT(0 != mSprite && "You're not loading your object properly before using it.");//FIXME remove this????

  mWorldX = x;
  mWorldY = y;
  mSprite->SetWorldX(mWorldX - (mSprite->GetWidth() / 2.0f));
	mSprite->SetWorldY(mWorldY);
	mSprite->SetZOrder(mWorldY);
	
  // Update status bar rectangles.
  mArmorBar->SetWorldX(mWorldX + mRadius + ikArmorBarOffset);
  mArmorBar->SetWorldY(mWorldY);
	mArmorBar->SetZOrder(mWorldY);
  mShieldBar->SetWorldX(mWorldX + mRadius + ikShieldBarOffset);
  mShieldBar->SetWorldY(mWorldY);
  mShieldBar->SetZOrder(mWorldY - 1);
//  mSyncBar->SetWorldX(mWorldX + mRadius + ikSyncBarOffset);
//  mSyncBar->SetWorldY(mWorldY);
//	mSyncBar->SetZOrder(mWorldY);
	mSelRect->SetWorldX(mWorldX - mRadius);
	mSelRect->SetWorldY(mWorldY);
	mSelRect->SetZOrder(mWorldY - 1);

}


/*  _________________________________________________________________________ */
void CObject::TakeDamage(EDamageType type,float amount)
/*! @brief Takes damage.

    TakeDamage() causes the object to intelligently take damage in the
    specified amount of the specified type. The object's damage modifiers are
    taken into account when calculating damage.
    
    Note that CObjects do not respond to sync type damage at all unless they
    are really CMech objects.
    
    @param type    Type of damage.
    @param amount  Amount to damage. 
*/
{
  if(type != kDamageSync)
  {
    if(mCurShields > 0.0f)
      mCurShields -= amount * mDamageMods[type];
    else
      mCurArmor -= amount * mDamageMods[type];
  }
  
  // Clamp values.
  nsl::clampval(mCurShields,0.0f,mShields);
  nsl::clampval(mCurArmor,0.0f,mArmor);
    
  // Now update status rectangles.
float  tArmorScale = mCurArmor / mArmor;
float  tShieldScale = mCurShields / mShields;

  mArmorBar->SetHeight(tArmorScale * mHeight);
  mShieldBar->SetHeight(tShieldScale * mHeight);
}

void CObject::Destroy(void)
{
  ShowStatusBars(false);
  ShowSelectionRect(false);
  
  // The above calls will no-op if mDead is true, so set this here.
//  mDead = true;
}


void CObject::ShowStatusBars(bool on)
{
  if(DoesDrawStatus())
  {
    mArmorBar->SetVisible(on);
    mShieldBar->SetVisible(on);
   // mSyncBar->SetVisible(on);
  }
}
    

void CObject::ShowSelectionRect(bool on)
{
  if(DoesDrawSelection())
    mSelRect->SetVisible(on);
}

/*  _________________________________________________________________________ */
void CObject::Update(void)
/*! @brief Performs periodic updating.

    @param sim  The current game session.
*/
{
//  if(mDead)
 // {
    //SetPosition(-100,-100);
  //  mSprite->SetVisible(false);
 // }
}