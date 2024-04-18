/*! =========================================================================
      
      @file    CUnit.h
      @brief   Interface to unit class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_UNIT_H_
#define _C_UNIT_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CScriptMgrS.h"
#include "CScriptableM.h"

#include "CMech.h"
#include "CAttack.h"

#include "CRect.h"
#include "CText.h"

#include "UIRingMenu.h"


/*                                                                  constants
----------------------------------------------------------------------------- */


/*                                                                    classes
----------------------------------------------------------------------------- */

// forward declarations
class CMap;


/*  _________________________________________________________________________ */
class CUnit : public CScriptableM< CUnit >
/*! @brief Unit class.
*/
{  
  public:
    // typedefs
    typedef int  ID;

    // ct and dt
	           CUnit(const std::string &tag = "",int team = 0,int player = 0,float x = 0.0f,float y = 0.0f);
	  virtual ~CUnit(void);

    // initialization
    virtual void LoadFromTag(const std::string &tag);

    // accessors
    CUnit::ID   Ident(void) const                 { return (mID); }
    int         Team(void) const                  { return (mTeam); }
    int         Player(void) const                { return (mPlayer); }
    bool        Selected(void) const              { return (mSelected); }
    std::string Name(void) const                  { return (mName); }
    EXPORT float       X(void)                      { return (mMech != 0 ? mMech->X()          : -1.0f); }
    EXPORT float       Y(void)                      { return (mMech != 0 ? mMech->Y()          : -1.0f); }
    float       Radius(void) const                { return (mMech != 0 ? mMech->Radius()     : -1.0f); }
    float       Height(void) const                { return (mMech != 0 ? mMech->Height()     : -1.0f); }
    float       Armor(void) const                 { return (mMech != 0 ? mMech->Armor()      : -1.0f); }
    float       ArmorMax(void) const              { return (mMech != 0 ? mMech->ArmorMax()   : -1.0f); } 
    EXPORT float       Shields(void) const               { return (mMech != 0 ? mMech->Shields()    : -1.0f); }
    float       ShieldsMax(void) const            { return (mMech != 0 ? mMech->ShieldsMax() : -1.0f); }
    float       Sync(void) const                  { return (mMech != 0 ? mMech->Sync()       : -1.0f); }
    float       SyncMax(void) const               { return (mMech != 0 ? mMech->SyncMax()    : -1.0f); }
    float       Speed(void) const                 { return (mMech != 0 ? mMech->Speed()      : -1.0f); }
    bool        IsRingMenuVisible(void)           { return (mRingMenuVis); }
    float       TerrainCost(ETerrainType t) const { return (mMech != 0 ? mMech->TerrainModifier(t) : 0.0f); }
	  CMech*      Mech(void) const                  { return mMech; }
	  int         Facing(void) const                { return mFace; } 

    EXPORT int Dead(void) 
    { 
    int ret = (mDead ? 1 : 0);
    return (mDead ? 1 : 0);
    }
    void Dead(bool b)  { mDead = b; }

    int PrimedAttack(void) const { return (mPrimedAttack); }

    // manipulators
    void Ident(CUnit::ID id)           { mID = id; }
    void Selected(bool v)              { mSelected = v; }
    void SetPosition(float x,float y)  { if(mMech != 0) mMech->SetPosition(x,y); }
    void SetName(const std::string &n) { mName = n; }
    void SetArmor(float v)             { if(mMech != 0) mMech->SetArmor(v); }
    void SetArmorMax(float v)          { if(mMech != 0) mMech->SetArmorMax(v); }
    void SetShields(float v)           { if(mMech != 0) mMech->SetShields(v); }
    void SetShieldsMax(float v)        { if(mMech != 0) mMech->SetShieldsMax(v); } 
    void SetSync(float v)              { if(mMech != 0) mMech->SetSync(v); }       
    void SetSyncMax(float v)           { if(mMech != 0) mMech->SetSyncMax(v); }    
    void Show(bool s)                  { if(mMech != 0) mMech->Show(s); }
    void ShowStatusBars(bool s)        { if(mMech != 0) mMech->ShowStatusBars(s); }
    void ShowSelectionRect(bool s)     { if(mMech != 0) mMech->ShowSelectionRect(s); }
    void ShowRingMenu(bool s)          { mRingMenuVis = s; }
    void ShowName(bool s)              { mNameObj->SetVisible(s); }


  
    void GiveAttack(const CAttack &attack);
	void PrimeAttack(int attack)
	{
		mPrimedAttack = attack;
	}

    // set mech
    void SetMech(const std::string &tag);
  
    // positioning and movement
	         void MovePathAppend(std::vector< nsl::point2D< float > > &path);
	         void MovePathFlush(void);
	  EXPORT void MovePathDest(float x,float y);
	         void MovePathDestInternal(float x,float y); // DON'T CALL THIS FUNCTION UNLESS YOU MEAN IT
	  EXPORT int  MovePathEmpty(void) { return (mPathSteps.empty() ? 1 : 0); }
	  
	  // attacks
	  //void SetAttackTarget(CObject *target,unsigned int attack);
	  EXPORT void SetAttackTarget(float target_x,float target_y,unsigned int attack);
	  
	  // information
	  EXPORT int TestWithinRadius(float x,float y,float minor,float major);
	  
	  // script bootstrap
	  EXPORT void DefineSeeEnemyResponse(char *subscript) { mResponseSeeEnemy = subscript; }
	  
	  // updating
	  void Update(void);
	  
	  // ugly hacks
	  EXPORT CUnit* GetSeenUnit(void) { return (mSeenUnit); }

	  // Name of the tag the unit was loaded from
	  std::string tagName;
	  
	  int needsAttack;
  UIRingMenu *mRingMenu;

  EXPORT void StopAttacksFor(int howlong)
  {
    mStopAttackCnt = howlong;
  }

private:  
	  // data members
	  ID   mID;  // Unit ID.
	  bool mShutdown; //true when shutdown due to undersync
	  CMech        *mMech;  // Mech the unit is piloting.
	  std::string   mName;  // Unit name.
	  
	  std::string  mScript;
	  
	  std::string mResponseSeeEnemy;
	    
	  int   mTeam;      // Team owning the unit.
	  int   mPlayer;    // Player controlling the unit.
	  bool  mSelected;  // True if unit is selected.
	  
	  float                                 mDestX;      // Final destination, X.
	  float                                 mDestY;      // Final destination, Y.
    std::vector< nsl::point2D< float > >  mPathSteps;  // Intermediate world coordinates in current movement path.

    
    bool        mRingMenuVis;
    CText      *mNameObj;
    
    CUnit *mSeenUnit;
    
    int    mFace;
    float  mFaceAngle;
    
    int mStopAttackCnt;
    
    bool mDead;
	int mPrimedAttack;
};


#endif  /* _C_UNIT_H_ */
