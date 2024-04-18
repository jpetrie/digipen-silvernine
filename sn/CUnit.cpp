/*! =========================================================================
      
      @file    CUnit.cpp
      @brief   Implementation of the unit class.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CGameEngine.h"

#include "CTagMgrS.h"
#include "CTag_strc.h"
#include "CTag_unit.h"

#include "CUnit.h"
#include "UIButton.h"

#include "CEvent_UnitMove.h"
#include "CEvent_UnitAttack.h"
#include "CEvent_UnitDestroy.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CUnit::CUnit(const std::string &tag,int team,int player,float x,float y)
/*! @brief Constructor.

    Constructs a new unit object. If the parameters are allowed to default,
    the unit will be initialized with legal, but probably useless, values.
    
    @param tag     The unit tagfile to construct the unit from.
    @param team    The index of the team the unit belongs to.
    @param player  The index of the player the unit belongs to.
    @param x       Initial X world position.
    @param y       Initial Y world position.
*/
: mID(0),
  mTeam(team),mPlayer(player),
  mSelected(false),
  mMech(0),
  mRingMenu(0),mRingMenuVis(false),
  mFace(0),mFaceAngle(0.0f)
{  
  mNameObj = 0;
  if(tag.length() > 0)
    LoadFromTag(tag);
  
  if(mMech != 0)
    mMech->Show(false);
    
  mSeenUnit = 0;
  mDead = false;
  mShutdown = false;
  mPrimedAttack = 0;
  needsAttack = -1;
  mStopAttackCnt =0;
}


/*  _________________________________________________________________________ */
CUnit::~CUnit(void)
/*! @brief Destructor.
*/
{
  // Release mech object.
  delete mMech;
}


/*  _________________________________________________________________________ */
void CUnit::LoadFromTag(const std::string &tag)
/*! @brief Reinitializes a unit from the specified tag.

    @param tag  The name of the tag to load data from.
*/
{ 
	tagName = tag;
CTag_unit *tTag = dcast< CTag_unit* >(CTagMgr->Unarchive(kTag_unit,tag));

nsl::stringlist tNames;

  if(0 != tTag)
  {
    // Set up the unit's mech.
    SetMech(tTag->mech);
    Show(false);
    
    std::ifstream  names("data/text/names.txt");
    if(names.is_open())
    {
        names.seekg(0,ios_base::end);
      int size = names.tellg();
      char *buffer = new char[size];
        names.seekg(0,ios_base::beg);
        names.read(buffer,size);
      tNames = nsl::stsplit_chr(buffer,"\n");
    }
      
    // Prevent divide-by-zero errors.
    if(tNames.size() == 0)
      mName = "Unknown Soldier";
    else
      mName = tNames[rand() % tNames.size()];
   
   mNameObj = new CText(mName,14,"Terminal");
    mNameObj->SetColor4f(1.0f,1.0f,1.0f,0.8f);
    mNameObj->SetVisible(false);
    mNameObj->SetWidth(256);
    mNameObj->SetHeight(64);
    mNameObj->SetWorldX(X());
    mNameObj->SetWorldY(Y());
    mNameObj->SetZOrder(-1000);
   
    mScript = tTag->script;
    names.close();
  }
  
  CTagMgr->Release(tTag);
}

void CUnit::GiveAttack(const CAttack &attack)
{
  mMech->mAttacks.push_back(attack);
  
  CGame->RequestScreen()->RemoveFromScreen(mRingMenu);
  //delete mRingMenu;
  mRingMenu = new UIRingMenu(X(),Y() + (Height() / 2.0f),500,500);
  mRingMenu->SetAbsSize(150,150);
  for(unsigned int i = 0; i < mMech->GetAttackCount(); ++i)
  {
  UIButton *tButton = new UIButton(1000 + i,0,0,0,0,"icons");

    //Technically, you shouldn't need to do this, but I dun did somethin janky
	//so keep it when screen doesn't clear the screen after this and before it
	//wants to display it -Sincerely HotBoy #1
    tButton->baseSprite->SetSequence(mMech->GetAttack(i).Icon(),0);
    mRingMenu->AddButton(tButton);
  }
  
  mRingMenu->SetExtent();
  CGame->RequestScreen()->AddToScreen(mRingMenu);
  mRingMenu->Draw(false);
}


