/*! =========================================================================
      
      @file    CEvent_ArmyShop.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include <strstream>

#include "CEvent_ArmyShop.h"



/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_ArmyShop::CEvent_ArmyShop(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_ArmyShop)
{
}


/*  _________________________________________________________________________ */
CEvent_ArmyShop::~CEvent_ArmyShop(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_ArmyShop::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
	// Load the UI.
	CGame->LoadUIScreen("data/script/ui_armyshop.uis");
	
	 /* if(CGame->RequestState()->army_Briefing != 0)
  {
    delete CGame->RequestState()->army_Briefing;
    CGame->RequestState()->army_Briefing = 0;
  } 
*/
	CGameState *state  = CGame->RequestState();
	UIScreen   *screen = CGame->RequestScreen();
	
//	state->army_Briefing->SetVisible(false);
state->army_Briefing->SetZOrder(-2000);

	// Build the army list.
	state->army_PlayerUnitsList = screen->NewButtonBox(25,100,200,375,"lstparts",0,0,"");
	for(unsigned int i = 0; i < state->unitShop.size(); ++i)
	{
	  char *s = new char[state->hireUnits[i]->Name().size() + 1];
	  
	  //jpetrie   modifying to load units so we get real names in here
	  
	  sprintf(s,"%s",state->hireUnits[i]->Name().c_str());
		//sprintf(s,"%s",state->unitShop[i].c_str());
		screen->NewGroupedButton(state->army_PlayerUnitsList,"lstparts",1,kShopListBiasLO  + i,s);
		delete[] s;
	}

  state->army_Briefing->SetText("YAY");
	
	/*jpetrie   dummying these out, I don't think we're going to be using them :( 
	state->army_PlayerUnitsList = screen->NewButtonBox(285,100,200,375,"lstparts",0,0,"");
	for(unsigned int i = 0; i < state->ablpShop.size(); ++i)
	{
	  char *s = new char[state->ablpShop[i].size() + 1];
	  
		sprintf(s,"%s",state->ablpShop[i].c_str());
		screen->NewGroupedButton(state->army_PlayerUnitsList,"lstparts",1,kAblpListBiasLO  + i,s);
		delete[] s;
	}

	state->army_PlayerUnitsList = screen->NewButtonBox((float)CGraphicsMgr->Width()-250,100,200,375,"lstparts",0,0,"");
	for(unsigned int i = 0; i < state->ablmShop.size(); ++i)
	{
	  char *s = new char[state->ablmShop[i].size() + 1];
	  
		sprintf(s,"%s",state->ablmShop[i].c_str());
		screen->NewGroupedButton(state->army_PlayerUnitsList,"lstparts",1,kAblmListBiasLO  + i,s);
		delete[] s;
	}
	*/
}