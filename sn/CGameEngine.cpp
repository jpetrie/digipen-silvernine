/*! =========================================================================
      
      @file    CGameEngine.cpp
      @brief   Implementation of game engine class.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CGameEngine.h"

#include "CRect.h"

#include "CEvent_UnitAttack.h"
#include "CEvent_UnitMove.h"
#include "CEvent_UnitStop.h"
#include "CEvent_UnitSelect.h"
#include "CEvent_CreateProjectile.h"
#include "CEvent_TextBoxEntry.h"
#include "CProjectileGroup.h"
#include "UIRingMenu.h"
#include "UIButton.h"
//<<<<<<< .mine
#include "CSoundMgrS.h"
//=======
#include "CEvent_LevelEnd.h"//REMOVE ME
//>>>>>>> .r82

EXPORT CMap* GlobalMap(void)
{
  return (CGame->RequestState()->map);
}

/*                                                         internal constants
----------------------------------------------------------------------------- */

namespace
{
  const int  ikDefaultFrameTime = 10;
}


/*                                                           member functions
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CGameEngine::CGameEngine()
/* @brief Default constructor.
*/
: mFrameTime(ikDefaultFrameTime),
  mLastTime(0),mElapsedTime(0), 
  mClientState(new CGameState),mServerState(new CGameState)
{
  // Set the resolution of the timer.
  timeBeginPeriod(1);
  
  memset(mKeys,0,sizeof(bool) * 256);

  mScreen = new UIScreen();
  mScreen->ExecuteScript("data/script/ui_mainmenu.uis");
 
  mScreen->Show(true);
  
  mSelRect = 0;

  mClickTime = 0;
  
   mAbort = false;

  NetworkGame = false;
}


/*  _________________________________________________________________________ */
CGameEngine::~CGameEngine()
/* @brief Destructor.
*/
{
  // Must match call to timeBeginPeriod().
  timeEndPeriod(1);

  delete mClientState;
  delete mServerState;
  
  if(mSelRect)
    delete mSelRect;
  
  mSelecting = false;
  delete mScreen;
}


/*  _________________________________________________________________________ */
CEvent* CGameEngine::MakeEvent(CEvent::ID evt)
/* @brief Creates a new event.
*/
{
  return (CEventFactory::ConstructEvent(evt));
}


/*  _________________________________________________________________________ */
void CGameEngine::PostEvent(CEvent *evt)
/* @brief Posts an event to the queue.

   Note that this function can only be used to post to the client queue.
*/
{
  if(0 == evt)
    return;

  mClientQueue.push(evt);
}


/*  _________________________________________________________________________ */
void CGameEngine::ProcessServerTasks(void)
/* @brief Process server tasks.
*/
{
  if(0 != mServerState)
  {
    // Do something.
  }
}


/*  _________________________________________________________________________ */
void CGameEngine::ProcessClientTasks(void)
/* @brief Process client tasks.
*/
{
nsl::uint32_t  tThisTime = 0;
nsl::uint32_t  tElapsedTime = 0;
  
  if(mAbort == true)
    mAbort = false;
  
  // Calculate elapsed time. Note that the timer rolls over every 2^32 milliseconds.
  tThisTime = timeGetTime();
  if(tThisTime < mLastTime)
	  tElapsedTime = mLastTime - tThisTime;
  else
	  tElapsedTime = tThisTime - mLastTime;

  // Handle events.
  nProcessUI(mClientState);
  nProcessQueue(mClientQueue,mClientState);

  // If enough time has gone by, fire an update.
  mElapsedTime += tElapsedTime;
  if(mElapsedTime >= mFrameTime)
  {
    nProcessUpdates(mClientState);
    mElapsedTime = 0;
  }
  
  // Save this time.
  mLastTime = tThisTime;

  // Render.
  CGraphicsMgr->ProcessGraphics();
}

