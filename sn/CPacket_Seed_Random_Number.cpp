/*! =========================================================================
      
      @file    CPacket_Seed_Random_Number.cpp
      @author  YOUR NAME HERE
      @brief   Seed_Random_Number Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_Seed_Random_Number.h"
#include "CPacketFactory_Seed_Random_Number.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_Seed_Random_Number::Handle(void * GameState, void * Socket)
{
	// Client side handling (just seed the random number generator)
	srand(seed);
}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_Seed_Random_Number::Serialize()
{
	assert(2 == sizeof(short));
	
	stream << (short)(0) << mType;
	stream << seed;
	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());

	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveRequest DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_Seed_Random_Number::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	short temp;
	stream.raw_set(rawData, len);
	stream >> temp;
	stream >> mType;
	stream >> seed;
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_Seed_Random_Number::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_SEED_RANDOM_NUMBER constructor
*/
CPacket_Seed_Random_Number::CPacket_Seed_Random_Number(void) : CPacket( kPacket_Seed_Random_Number )
{
	mType = kPacket_Seed_Random_Number;
	seed = SEED_VAL;
}

/*!
	@brief		Destructor
*/
CPacket_Seed_Random_Number::~CPacket_Seed_Random_Number(void)
{
}