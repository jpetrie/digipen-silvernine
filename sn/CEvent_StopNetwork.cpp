/*! =========================================================================
      
      @file    CEvent_StopNetwork.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_StopNetwork.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_StopNetwork::CEvent_StopNetwork(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_StopNetwork)
{
}


/*  _________________________________________________________________________ */
CEvent_StopNetwork::~CEvent_StopNetwork(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_StopNetwork::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
	// Tell the game engine that we're no longer in a net game state
	CGame->SetNetGame(false);

	// Clear the socket and datagram lists so nothing will be listened on
	NetworkManager->ClearSocketList();
	NetworkManager->ClearDatagramList();

	// Load the script for the main screen
	CGame->LoadUIScreen("data/script/ui_mainmenu.uis");
}