/*  _________________________________________________________________________ */
void CGameEngine::LeftMouseDown(void)
/* @brief Handle left mouse click.
*/
{
	

nsl::point2D< float > tWorldPt = ScreenToWorld(mMouseX,mMouseY);

  mClickTime = timeGetTime();

  // In the menu shell...
  if(0 == mClientState->map)
  {
	ResponseCode code =	mScreen->RespondToLClick(tWorldPt.x,tWorldPt.y);
	
    // Test if the code was a network event for server selection.
	// The code is not valid for an event, since it was created with the
	// purpose of encoding the index within the server list (maintained by the
	// user interface) for easy retrieval here.  The connect method must know
	// the code to get the proper entry in the hash map maintained in the
	// game state.
	// NOTE :: keycodes 1 - 256 are reserved by the newtwork engine.  
	// If you happen to have one in this range, don't!

	const int NET_CODE_MAX = 257;

		if( NetGame() && (code < NET_CODE_MAX) && (code > 0) )
		{
			RequestServerState()->userServerChoice = code;
			PostEvent(CGame->MakeEvent(nlFOURCODE('c','t','s','v')));
		}
		else if(code <= kArmyListBiasHi && code >= kArmyListBiasLo)
		{
		  std::cout << code << "\n";
		  code -= kArmyListBiasLo;
		  
		  // Iterate the active units
		CUnit *tUnit =mClientState->teams[mClientState->thisTeam]->GetUnit(code);
		bool   add   = true;
		int remidx = 0;
		
		  // Wow, this is ugly stuff.
		  for(unsigned int i = 0; i < mClientState->teams[mClientState->thisTeam]->GetSizeofActive(); ++i)
		  {
		    if(tUnit == mClientState->teams[mClientState->thisTeam]->GetActiveUnit(i))
		    {
		      remidx = i;
		      add = false;
		      break;
		    }
		  }
		  
		  if(add)
		    mClientState->teams[mClientState->thisTeam]->AddActiveUnit(tUnit);
		  else
		    mClientState->teams[mClientState->thisTeam]->RemActiveUnit(remidx);
		}
		else if(code < kShopListBiasHI && code >= kShopListBiasLO)
		{
		  if (code < kUnitListBiasHI) // code is from unit list
		  {
			  int idx = code - kShopListBiasLO;       
        
        std::vector<int>::iterator iter = mWaitingUnits.begin();
        while(iter != mWaitingUnits.end() )
        {
			    if(*iter == idx)
			    {
			      mWaitingUnits.erase(iter);
			      return;
			    }
			    else       
			      ++iter; 
		    }// end while
		    mWaitingUnits.push_back(idx);
		    return;
		  }// end if kUnitBiasHI
		  else if (code < kAblpListBiasHI)        // code is from physical ability list
		  {
		    int idx = code - kAblpListBiasLO;   
      		
			  std::vector<int>::iterator iter = mWaitingAblp.begin();
			  while(iter != mWaitingAblp.end() )
			  {
			    if(*iter == idx)
			    {
				    mWaitingAblp.erase(iter);
				    return;
			    }
			    else       
				    ++iter; 
			  }// end while
			    mWaitingAblp.push_back(idx);
			    return;
			}// end if kAblpListBiasHI
			else if (code < kAblmListBiasHI)        // code is from mental ability list
			{
			  int idx = code - kAblmListBiasLO;   
			  
			  std::vector<int>::iterator iter = mWaitingAblm.begin();
				while(iter != mWaitingAblm.end() )
				{
						if(*iter == idx)
						{
							mWaitingAblm.erase(iter);
							return;
						}
						else       
							++iter; 
				}// end while
				mWaitingAblm.push_back(idx);
				return;
			}//end if kAblmListBiasHI
		}
		else  if(code)
		{
			CEvent *event = CGame->MakeEvent(code);
			
			PostEvent(event);
		}
  }
  // In the game shell...
  else
  {
    ResponseCode code =	mScreen->RespondToLClick(tWorldPt.x,tWorldPt.y);
    std::cout << code << "\n";
  

	if(code >= 1000 && code < 2000)
	{
		if(mClientState->selected.size() == 1)
		{
			mClientState->selected[0]->PrimeAttack(code - 1000);
			mClientState->selected[0]->ShowRingMenu(false);
		}
		
	}

    // Test units for intersection with mouse cursor.
    mSelAnchor = tWorldPt;

    // Test units for intersection with mouse cursor.
    for(unsigned int i = 0; i < mClientState->map->UnitCount(); ++i)
    {
    CUnit *tUnit = mClientState->map->Unit(i);
    
      if(tUnit->Dead()) continue;
    
      if(nsl::pt_in_rect< float >(tWorldPt.x,tWorldPt.y,
                                  tUnit->X() - tUnit->Radius(),
                                  tUnit->Y() + tUnit->Height(),
                                  tUnit->X() + tUnit->Radius(),
                                  tUnit->Y()))
      {
      CEvent_UnitSelect *tSelectEvt = scast< CEvent_UnitSelect* >(CGame->MakeEvent(kEvent_UnitSelect));
        
        // Attack enemy units.
        if(tUnit->Team() != mClientState->thisTeam)
        {
        CEvent_UnitAttack *tAttackEvt = scast< CEvent_UnitAttack* >(CGame->MakeEvent(kEvent_UnitAttack));
        
          // Make all the selected units attack.
          tAttackEvt->ground = false;
          tAttackEvt->ground_x = 0.0f;
          tAttackEvt->ground_y = 0.0f;
          tAttackEvt->target = tUnit;
          tAttackEvt->units = mClientState->selected;
          
          CGame->PostEvent(tAttackEvt);
          return;
        }
        
        if(GetKey(VK_SHIFT))
        {
          tSelectEvt->unit = tUnit;
          CGame->PostEvent(tSelectEvt);
        }
        else if(!tUnit->Selected())
        {
          // First deselect everybody else, then select the new unit.
          for(unsigned int j = 0; j < mClientState->selected.size(); ++j)
            mClientState->selected[j]->Selected(false);
            
          mClientState->selected.clear();
          tSelectEvt->unit = tUnit;
          CGame->PostEvent(tSelectEvt);
        }
        else
        {
          // Click an already-selected unit without the shift key
          // deselects the existing units and selects the new one.
          for(unsigned int j = 0; j < mClientState->selected.size(); ++j)
            mClientState->selected[j]->Selected(false);
            
          mClientState->selected.clear();
          tSelectEvt->unit = tUnit;
          CGame->PostEvent(tSelectEvt);
        }
        return;
      }
    }
    
    // If we get here, we clicked on the ground. Yay.
    if(!mClientState->selected.empty() && GetKey(VK_CONTROL))
    {
    CEvent_UnitAttack *tAttackEvt = scast< CEvent_UnitAttack* >(CGame->MakeEvent(kEvent_UnitAttack));
    
      // Make all the selected units attack.
      tAttackEvt->ground = true;
      tAttackEvt->ground_x =tWorldPt.x;
      tAttackEvt->ground_y =tWorldPt.y;
      tAttackEvt->target = 0;
      tAttackEvt->units = mClientState->selected;
      
      CGame->PostEvent(tAttackEvt);
    }
    else if(!mClientState->selected.empty())
    {
    CEvent_UnitMove *tMoveEvt = scast< CEvent_UnitMove* >(CGame->MakeEvent(kEvent_UnitMove));
      
      // Move all the selected units.
      for(unsigned int i = 0; i < mClientState->selected.size(); ++i)
        if(mClientState->selected[i]->Dead())
          mClientState->selected.erase(mClientState->selected.begin() + i);
          
      tMoveEvt->units = mClientState->selected;
      tMoveEvt->x = tWorldPt.x;
      tMoveEvt->y = tWorldPt.y;
      CGame->PostEvent(tMoveEvt);
    }
  }
}


