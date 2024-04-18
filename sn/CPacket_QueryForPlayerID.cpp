/*! =========================================================================
      
      @file    CPacket_QueryForPlayerID.cpp
      @author  YOUR NAME HERE
      @brief   QueryForPlayerID Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_QueryForPlayerID.h"
#include "CPacketFactory_QueryForPlayerID.h"
#include "CPacket_RespondQueryPlayerID.h"
#include "CNetworkMgrS.h"
#include "CGameEngine.h"
#include "CPacket_Seed_Random_Number.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_QueryForPlayerID::Handle(void * GameState, void * Socket)
{
	CPacket * response = NetworkManager->MakePacket(kPacket_RespondQueryPlayerID);
	((CPacket_RespondQueryPlayerID *)response)->yourID = CGame->RequestServerState()->currentUserID++;
	
	CSocket * sendSock = (CSocket *)Socket;
	sendSock->Send(*response);

	// send the random number seed
	// Note that the seed # is set in the packet constructor (you can't change it from here)
	CPacket_Seed_Random_Number * randSeed = scast<CPacket_Seed_Random_Number *>(NetworkManager->MakePacket(kPacket_Seed_Random_Number));
	sendSock->Send(*randSeed);
}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_QueryForPlayerID::Serialize()
{
	// The size field must be two bytes
	assert(2 == sizeof(short));
	
	stream << (short)0 << mType;
	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());
	
	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveRequest DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_QueryForPlayerID::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	short temp;
	stream.raw_set(rawData, len);
	stream >> temp;
	stream >> mType;
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_QueryForPlayerID::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_QueryForPlayerID constructor
*/
CPacket_QueryForPlayerID::CPacket_QueryForPlayerID(void) : CPacket( kPacket_QueryForPlayerID )
{
	mType = kPacket_QueryForPlayerID;
}

/*!
	@brief		Destructor
*/
CPacket_QueryForPlayerID::~CPacket_QueryForPlayerID(void)
{
}