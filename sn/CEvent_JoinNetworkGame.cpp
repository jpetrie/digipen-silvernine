/*! =========================================================================
      
      @file    CEvent_JoinNetworkGame.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_JoinNetworkGame.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_JoinNetworkGame::CEvent_JoinNetworkGame(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_JoinNetworkGame)
{
}


/*  _________________________________________________________________________ */
CEvent_JoinNetworkGame::~CEvent_JoinNetworkGame(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_JoinNetworkGame::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
	// Set the server game state's IAmServer to false
	((CGameEngine::instance())->RequestServerState())->IAmServer = false;

	// Create a listening datagram to recv incoming transmissions
	CDatagram listen;
	listen.Listen(GAME_PORT);
	
	// Send out a query for net games datagram -- broadcast to the entire lan
	CDatagram Query;
	CPacket * QueryPacket = CPacketFactory::ConstructPacket(kPacket_QueryForNetGames);
	((CPacket_QueryForNetGames *)QueryPacket)->clientID = CGame->RequestState()->thisPlayer;
	Query.Send(*QueryPacket, std::string("255.255.255.255"), GAME_PORT);

	// Close the datagram before the function exits
	Query.Disconnect();

	// Load the UI game select screen
	CGame->LoadUIScreen("data/script/ui_servselect.uis");
	
	// Create a new button box -> save the index in the game state (it will be addressed during server selection
	// to choose which server the user wishes to connect to)
	
	int ButtonBoxIndex = CGame->GetScreen()->NewButtonBox(200, 400, 100, 100, "chicky", 0, GetEventCode("ctsv"), "Servers");
	CGame->GetScreen()->MenuList[ButtonBoxIndex]->SetAbsSize(600, 600);
	CGame->RequestServerState()->ButtonBoxIndex = ButtonBoxIndex;
}