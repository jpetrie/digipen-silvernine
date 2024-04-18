/*! =========================================================================
      
      @file    CMech.h
      @brief   Interface to mech class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_MECH_H_
#define _C_MECH_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CMap.h"
#include "CObject.h"
#include "CAttack.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/* __________________________________________________________________________ */
class CMech : public CObject
/*! @brief Mech class.
*/
{
  friend class CUnit;

	public:
	  // typedefs
    typedef std::vector< CAttack >  TAttackList;
    
    
    // ct and dt
     CMech(const std::string &tag = "");
		~CMech(void);
    
    // initialization
    void LoadFromTag(const std::string &tag);
    
    // accessors
    float Sync(void) const                            { return (mCurSync); }
    float SyncMax(void) const                         { return (mSync); }
    float Speed(void) const                           { return (mSpeed); }
    float TerrainModifier(ETerrainType terrain) const { return (mTerrainMods[terrain]); }
    float RadarRadius(void) const                     { return (mRadarRange); }
    

    // manipulators
    void SetSync(float v)    { mCurSync = v; }
    void SetSyncMax(float v) { mSync = v; }
    
    // position
    virtual void SetPosition(float x,float y);
    
    // attacks
    unsigned int GetAttackCount(void) const { return (scast< unsigned int >(mAttacks.size())); }
    CAttack&     GetAttack(unsigned int i)  { return (mAttacks[i]); }
    
    
    // damage
    virtual void TakeDamage(EDamageType type,float amount);
    virtual void Destroy(void);
    
    // updating
    virtual void Update(void) { };
    
    // misc
    virtual void ShowStatusBars(bool on);
    virtual void ShowSelectionRect(bool on);
 
    int kind;//0 = scout, 1 = grunt, 2 = sniper, 3 = bmf
 
TAttackList  mAttacks;
  protected:
	  // data members
	  float mSync;     // Maximum sync level.
	  float mCurSync;  // Current sync level.
	  
	  int  mIdleSeqIdx;      // Idle animation.
	  int  mWalkSeqIdx;      // Walk animation.
	  int  mFlinchSeqIdx;    // Flinch (hit) animation.
	  int  mTauntSeqIdx;     // Taunting / victory animation.
	  int  mSoftSeqIdx;      // Soft death animation.
	  int  mHardSeqIdx;      // Hard death animation.
	  int  mPortraitSeqIdx;  // Portrait (army screen) animation.
	  int  mFire1SeqIdx;     // Primary firing animation.
	  int  mFire2SeqIdx;     // Secondary firing animation.
	  int  mFire3SeqIdx;     // Ternary firing animation.
	  
    float  mSpeed;                        // Basic movement speed.
    float  mTerrainMods[kTerrain_Types];  // Modifiers to speed for terrain types.
    
    float  mRadarRange;
    float  mVisionRange;
    
   // TAttackList  mAttacks;
    
    std::string  mIdlePGroup;
    std::string  mFlinchPGroup;
    std::string  mSoftPGroup;
    std::string  mHardPGroup;
    
    CRect *mSyncBar;    // The sync status bar.
    
};


#endif  /* _C_MECH_H_ */