/*  _________________________________________________________________________ */
void CGameEngine::RightMouseDown(void)
/* @brief Handle right mouse click.
*/
{
nsl::point2D< float > tWorldPt = ScreenToWorld(mMouseX,mMouseY);

  // In the menu shell...
  if(0 == mClientState->map)
  {
  }
  else
  {
	  if(mClientState->selected.size() != 1)
		return;

    // Test units for intersection with mouse cursor.
    for(unsigned int i = 0; i < mClientState->map->UnitCount(); ++i)
    {
    CUnit *tUnit = mClientState->map->Unit(i);
    
      if(tUnit->Dead() || !tUnit->Selected()) continue;
      
      if(nsl::pt_in_rect< float >(tWorldPt.x,tWorldPt.y,
                                tUnit->X() - tUnit->Radius(),
                                tUnit->Y() + tUnit->Height(),
                                tUnit->X() + tUnit->Radius(),
                                tUnit->Y()))
      {
        if(tUnit->IsRingMenuVisible())
          tUnit->ShowRingMenu(false);
        else
		{
          tUnit->ShowRingMenu(true);
		  CGame->RequestScreen()->flickMode = true;
		  CGame->RequestScreen()->flickMenu = tUnit->mRingMenu;
		  CGame->RequestScreen()->flickPoint = tWorldPt;
		}
      }
    }
    
  }
}


