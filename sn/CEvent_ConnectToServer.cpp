/*! =========================================================================
      
      @file    CEvent_ConnectToServer.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_ConnectToServer.h"
#include "CPacket_QueryForPlayerID.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_ConnectToServer::CEvent_ConnectToServer(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_ConnectToServer)
{
}


/*  _________________________________________________________________________ */
CEvent_ConnectToServer::~CEvent_ConnectToServer(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_ConnectToServer::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
	// Get the info from the server state
	std::string & name = CGame->RequestServerState()->serverIndex[CGame->RequestServerState()->userServerChoice];
	std::string & ip   = CGame->RequestServerState()->servers[name];

	// Send out a holla to the server 
	CSocket & sock = CGame->GetServSock();
	sock.Connect(ip, GAME_PORT);

	// Ask the server what our ID should be
	CPacket * requestID = NetworkManager->MakePacket(kPacket_QueryForPlayerID);
	sock.Send(*requestID);

	return;
}