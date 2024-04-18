/*! =========================================================================
      
      @file    CEvent_HostNetworkGame.cpp
      @brief   Does the necessary processing for hosting a network game
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_HostNetworkGame.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_HostNetworkGame::CEvent_HostNetworkGame(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_HostNetworkGame)
{
}


/*  _________________________________________________________________________ */
CEvent_HostNetworkGame::~CEvent_HostNetworkGame(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_HostNetworkGame::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
	// Set the IAmServer boolean in the ServerState to true
	CGame->SetNetGame(true);
	(CGame->RequestServerState())->IAmServer = true;

	// Create a listening datagram to recv incoming transmissions
	CDatagram listen;
	listen.Listen(GAME_PORT);

	// Get the local IP address
	const int BUFF_SIZE = 100;
	char tempBuff[BUFF_SIZE];
	
	if(gethostname(tempBuff, BUFF_SIZE) < 0)
		nlTHROW("Error getting host name");
	struct hostent * host;
	if( 0== (host = gethostbyname(tempBuff)) )
		nlTHROW("Error getting host by name");

	// Call some BSD functions to convert the mangled name to an actual IP address
	struct in_addr addr;
	memcpy(&addr, host->h_addr_list[0], sizeof(struct in_addr));
	CGame->RequestServerState()->serverAddress = inet_ntoa(addr);

	// Load the UI Chat screen
	//CGame->LoadUIScreen("data/script/ui_hostconfig.uis");
	CGame->LoadUIScreen("data/script/ui_chat.uis:");
	int pos = CGame->RequestScreen()->NewText(200, 200, 400, 300, 0, "Enter Game Name");
	CGame->RequestServerState()->TextBox = (UIText *)(CGame->RequestScreen()->MenuList[pos]);
	CGame->RequestServerState()->TextType = CGameState::SERVER_NAME_ENTRY;
}