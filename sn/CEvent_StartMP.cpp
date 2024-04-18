/*! =========================================================================
      
      @file    CEvent_StartMP.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_StartMP.h"
#include "CEvent_ArmyBegin.h"

namespace	// @todo These should be synched with CEvent_StartSP
{
  const std::string  ikPreload     = "data/preload/single.pre";
  const std::string  ikMultiPreload= "data/preload/multi.pre";
  const std::string  ikNewGameSave = "data/preload/newgame.sta";
};

/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_StartMP::CEvent_StartMP(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_StartMP)
{
}


/*  _________________________________________________________________________ */
CEvent_StartMP::~CEvent_StartMP(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_StartMP::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
	CEvent_ArmyBegin *tEvt = rcast< CEvent_ArmyBegin* >(CGame->MakeEvent(kEvent_ArmyBegin));
	std::ifstream     tPreload;

	CGraphicsMgr->BuildQuadTree(0,0,33000,33000);
	std::cout << "Starting Multi-player game...";

	// @todo FIXEME -- load a multiplayer map!!!
	// Unarchive the new game state and copy relevant data.
	data->Load(ikNewGameSave);

	// Read singleplayer preload.
	tPreload.open(ikMultiPreload.c_str());
	tPreload >> data->level;
	tPreload.close();

	//Clear old screen echan
	//CGame->RequestScreen()->ClearScreen();

	// Start army management.

	// END FIXEME

	CGame->PostEvent(tEvt);

}