/*! =========================================================================
      
      @file    CPacket_StartGameResponse.cpp
      @author  YOUR NAME HERE
      @brief   StartGameResponse Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_StartGameResponse.h"
#include "CPacketFactory_StartGameResponse.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_StartGameResponse::Handle(void * GameState, void * Socket)
{

}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_StartGameResponse::Serialize()
{
	// The size field must be two bytes
	assert(2 == sizeof(short));
	
	stream << (short)0 << mType;
	stream << response;
	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());
	
	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveRequest DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_StartGameResponse::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	short temp;
	stream.raw_set(rawData, len);
	stream >> temp;
	stream >> mType;
	stream >> response;
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_StartGameResponse::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_StartGameResponse constructor
*/
CPacket_StartGameResponse::CPacket_StartGameResponse(void) : CPacket( kPacket_StartGameResponse )
{
	mType = kPacket_StartGameResponse;
}

/*!
	@brief		Destructor
*/
CPacket_StartGameResponse::~CPacket_StartGameResponse(void)
{
}