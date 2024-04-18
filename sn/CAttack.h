/*! =========================================================================
      
      @file    CAttack.h
      @brief   Interface to attack class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_ATTACK_H_
#define _C_ATTACK_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory.h"

#include "CScriptMgrS.h"
#include "CScriptableM.h"

#include "CProjectile.h"


/*                                                                  constants
----------------------------------------------------------------------------- */


/*                                                                    classes
----------------------------------------------------------------------------- */

// forward declarations
//class CS9Session;
class CUnit;


/*  _________________________________________________________________________ */
class CAttack : public CScriptableM< CAttack >
/*! @brief Attack class.
*/
{
  public:
    // ct and dt
             CAttack(const std::string &tag = "");
    virtual ~CAttack(void);
    
    // initialization
    void LoadFromTag(const std::string &tag);
  
    // accessors
    int    CashCost(void) const    { return (mCashCost); }
    float  SyncCost(void) const    { return (mSyncCost); }
    int    AmmoCost(void) const    { return (mAmmoCost); }
    int    AmmoMax(void) const     { return (mMaxAmmo); }
    int    Ammo(void) const        { return (mCurAmmo); }
    float  MinDistance(void) const { return (mMinDist); }
    float  MaxDistance(void) const { return (mMaxDist); }
    int    Icon(void) const        { return (mIcon); }
    int    Lifetime(void) const    { return (mLifetime); }
    std::string  AmmoName(void)    { return (mAmmoTag); }
    std::string  AttackName(void)     { return (mAttackName); }
    
    // execution
    void Execute(CUnit *u,float x,float y,CUnit *target);
    void Recharge(void);
  
    // scriptablity
    EXPORT void SetupEffectGroup(char *t)      { mEffectTag = t; }
    EXPORT void SetupProjectileGroup(char *t)  { mProjectileTag = t; }
    EXPORT void SetupCost(int t)               { mCashCost = t; }
    EXPORT void SetupSync(float t)             { mSyncCost = t; }
    EXPORT void SetupClip(int t)               { mMaxAmmo = t; }
    EXPORT void SetupMinDistance(float t)      { mMinDist = t; }
    EXPORT void SetupMaxDistance(float t)      { mMaxDist = t; }
    EXPORT void SetupIcon(int t)               { mIcon = t; }
    EXPORT void SetupLifetime(int t)           { mLifetime = t; }
    EXPORT void SetupAmmoTag(char *t)          { mAmmoTag = t; }
    EXPORT void SetupDelay(int t)              { mDelay = mCurDelay = t; }
  
  
  private:
    // data members
    std::string  mEffectTag;      // (pgrp) Called to generate "casting effect."
    std::string  mProjectileTag;  // (pgrp) Called to generate actual attack projectiles.
  std::string mAttackName;
  
    int    mCashCost;  // Cost to buy this attack.

    float  mSyncCost;  // Sync consumed in generating the attack.
    int    mAmmoCost;  // Ammo consumed in generating the attack.
    int    mCurAmmo;   // Current ammo remaining.
    int    mMaxAmmo;   // Maximum ammo.
    
    float  mMinDist;  // Minimum distance to launch this attack.
    float  mMaxDist;  // Maximum distance to launch this attack.
    std::string  mAmmoTag;
    int  mDelay;      // Delay between uses.
    int  mCurDelay;   // When 0, attack can execute.
    int  mLifetime;   // Lifetime of attack projectiles.
    
    int mIcon;
};


#endif  /* _C_ATTACK_H_ */
