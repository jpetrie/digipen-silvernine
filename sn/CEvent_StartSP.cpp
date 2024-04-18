/*! =========================================================================
      
      @file    CEvent_StartSP.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_ArmyBegin.h"
#include "CEvent_StartSP.h"


/*                                                         internal constants
----------------------------------------------------------------------------- */

namespace
{
  const std::string  ikPreload     = "data/preload/single.pre";
  const std::string  ikMultiPreload= "data/preload/multi.pre";
  const std::string  ikNewGameSave = "data/preload/newgame.sta";
};


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_StartSP::CEvent_StartSP(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_StartSP)
{
}


/*  _________________________________________________________________________ */
CEvent_StartSP::~CEvent_StartSP(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_StartSP::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
CEvent_ArmyBegin *tEvt = rcast< CEvent_ArmyBegin* >(CGame->MakeEvent(kEvent_ArmyBegin));
std::ifstream     tPreload;

  CGraphicsMgr->BuildQuadTree(0,0,33000,33000);
  std::cout << "Starting single player game...";

  // Unarchive the new game state and copy relevant data.
  data->Load(ikNewGameSave);
  
  // Read singleplayer preload.
  tPreload.open(ikPreload.c_str());
  tPreload >> data->level;
  tPreload.close();
  
  // Start army management.
  CGame->PostEvent(tEvt);
}