/*  _________________________________________________________________________ */
void CUnit::SetMech(const std::string &tag)
/*! @brief Sets the unit's mech.

    @param tag  The name of the tag to load data from.
*/
{
  if(0 == mMech)
    mMech = new CMech;
    
  mMech->LoadFromTag(tag);
  
  // Rebuild ring menu with new abilities.
  delete mRingMenu;
  //CGame->RequestScreen()->RemoveFromScreen(mRingMenu); //This crashes
  mRingMenu = new UIRingMenu(X(),Y() + (Height() / 2.0f),500,500);
  mRingMenu->SetAbsSize(150,150);
  for(unsigned int i = 0; i < mMech->GetAttackCount(); ++i)
  {
  UIButton *tButton = new UIButton(1000 + i,0,0,0,0,"icons");

    //Technically, you shouldn't need to do this, but I dun did somethin janky
	//so keep it when screen doesn't clear the screen after this and before it
	//wants to display it -Sincerely HotBoy #1
    tButton->baseSprite->SetSequence(mMech->GetAttack(i).Icon(),0);
    mRingMenu->AddButton(tButton);
  }
  
  mRingMenu->SetExtent();
//<<<<<<< .mine
//=======
//  //CGame->RequestScreen()->AddToScreen(mRingMenu); //This crashes
//  //Dont add this until screen is set up
//  CGame->RequestScreen()->MenuList.push_back(mRingMenu);
//>>>>>>> .r82

  mRingMenu->Draw(false);

}


/*  _________________________________________________________________________ */
void CUnit::MovePathAppend(std::vector< nsl::point2D< float > > &path)
/*! @brief Appends extra steps to the movement path of the unit.
*/
{
  for(unsigned int i = 0; i < path.size(); ++i)
    mPathSteps.push_back(path[i]);
}


/*  _________________________________________________________________________ */
void CUnit::MovePathFlush(void)
/*! @brief Flushes the movement path of the unit.

    This can be used to halt a unit.
*/
{
  mPathSteps.clear();
  
  // So the unit doesn't try and move any more.
  mDestX = X();
  mDestY = Y();
}


/*  _________________________________________________________________________ */
void CUnit::MovePathDest(float x,float y)
/*! @brief Sets fine coordinates for final movement step.
*/
{
  MovePathFlush();

CEvent_UnitMove *tEvt = (CEvent_UnitMove*)CGame->MakeEvent(kEvent_UnitMove);

  tEvt->units.push_back(this);
  tEvt->x = x;
  tEvt->y = y;
  CGame->PostEvent(tEvt);
}

/*  _________________________________________________________________________ */
void CUnit::MovePathDestInternal(float x,float y)
/*! @brief Sets fine coordinates for final movement step.
*/
{
  mDestX = x;
  mDestY = y;
}


