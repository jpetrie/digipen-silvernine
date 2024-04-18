/*! =========================================================================
      
      @file    CPacket_JoinRequest.cpp
      @author  plaukait
      @brief   JoinRequest Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_JoinRequest.h"
#include "CPacketFactory_JoinRequest.h"
#include "CPacket_JoinResponse.h"
#include "CPacketFactory_JoinResponse.h"
#include "CNetworkMgrS.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_JoinRequest::Handle(void * GameState, void * Socket)
{
	// Client -> Server
	// The client sends a response packet
	CPacket * responsePacket = (CNetworkMgrS::instance())->MakePacket(kPacket_JoinResponse);
	CSocket * pSocket = (CSocket *)Socket;
	pSocket->Send(*responsePacket);
}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_JoinRequest::Serialize()
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
void CPacket_JoinRequest::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	stream.raw_set(rawData, len);
	short temp;
	stream >> temp;
	stream >> mType;
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_JoinRequest::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_JoinRequest constructor
*/
CPacket_JoinRequest::CPacket_JoinRequest(void) : CPacket( kPacket_JoinRequest )
{
	mType = kPacket_JoinRequest;
}

/*!
	@brief		Destructor
*/
CPacket_JoinRequest::~CPacket_JoinRequest(void)
{
}