/*  _________________________________________________________________________ */
void CGameEngine::LeftMouseUp(void)
/* @brief Handle left mouse up.
*/
{ 
  if(0 == mClientState->map)
  {
	Effect e;
	e.PlayEffect("./data/patch/sound collections/pop1.wav", FSOUND_FREE);
  {
  }
  }
  // In the menu, we don't care about this.
  if(0 == mClientState->map)
    return;

  if(mSelecting && (timeGetTime() - mClickTime) > 200)
  {
    // First deselect everybody else, then select the new units.
    for(unsigned int j = 0; j < mClientState->selected.size(); ++j)
      mClientState->selected[j]->Selected(false);
    mClientState->selected.clear();
  
    // Only iterate through units that are selectable (i.e., on the same team).
    for(unsigned int i = 0; i < mClientState->map->SizeOfActiveTeam(mClientState->thisTeam); ++i)
    {
    CUnit *tUnit = mClientState->map->UnitOfActiveTeam(mClientState->thisTeam,i);
    
      if(tUnit->Dead()) continue;
      if(nsl::pt_in_rect< float >(tUnit->X(),tUnit->Y(),
                                mSelRect->GetWorldX(),
                                mSelRect->GetWorldY() + mSelRect->GetHeight(),
                                mSelRect->GetWorldX() + mSelRect->GetWidth(),
                                mSelRect->GetWorldY()))
      {
      CEvent_UnitSelect *tSelectEvt = scast< CEvent_UnitSelect* >(CGame->MakeEvent(kEvent_UnitSelect));
        
        tSelectEvt->unit = tUnit;
        CGame->PostEvent(tSelectEvt);
      }
    }
  }
  
  mSelRect->SetVisible(false);
  mSelecting = false;
}


/*  _________________________________________________________________________ */
void CGameEngine::LeftMouseDrag(void)
/* @brief Handle left mouse drag.
*/
{
nsl::point2D< float >  tPointer = ScreenToWorld(mMouseX,mMouseY);

  // In the menu, we can't drag anything.
  if(0 == mClientState->map)
    return;

  if(!mSelecting)
  {
    mSelRect->SetWorldX(mSelAnchor.x);
    mSelRect->SetWorldY(mSelAnchor.y);
    mSelecting = true;
  }
  
  mSelRect->SetWidth(tPointer.x - mSelAnchor.x);
  mSelRect->SetHeight(tPointer.y - mSelAnchor.y);
  
  mSelRect->SetVisible(true);
  mSelRect->SetZOrder(-1000);
}

/*  _________________________________________________________________________ */
void CGameEngine::MouseMove(int x, int y)
/* @brief Handle left mouse drag.
*/
{
	ResponseCode code = 0;
	
	//is there a UIRingMenu up?
	if(CGame->RequestScreen()->flickMode)
	{
		nsl::point2D<float> temp = ScreenToWorld(x,y);
		
		//Should do something that notifies which the player picked
		code = CGame->RequestScreen()->RespondToMouseMove(temp.x, temp.y);
	}
	//Process codes
	if(code >= 1000 && code < 2000)
	{
		if(mClientState->selected.size() == 1)
		{
			mClientState->selected[0]->PrimeAttack(code - 1000);
			mClientState->selected[0]->ShowRingMenu(false);
		}
		
	}
}

/*  _________________________________________________________________________ */
void CGameEngine::SetupForGameplay(void)
/* @brief Set up for gameplay.
*/
{
	
  mAbort = false;
  mParallax = new CSprite(nsl::randfloat(0.f, mClientState->map->WorldWidth()), nsl::randfloat(0.f, mClientState->map->WorldHeight()), 1024, 1024, "effes");
  mParallaxTimer = 0;
  mParallaxDelay = 600; // game loops
  mParallaxXstep = nsl::randfloat(0.f, 1.f);
  mParallaxYstep = nsl::randfloat(0.f, 1.f);	
  mParallaxSpeed = nsl::randfloat(.5f, 2.f);
  mSelRect = new CRect(0,0,0,0);
  mSelRect->SetBorderColor(1.0f,1.0f,0.0f,0.9f);
  mSelRect->SetInteriorColor(1.0f,1.0f,0.0f,0.1f);
  mSelRect->SetVisible(false);
  mSelRect->SetZOrder(-1000);
  mSelecting = false;
}


