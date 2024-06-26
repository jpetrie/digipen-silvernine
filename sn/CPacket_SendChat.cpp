/*! =========================================================================
      
      @file    CPacket_SendChat.cpp
      @author  YOUR NAME HERE
      @brief   SendChat Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_SendChat.h"
#include "CPacketFactory_SendChat.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_SendChat::Handle(void * GameState, void * Socket)
{
	//CPacket_RelayChat * relay = rcast<CPacket_RelayChat *>(NetworkManager->MakePacket(kPacket_RelayChat));
	std::cout << message;
	// @fixeme
}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_SendChat::Serialize()
{
	// The size field must be two bytes
	assert(2 == sizeof(short));
	
	stream << (short)0 << mType;
	stream << message;

	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());
	
	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveRequest DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_SendChat::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	short temp;
	stream.raw_set(rawData, len);
	stream >> temp;
	stream >> mType;
	stream >> message;
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_SendChat::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_SendChat constructor
*/
CPacket_SendChat::CPacket_SendChat(void) : CPacket( kPacket_SendChat )
{
	mType = kPacket_SendChat;
}

/*!
	@brief		Destructor
*/
CPacket_SendChat::~CPacket_SendChat(void)
{
}