/*! =========================================================================
      
      @file    CPacket_QueryForNetGames.cpp
      @author  plaukait
      @brief   QueryForNetGames Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_QueryForNetGames.h"
#include "CPacketFactory_QueryForNetGames.h"
#include "CPacket_RespondNetGameQuery.h"
#include "CGameEngine.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_QueryForNetGames::Handle(void * GameState, void * Socket)
{
	// Silence the compiler -- The correct GameState is accessed through the GameEngine
	GameState;

	// Check if I am a server and that a net game has been enabled
	if( CGame->RequestServerState()->IAmServer && CGame->NetGame())
	{
		// Send a response packet with the client ID and server name / game name
		CPacket_RespondNetGameQuery * pResponse = 
			reinterpret_cast<CPacket_RespondNetGameQuery *>(NetworkManager->MakePacket(kPacket_RespondNetGameQuery));

		// Set the data of the response packet
		pResponse->serverName = CGame->RequestServerState()->serverName;
		pResponse->gameName = CGame->RequestServerState()->gameName;
		pResponse->clientID = clientID;
		pResponse->serverAddress = CGame->RequestServerState()->serverAddress;

		// Send the data back to the client as a datagram -- all broadcasts must be as datagrams
		CDatagram sendingGram;
		sendingGram.Send(*pResponse, std::string("255.255.255.255"), GAME_PORT);
		sendingGram.Disconnect();

		return;
	}

	// No?
		// Discard this packet -- nothing needs to be done
	return;
}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_QueryForNetGames::Serialize()
{
	// The size field must be two bytes
	assert(2 == sizeof(short));
	
	stream << (short)0 << mType;
	stream << clientID;
	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());
	
	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveRequest DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_QueryForNetGames::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	short temp;
	stream.raw_set(rawData, len);
	stream >> temp;
	stream >> mType;
	stream >> clientID;
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_QueryForNetGames::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_QueryForNetGames constructor
*/
CPacket_QueryForNetGames::CPacket_QueryForNetGames() : CPacket( kPacket_QueryForNetGames ), clientAddress("NULL")
{
	mType = kPacket_QueryForNetGames;
	clientPort = 0;
}

/*!
	@brief		Destructor
*/
CPacket_QueryForNetGames::~CPacket_QueryForNetGames()
{
}