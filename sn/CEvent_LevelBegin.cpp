/*! =========================================================================
      
      @file    CEvent_LevelBegin.cpp
      @brief   Loads a level and starts the game.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_LevelBegin.h"
#include "CPacket_SendArmyData.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_LevelBegin::CEvent_LevelBegin(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_LevelBegin)
{
}


/*  _________________________________________________________________________ */
CEvent_LevelBegin::~CEvent_LevelBegin(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_LevelBegin::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
  if(CGame->RequestState()->teams[0]->GetSizeofActive() <= 0)
    return;



	// If we're on a network game, send the army data to the server & check if we can start the game
	if(CGame->NetGame())
	{
		if(CGame->RequestState()->okToStartNetGame)
		{
			std::cout << "Starting NET combat...\n";

			// Load the UI.
			CGame->LoadUIScreen("data/script/ui_game.uis");

			// Load the map.
			delete CGame->RequestState()->army_Briefing;
			CGame->RequestState()->army_Briefing = 0;
			  
			data->map = new CMap(data->level,&data->teams,nLoadCallback);
			CGraphicsMgr->SortTree();
			CGame->SetupForGameplay();


//<<<<<<< .mine
	for(unsigned int i = 0; i < data->map->mUnitList.size(); ++i)
		if(data->map->mUnitList[i]->Team() == data->thisTeam)
		{
			CGame->RequestScreen()->AddToScreen(data->map->mUnitList[i]->mRingMenu);
			for(unsigned int j = 0; j < data->map->mUnitList[i]->mRingMenu->ButtonList.size(); ++j)
				CGame->RequestScreen()->AddToScreen(data->map->mUnitList[i]->mRingMenu->ButtonList[j]);
		}
//=======
			  
			// Default zoom.
			CGraphicsMgr->SetZoom(1.5f);
		}
		else if(CGame->NetGame() && !CGame->RequestState()->sentArmyData)
		{
			CPacket_SendArmyData * sendArmy = rcast<CPacket_SendArmyData *>(NetworkManager->MakePacket(kPacket_SendArmyData));
			sendArmy->playerID = CGame->RequestState()->thisPlayer;
			CGame->GetServSock().Send(*sendArmy);
			CGame->RequestState()->sentArmyData = true;
		}
	}
	else
		{
//>>>>>>> .r82

			// Load the UI.
			CGame->LoadUIScreen("data/script/ui_game.uis");

			// Load the map.
			delete CGame->RequestState()->army_Briefing;
			CGame->RequestState()->army_Briefing = 0;
			  
			data->map = new CMap(data->level,&data->teams,nLoadCallback);
			CGraphicsMgr->SortTree();
			CGame->SetupForGameplay();


				for(unsigned int i = 0; i < data->map->mUnitList.size(); ++i)
		if(data->map->mUnitList[i]->Team() == data->thisTeam)
		{
			CGame->RequestScreen()->AddToScreen(data->map->mUnitList[i]->mRingMenu);
			for(unsigned int j = 0; j < data->map->mUnitList[i]->mRingMenu->ButtonList.size(); ++j)
				CGame->RequestScreen()->AddToScreen(data->map->mUnitList[i]->mRingMenu->ButtonList[j]);
		}  
			// Default zoom.
			CGraphicsMgr->SetZoom(1.5f);
		}
		
		
		  // Give each active unit some extra abilities.
  for(int i = 0; i < CGame->RequestState()->teams[0]->GetSizeofActive(); ++i)
  {
  int max = rand() % 2;
  
    for(unsigned int j = 0; j < max; ++j)
    {
    CAttack at(CGame->attacksAvail[ rand() % CGame->attacksAvail.size() ]);
    
      CGame->RequestState()->teams[0]->GetActiveUnit(i)->GiveAttack(at);
    }
  }
}


/*  _________________________________________________________________________ */
void CEvent_LevelBegin::nLoadCallback(const std::string &task)
/*! @brief Level load progress callback.

    @param task  A string passed from the map loader.
*/
{
  std::cout << "CB: " << task << "\n";
}
