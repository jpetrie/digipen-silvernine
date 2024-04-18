/*! =========================================================================
      
      @file    CPacket_RespondNetGameQuery.cpp
      @author  plaukait
      @brief   RespondNetGameQuery Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_RespondNetGameQuery.h"
#include "CPacketFactory_RespondNetGameQuery.h"
#include "CGameEngine.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_RespondNetGameQuery::Handle(void * GameState, void * Socket)
{
	// Silence the compiler about unused parameters
	GameState;

	// Am I the client that requested the data?
	//if(clientID == CGame->RequestServerState()->thisPlayer)
	//{
	// The server must absolutely not handle this message!
	if(!(CGame->RequestServerState()->IAmServer))
	{
		// Yes? Add the appropriate data to the GameState
		gameName = serverName;
		CGame->RequestServerState()->gameName = serverName;
		CGame->RequestServerState()->servers.insert(std::make_pair(serverName, serverAddress));

		// Generate a new key for the server
		int key = ++(CGame->RequestState()->CurrentServerListCode);

		// Add the key and name to the index/name hash
		CGame->RequestServerState()->serverIndex.insert(std::make_pair(key, serverName));	

		// Add a button to the screen (button box)
		char * pName = new char[gameName.length() + 1];
		if(!pName)
			nlTHROW("Couldn't allocate memory for a server name buffer in RespondNetGameQuery");
		memcpy(pName, gameName.c_str(), gameName.length());
		pName[gameName.length()] = '\0';	// Null terminate the thing
		
		CGame->GetScreen()->NewGroupedButton(CGame->RequestServerState()->ButtonBoxIndex, "ui_mmenu", 0, key, pName);
		delete[] pName;
	//}
	}

	// No? Discard
	return;

}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_RespondNetGameQuery::Serialize()
{
	// The size field must be two bytes
	assert(2 == sizeof(short));
	
	stream << (short)0 << mType;
	stream << serverName;
	stream << gameName;
	stream << serverAddress;
	stream << clientID;
	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());
	
	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveRequest DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_RespondNetGameQuery::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	short temp;
	stream.raw_set(rawData, len);
	stream >> temp;
	stream >> mType;
	stream >> serverName;
	stream >> gameName;
	stream >> serverAddress;
	stream >> clientID;
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_RespondNetGameQuery::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_RespondNetGameQuery constructor
*/
CPacket_RespondNetGameQuery::CPacket_RespondNetGameQuery(void) : CPacket( kPacket_RespondNetGameQuery )
{
	mType = kPacket_RespondNetGameQuery;
}

/*!
	@brief		Destructor
*/
CPacket_RespondNetGameQuery::~CPacket_RespondNetGameQuery(void)
{
}