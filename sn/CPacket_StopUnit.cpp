/*! =========================================================================
      
      @file    CPacket_StopUnit.cpp
      @author  YOUR NAME HERE
      @brief   StopUnit Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_StopUnit.h"
#include "CPacketFactory_StopUnit.h"
#include "CPacket_StopUnitResponse.h"
#include "CNetworkMgrS.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_StopUnit::Handle(void * GameState, void * Socket)
{
	// Create a response & send it to everyone
	CPacket_StopUnitResponse * resp = rcast<CPacket_StopUnitResponse *>(NetworkManager->MakePacket(kPacket_StopUnitResponse));
	resp->unitIDs = unitIDs;

	
	// Send to everyone
	std::vector<CSocket>::iterator socks = NetworkManager->sockList.end();
	--socks;

	for(; socks != (NetworkManager->sockList.begin() + 1); --socks)
	{
		(*socks).Send(*resp);
	}
}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_StopUnit::Serialize()
{
	// The size field must be two bytes
	assert(2 == sizeof(short));
	
	stream << (short)0 << mType;

	std::vector<CUnit *>::iterator it = units.begin();
	stream << units.size();
	for(; it != units.end(); ++it)
	{
		stream << (unsigned int)((*it)->Ident());
	}

	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());
	
	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveRequest DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_StopUnit::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	short temp;
	stream.raw_set(rawData, len);
	stream >> temp;
	stream >> mType;

	int size;
	stream >> size;
	int num;

	for(int i = 0; i < size; ++i)
	{
		stream >> num;
		unitIDs.push_back(num);
	}
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_StopUnit::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_StopUnit constructor
*/
CPacket_StopUnit::CPacket_StopUnit(void) : CPacket( kPacket_StopUnit )
{
	mType = kPacket_StopUnit;
}

/*!
	@brief		Destructor
*/
CPacket_StopUnit::~CPacket_StopUnit(void)
{
}