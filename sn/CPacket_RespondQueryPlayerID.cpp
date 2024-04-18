/*! =========================================================================
      
      @file    CPacket_RespondQueryPlayerID.cpp
      @author  YOUR NAME HERE
      @brief   RespondQueryPlayerID Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_RespondQueryPlayerID.h"
#include "CPacketFactory_RespondQueryPlayerID.h"
#include "CGameEngine.h"
#include "CEvent_StartMP.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_RespondQueryPlayerID::Handle(void * GameState, void * Socket)
{
	// Set the ID that the server said was yours
	CGame->RequestState()->thisPlayer = yourID;

	// Generate an event to start the multiplayer game
	CEvent_StartMP * event = rcast<CEvent_StartMP *>(CGame->MakeEvent(kEvent_StartMP));
	CGame->PostEvent(event);
}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_RespondQueryPlayerID::Serialize()
{
	// The size field must be two bytes
	assert(2 == sizeof(short));
	
	stream << (short)0 << mType;
	stream << yourID;
	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());
	
	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveRequest DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_RespondQueryPlayerID::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	short temp;
	stream.raw_set(rawData, len);
	stream >> temp;
	stream >> mType;
	stream >> yourID;
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_RespondQueryPlayerID::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_RespondQueryPlayerID constructor
*/
CPacket_RespondQueryPlayerID::CPacket_RespondQueryPlayerID(void) : CPacket( kPacket_RespondQueryPlayerID )
{
	mType = kPacket_RespondQueryPlayerID;
}

/*!
	@brief		Destructor
*/
CPacket_RespondQueryPlayerID::~CPacket_RespondQueryPlayerID(void)
{
}