/*! =========================================================================
      
      @file    CEvent_StartNetworkGame.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_StartNetworkGame.h"

// HACK
#include "CEvent_StartSP.h"
// END HACK

#include "CPacket_StartGameCommand.h"
#include "CPacket_SendArmyData.h"

/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_StartNetworkGame::CEvent_StartNetworkGame(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_StartNetworkGame)
{
}


/*  _________________________________________________________________________ */
CEvent_StartNetworkGame::~CEvent_StartNetworkGame(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_StartNetworkGame::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
	CPacket_StartGameCommand * pStart = rcast<CPacket_StartGameCommand *>(NetworkManager->MakePacket(kPacket_StartGameCommand));
	pStart->response = 1;

	// Send army data to each client
	std::vector<CSocket>::iterator socks = NetworkManager->sockList.end();
	--socks;

	for(; socks != (NetworkManager->sockList.begin() + 1); --socks)
	{
		int size = CGame->RequestState()->teams.size();
		for(int i = 0; i < CGame->RequestState()->teams.size(); ++i)
		{
			if(0 != CGame->RequestState()->teams[i])
			{
				CPacket_SendArmyData * pSend = rcast<CPacket_SendArmyData *>(NetworkManager->MakePacket(kPacket_SendArmyData));
				pSend->playerID = i;
				(*socks).Send(*pSend);
			}
		}
	}


	// Tell everyone to start
	socks = NetworkManager->sockList.end();
	--socks;

	for(; socks != (NetworkManager->sockList.begin() + 1); --socks)
		(*socks).Send(*pStart);
}