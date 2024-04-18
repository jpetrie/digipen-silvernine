/*! =========================================================================
      
      @file    CPacket_TEMPLATE.cpp
      @author  YOUR NAME HERE
      @brief   TEMPLATE Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_TEMPLATE.h"
#include "CPacketFactory_TEMPLATE.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_TEMPLATE::Handle(void * GameState, void * Socket)
{

}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_TEMPLATE::Serialize()
{
	assert(2 == sizeof(short));
	
	stream << (short)(0) << mType;
	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());

	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveRequest DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_TEMPLATE::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	short temp;
	stream.raw_set(rawData, len);
	stream >> temp;
	stream >> mType;
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_TEMPLATE::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_TEMPLATE constructor
*/
CPacket_TEMPLATE::CPacket_TEMPLATE(void) : CPacket( kPacket_TEMPLATE )
{
	mType = kPacket_TEMPLATE;
}

/*!
	@brief		Destructor
*/
CPacket_TEMPLATE::~CPacket_TEMPLATE(void)
{
}