/*  _________________________________________________________________________ */
void CUnit::SetAttackTarget(float target_x,float target_y,unsigned int attack)
/*! @brief Sets the attack target of the unit.

    @param target  The object to target.
*/
{
CEvent_UnitAttack *tAttackEvt = scast< CEvent_UnitAttack* >(CGame->MakeEvent(kEvent_UnitAttack));
    
      // Make all the selected units attack.
      tAttackEvt->ground = true;
      tAttackEvt->ground_x = target_x;
      tAttackEvt->ground_y = target_y;
      tAttackEvt->target = 0;
      tAttackEvt->units.push_back(this);
      
      CGame->PostEvent(tAttackEvt);
}

	    
/*  _________________________________________________________________________ */
int CUnit::TestWithinRadius(float x,float y,float minor,float major)
/*! @brief Test if the unit is within the specified radius.

    @return
    1 if within, 0 if without.

*/
{
  if(nsl::pt_in_ellipse(x,y,minor,major,X(),Y()))
    return 1;
  return 0;
}

	    
/*  _________________________________________________________________________ */
void CUnit::Update(void)
/*! @brief Performs periodic updating.

    @param sim  The current game session.
*/
{
CGameState *tState = CGame->RequestState();
float       tXStep = 0.0f;
float       tYStep = 0.0f;
  
  if(Dead())
  {
    Show(false);
    ShowSelectionRect(false);
    ShowStatusBars(false);
	ShowName(false);
	ShowRingMenu(false);
    return;
  }
  
  // If unit isn't player controlled, run its script.
  if(CGame->RequestState()->thisPlayer != Player() && !mShutdown)
    ExecuteScript(nsl::stformat("data/script/controllers/%s.ucs",mScript.c_str())); 
  
  // Test to see if the unit is dead and should be removed.
  if(Armor() <= 0.0f)
  {
  CEvent_UnitDestroy *tEvt = (CEvent_UnitDestroy*)CGame->MakeEvent(kEvent_UnitDestroy);
  
    tEvt->unit = this;
    CGame->PostEvent(tEvt);
    return;
  }
  
  // If the unit is waiting to be able to attack, see if they've moved into range.
  if(needsAttack >= 0 && mStopAttackCnt <= 0)
  {
    // test within range
    if(nsl::pt_in_ellipse(X(),Y(),Mech()->GetAttack(needsAttack).MaxDistance(),Mech()->GetAttack(needsAttack).MaxDistance() / 2.0f,mDestX,mDestY))
    {
      SetAttackTarget(mDestX,mDestY,needsAttack);
      needsAttack = -1;
    }
  }
  
  if(mStopAttackCnt > 0)
    --mStopAttackCnt;
  
  // Test to see if the unit sees anybody.
  if(!mShutdown)
  {
    for(unsigned int i = 0; i < tState->map->mUnitList.size(); ++i)
    {
    CUnit *tUnit = tState->map->mUnitList[i];
    
      if(tUnit->Dead()) continue;
      
      // If this unit's team...
      if(Team() != tUnit->Team())
      {
        if(nsl::pt_in_ellipse(X(),Y(),mMech->RadarRadius(),mMech->RadarRadius() / 2.0f,tUnit->X(),tUnit->Y()))
        { 
          mSeenUnit = tUnit;
          if(!mResponseSeeEnemy.empty())
            ExecuteScript(nsl::stformat("data/script/responses/%s.urs",mResponseSeeEnemy.c_str())); 
          break;
        }
      }
    }
  }
  
  if(mPathSteps.size() > 0 && !mShutdown)
  // If there are still steps in our path...
  {
  float  tMag;
  
    if(mPathSteps.size() == 1) // Last step.
    {
      tXStep = (mDestX - X());
      tYStep = (mDestY - Y());
    }
    else
    {
      tXStep = mPathSteps[mPathSteps.size() - 2].x - X();
      tYStep = mPathSteps[mPathSteps.size() - 2].y - Y();
    }
    
    tMag = sqrt(tXStep * tXStep + tYStep * tYStep);
    if(abs(tXStep) < Speed())
      tXStep = 0;
    if(abs(tYStep) < Speed())
      tYStep = 0;
    if(tXStep != 0.0)
      tXStep /= tMag;
    if(tYStep != 0.0)
      tYStep /= tMag;

    // Use the step (if big enough) to compute the angle of the mech.
    // If the step is too small stick with the last angle.    
    if(tXStep == 0.0f && tYStep == 0.0f)
    {
      // Do nothing.
    }
    else if(abs(tXStep) <= std::numeric_limits<float>::epsilon())
    {
      mFaceAngle = (tYStep > 0.0f ? 90.0f : 270.0f);
    }
    else
    {
    CVector tHead(tXStep,tYStep,0.0f);
    CVector tBase(1.0f,0.0f,0.0f);
  
      tHead = tHead.Unit();
      mFaceAngle = (float)tHead.AngleD(tBase);
      if(tYStep < 0.0f)
        mFaceAngle = 360.0f - mFaceAngle;
    }
        
    // Scale the step by the speed of the mech.
    tXStep *= Speed();
    tYStep *= Speed();

    // Collision.
    for(unsigned int i = 0; i < tState->map->UnitCount(); ++i)
    {
    CUnit   *tU = tState->map->Unit(i);

		if(tU->Dead()) continue;

    CVector  tDir(tXStep,tYStep,0.0f);
    CVector  tOrtho(0.0f,0.0f,1.0f);
    CVector  tTurn = tDir ^ tOrtho;
    float    tTX,tTY;
    
      tTurn = tTurn.Unit();
      tTX = (float)tTurn.X() * Speed();
      tTY = (float)tTurn.Y() * Speed();

      // Don't test collision against yourself...
      if(tU != this &&
          nsl::ellipse_in_ellipse(X() + (Speed()*tXStep),Y() + (Speed()*tYStep),Radius(),Radius() / 2.0f,tU->X(),tU->Y(),tU->Radius(),tU->Radius() / 2.0f))
      {
        // If the other unit is stationary, we're allowed to pass through.
        if(tU->mPathSteps.empty())
        {
        }
        // If the other unit is faster than us, just stop and wait.
        else if(tU->Speed() > Speed())
        {
        }
        // If the other unit is slower, go around it.
        else
        {
          //tXStep = tTX;
         // tYStep = tTY;
        }
      }
    }
    
    // Facings. Huzzah.
    if(mFaceAngle >= 00.0f && mFaceAngle < 22.5f)
      mFace = 0;
    if(mFaceAngle >= 22.5f && mFaceAngle < 67.5f)
      mFace = 1;
    if(mFaceAngle >= 67.5f && mFaceAngle < 112.0f)
      mFace = 2;
    if(mFaceAngle >= 112.0f && mFaceAngle < 157.0f)
      mFace = 3;
    if(mFaceAngle >= 157.0f && mFaceAngle < 202.0f)
      mFace = 4;
    if(mFaceAngle >= 202.0f && mFaceAngle < 247.0f)
      mFace = 5;
    if(mFaceAngle >= 247.0f && mFaceAngle < 292.0f)
      mFace = 6;
    if(mFaceAngle >= 292.0f && mFaceAngle < 337.0f)
      mFace = 7;
    if(mFaceAngle >= 337.0f && mFaceAngle <= 360.0)
      mFace = 0;
      
    // Pop the step if we've reached its destination.
    if(tXStep == 0.0 && tYStep == 0.0)
      mPathSteps.pop_back();
  }
  else
  {
    tXStep = 0;
    tYStep = 0;
  }
    
  // Adjust unit position.
  SetPosition(X() + tXStep,Y() + tYStep);
  if(X() < Radius())
    SetPosition(Radius(),Y());
  if(Y() < 0.0f)
    SetPosition(X(),0.0f);
	
  
  
  // Update attacks.
  for(unsigned int i = 0; i < Mech()->GetAttackCount(); ++i)
    Mech()->GetAttack(i).Recharge();
  
  //Move ring menu.

  //mRingMenu->SetAbsPos(X(),Y()+(Height()/2.0f));
  mRingMenu->absPosition.x = X();
  mRingMenu->absPosition.y = Y() + (Height() / 2.0f);
//<<<<<<< .mine
  mRingMenu->Draw(mRingMenuVis);
//=======
//>>>>>>> .r82
  
  //mRingMenu->Draw(mRingMenuVis);//ESP NOT SAVED, was deleted

  
  // Adjust facing.
  mMech->mSprite->SetFacing(mFace);
	
  mNameObj->SetWorldX(X() - Radius());
  mNameObj->SetWorldY(Y() - 75);
  mNameObj->SetZOrder(-10000);
  
  // Update sync and let attacks recharge.
  mMech->TakeDamage(kDamageSync,-0.05f);
  
  // If the unit is below 10% sync level, make them shutdown.
  if(mMech->Sync() / mMech->SyncMax() < .10f)
  {
    mShutdown = true;
  }
  else
  {
    mShutdown = false;
  }
  
}