/*  _________________________________________________________________________ */
void CGameEngine::EndGameplay(void)
/* @brief End gameplay.
*/
{
  delete mClientState->map;
  mClientState->map = 0;
  
  CGraphicsMgr->KillQuadTree();
  CGraphicsMgr->BuildQuadTree(0,0,40000,40000);
  CGraphicsMgr->SetZoom(1.0f);
  
  // Invalid IDs.
  mClientState->thisPlayer = -1;
  mClientState->thisTeam = -1;
  mClientState->CurrentServerListCode = 0;
  
  mAbort = true;
  delete mParallax;
}


/*  _________________________________________________________________________ */
void CGameEngine::nProcessQueue(CGameEngine::TEventQueue &q,CGameState *state)
/* @brief Process an event queue.
*/
{
  if(0 == state)
    return;
    
  while(!q.empty())
  {
  CEvent *tEvt = q.front();
  
    if(!mAbort)
      tEvt->Handle(state);
    q.pop();
    delete tEvt;
  }
}


/*  _________________________________________________________________________ */
void CGameEngine::nProcessUpdates(CGameState *state)
/* @brief Process updates for a state.
*/
{
  if(0 == state)
    return;

  // Gameplay updates.
  if(0 != state->map)
  {
    // Update the map.
      state->map->Update();
    
    // Update all units on the map.
    for(int i = 0; i < scast<int>(state->map->UnitCount()); ++i)
      state->map->Unit(i)->Update();

	for(unsigned int i = 0; i < RequestState()->projGroups.size(); ++i)
		RequestState()->projGroups[i]->Update();

  if(mParallaxTimer++ > mParallaxDelay)
  {
	  mParallaxTimer = 0;
	  // compute new direction
	  mParallaxXstep = ((rand() % 5) > 2 ? 1.f : -1.f) * nsl::randfloat(0.f, 1.f);
	  mParallaxYstep = ((rand() % 5) > 2 ? 1.f : -1.f) * nsl::randfloat(0.f, 1.f);	
	  mParallaxSpeed = nsl::randfloat(.5f, 2.f);
	 
  }
  mParallax->SetWorldX(mParallax->GetWorldX() + mParallaxSpeed * mParallaxXstep);
  mParallax->SetWorldY(mParallax->GetWorldY() + mParallaxSpeed * mParallaxYstep);	
  mParallax->SetZOrder(-10000);
	
  }
}


