/*! =========================================================================
      
      @file    CPacket_RelayChat.cpp
      @author  YOUR NAME HERE
      @brief   RelayChat Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_RelayChat.h"
#include "CPacketFactory_RelayChat.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_RelayChat::Handle(void * GameState, void * Socket)
{
	std::cout << message;
}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_RelayChat::Serialize()
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
void CPacket_RelayChat::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
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
unsigned int CPacket_RelayChat::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_RelayChat constructor
*/
CPacket_RelayChat::CPacket_RelayChat(void) : CPacket( kPacket_RelayChat )
{
	mType = kPacket_RelayChat;
}

/*!
	@brief		Destructor
*/
CPacket_RelayChat::~CPacket_RelayChat(void)
{
}