/*! =========================================================================
      
      @file    CObject.h
      @brief   Interface to game object base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_OBJECT_H_
#define _C_OBJECT_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CSprite.h"
#include "CRect.h"

#include "CTagMgrS.h"
#include "CTag_obje.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// damage types
enum EDamageType
{
  kDamageKinetic = 0,
  kDamageExplosive,
  kDamageBurning,
  kDamageElectrical, 
  kDamageSync,
  kDamage_Types
};


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CObject
/*! @brief Gameplay object base class.
*/
{
  public:
    // ct and dt
             CObject(const std::string &tag = "");
    virtual ~CObject(void);
    
    // initialization
    virtual void LoadFromTag(const std::string &tag);
    
    // accessors
    bool  DoesIgnoreCollision(void) const { return (!!(mFlags & kObject_IgnoreCollision)); }
    bool  DoesDrawSelection(void) const   { return (!!(mFlags & kObject_DrawSelection)); }
    bool  DoesDrawStatus(void) const      { return (!!(mFlags & kObject_DrawStatus)); }
    float Radius(void) const              { return (mRadius); }
    float Height(void) const              { return (mHeight); }
    
    // manipulators
    void Show(bool v) { mSprite->SetVisible(v); }
    
    // scriptable accessors
    float X(void)          { return (mWorldX); }
    float Y(void)          { return (mWorldY); }
    float Armor(void)      { return (mCurArmor); }
    float ArmorMax(void)   { return (mArmor); }
    float Shields(void)    { return (mCurShields); }
    float ShieldsMax(void) { return (mShields); }
    
    // scriptable manipulators  
    void SetArmor(float v)      { mCurArmor = v; }
    void SetArmorMax(float v)   { mArmor = v; }
    void SetShields(float v)    { mCurShields = v; }
    void SetShieldsMax(float v) { mShields = v; }
    
    // positioning and movement
    virtual void SetPosition(float x,float y);
    
    // damage
    virtual void TakeDamage(EDamageType type,float amount);
    virtual void Destroy(void);
    
    // updating
    virtual void Update(void);
    
    // misc
    virtual void ShowStatusBars(bool on);
    virtual void ShowSelectionRect(bool on);
 
    int Cost(void) { return (int)mMass; }
    
 
  protected:
    // data members
    CSprite *mSprite;  // Object sprite. Here so it can be moved; but subclasses set it up.
    int      mFlags;   // Object flags. 
     
    float  mWorldX;   // Current X position in the world.
    float  mWorldY;   // Current Y position in the world.
    float  mDestX;    // Destination X in the world.
    float  mDestY;    // Destination Y in the world.
    
    float  mArmor;    // Armor; object dies when zero, does not recharge.
    float  mShields;  // Energy shields; depleted before armor, recharges.
    float  mMass;     // Mass; currently just a pretty stat. For units that can be bought, this is the cost. Hacky, I know.
    float  mRadius;   // Collision radius.
    float  mHeight;   // Collision height.
     
    float  mCurArmor;    // Current armor value.
    float  mCurShields;  // Current shields value.
    
    float  mDamageMods[kDamage_Types];  // Damage multipliers (1.0 is normal, 0.0 is none, and so on).
    
    CRect *mSelRect;    // The selection rectangle.
		CRect *mArmorBar;   // The armor status bar.
    CRect *mShieldBar;  // The shield status bar.
};


#endif  /* _C_OBJECT_H_ */