/*  _________________________________________________________________________ */
void CGameEngine::nProcessUI(CGameState *state)
/* @brief Process UI updates for a state.
*/
{
// 2 variables ->Thisteam, ThisPlayer, make sure that when a new player joins these are set correctly
// Thisteam index of the team that that client is in control of This player is probably the same #
// test if enter is down --> call get text

nsl::point2D< float > tWorldPt = ScreenToWorld(mMouseX,mMouseY);
const float trash = 0;
  
  // In a menu screen or somewhere where there is a screen
  if(mScreen && !mScreen->MenuList.empty())
  {
	  //Scrolling a UIText obj
	  if(GetKey(VK_DOWN))
	    mScreen->MenuList[mScreen->focusedControl]->Respond(ScrollDown);
	  if(GetKey(VK_UP))
	    mScreen->MenuList[mScreen->focusedControl]->Respond(ScrollUp);
	  if(GetKey(VK_SPACE))
		mScreen->MenuList[mScreen->focusedControl]->Respond(KeyPress, trash, trash, VK_SPACE);
	  if(GetKey(VK_BACK))
		mScreen->MenuList[mScreen->focusedControl]->Respond(KeyPress, trash, trash, VK_BACK);

	  /*if(GetKey(VK_RETURN) )
		{
			if(typeid(*(mScreen->MenuList[mScreen->focusedControl])) == typeid(UIText) )
			{
				(dynamic_cast<UIText*>(mScreen->MenuList[mScreen->focusedControl]))->textString;
				(dynamic_cast<UIText*>(mScreen->MenuList[mScreen->focusedControl]))->Clear();
			}
	  }*/
	  //Make into function
	  
	  // Check for the enter key on a menu screen
	  if(GetKey(VK_RETURN) && !mClientState->map)
	  {
		  if(CGame->RequestServerState()->TextBox->isFocused)
		  {			  
			  // Pass off the text to the event that handles new text box entries
			  CEvent_TextBoxEntry * Text = (CEvent_TextBoxEntry *)CGame->MakeEvent(nlFOURCODE('T', 'B', 'E', 'T'));
			  Text->text = CGame->RequestServerState()->TextBox->GetText();
			  CGame->PostEvent(Text);
		  }
	  }
  	
  	
	  for(int i='0';i<='Z' ; i++)
	  {
		  if(GetKey(i))
		  {
		    mScreen->MenuList[mScreen->focusedControl]->Respond(KeyPress, trash, trash, i);
		    break;
		  }
	  }
  }

  // Stop here if no state or not gameplay.
  if(0 == state || 0 == state->map)
    return;
 
  // Map movement.
  if(GetKey(VK_LEFT))
    CGraphicsMgr->ScrollLeft();
  if(GetKey(VK_RIGHT))
    CGraphicsMgr->ScrollRight();
  if(GetKey(VK_UP))
    CGraphicsMgr->ScrollUp();
  if(GetKey(VK_DOWN))
    CGraphicsMgr->ScrollDown();
  if(GetKey('A'))
	  CGraphicsMgr->ZoomIn();
  if(GetKey('Z'))
	  CGraphicsMgr->ZoomOut();
  //REMOVE ME
  if(GetKey('R') || GetKey('T'))
  {
	  CEvent_LevelEnd* end = new CEvent_LevelEnd;
	  end->win = GetKey('R')? false:true;
	  PostEvent(end);
  }
 
  /// Unit deselection.
  if(GetKey('X'))
  {
    for(unsigned int j = 0; j < mClientState->selected.size(); ++j)
      mClientState->selected[j]->Selected(false);
    mClientState->selected.clear();
  }
  
  // Bullet-time controls.
  if(GetKey('Q'))
    mFrameTime += 10;
  if(GetKey('W'))
    mFrameTime -= 10;
  if(mFrameTime < 10)
    mFrameTime = 10;
  if(mFrameTime > 1000)
    mFrameTime = 1000;
    
  // Unit stop controls.
  if(GetKey(VK_SPACE))
  {
  CEvent_UnitStop *tStopEvt = (CEvent_UnitStop*)MakeEvent(kEvent_UnitStop);
  
    tStopEvt->units = mClientState->selected;
    PostEvent(tStopEvt);
  }
  
  // Test units for intersection with mouse cursor.
  for(unsigned int i = 0; i < state->map->UnitCount(); ++i)
  {
  CUnit *tUnit = state->map->Unit(i);
    
    if(tUnit->Dead()) continue;
    
    if(tUnit->Selected())
    {
      tUnit->ShowStatusBars(true);
      tUnit->ShowSelectionRect(true);
      if(nsl::pt_in_rect< float >(tWorldPt.x,tWorldPt.y,
                              tUnit->X() - tUnit->Radius(),
                              tUnit->Y() + tUnit->Height(),
                              tUnit->X() + tUnit->Radius(),
                              tUnit->Y()))
							  tUnit->ShowName(true);
      else
        tUnit->ShowName(false);
    }
    else if(nsl::pt_in_rect< float >(tWorldPt.x,tWorldPt.y,
                              tUnit->X() - tUnit->Radius(),
                              tUnit->Y() + tUnit->Height(),
                              tUnit->X() + tUnit->Radius(),
                              tUnit->Y()))
    {
      std::cout << tUnit->Ident();
      tUnit->ShowStatusBars(true);
      tUnit->ShowSelectionRect(false);
      tUnit->ShowName(true);
    }
    else
    {
      tUnit->ShowStatusBars(false);
      tUnit->ShowSelectionRect(false);
      tUnit->ShowName(false);
    }
  }
}


/*  _________________________________________________________________________ */
void CGameState::nInit(void)
/* @brief Initializes game state data.
*/
{
  // NULL map pointer.
  // Testing this pointer is a reliable way to determine whether or not
  // the program is in gameplay mode.
  map = 0;
  
  // Invalid IDs.
  thisPlayer = -1;
  thisTeam = -1;
  CurrentServerListCode = 0;
  currentUserID = 0;
  sentArmyData = false;
  okToStartNetGame = false;
  RequiresMoveValidation = true;
  RequireStopValidation = true;
  
  army_Briefing = 0;
}



void DefinePlayerArmy(void)
{
  CGame->RequestState()->teams.push_back(new CArmy);
}

void DefinePlayerUnit(char *unit)
{
CUnit *u = new CUnit(unit);

  CGame->RequestState()->teams[0]->AddUnit(u);
}
