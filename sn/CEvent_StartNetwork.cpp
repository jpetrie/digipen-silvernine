/*! =========================================================================
      
      @file    CEvent_StartNetwork.cpp
      @brief   Starts the network layer for mulitplayer games
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_StartNetwork.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_StartNetwork::CEvent_StartNetwork(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_StartNetwork)
{
}


/*  _________________________________________________________________________ */
CEvent_StartNetwork::~CEvent_StartNetwork(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_StartNetwork::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
	// Tell the game engine that we're starting a net game
	CGame->SetNetGame(true);	

	// Set a socket to listen on
	CSocket tSock;
	tSock.Listen(GAME_PORT);
	NetworkManager->AddSocketToList(tSock);

	// Load the script for the 	Host / Join screen
	CGame->LoadUIScreen("data/script/ui_joinhost.uis");
}