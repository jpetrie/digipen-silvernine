/*! =========================================================================
      
      @file    CPacket_MoveRequest.cpp
      @author  YOUR NAME HERE
      @brief   MoveRequest Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_MoveRequest.h"
#include "CPacketFactory_MoveRequest.h"
#include "CPacket_MoveResponse.h"
#include "CNetworkMgrS.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_MoveRequest::Handle(void * GameState, void * Socket)
{
	// Create a response packet
	CPacket_MoveResponse * response = rcast<CPacket_MoveResponse *>(NetworkManager->MakePacket(kPacket_MoveResponse));
	
	// Fill in the vector of units to move
	response->unitIDs = unitsToMove;
	response->x = x;
	response->y = y;
	response->moveOk = true;

	// Send to everyone
	std::vector<CSocket>::iterator socks = NetworkManager->sockList.end();
	--socks;

	for(; socks != (NetworkManager->sockList.begin() + 1); --socks)
	{
		(*socks).Send(*response);
	}
}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_MoveRequest::Serialize()
{
	// The size field must be two bytes
	assert(2 == sizeof(short));
	
	stream << (short)0 << mType;
	stream << x << y;

	std::vector<CUnit *>::iterator it = units.begin();
	stream << units.size();
	for(; it != units.end(); ++it)
	{
		std::cout << "User attempted to move Units: \n" << (*it)->Ident() <<  "   " << (*it)->Name() << std::endl;
		stream << (unsigned int)((*it)->Ident());
	}

	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());
	
	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveRequest DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_MoveRequest::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	short temp;
	stream.raw_set(rawData, len);
	stream >> temp;
	stream >> mType;
	stream >> x;
	stream >> y;

	int size;
	stream >> size;
	int num;

	for(int i = 0; i < size; ++i)
	{
		stream >> num;
		unitsToMove.push_back(num);
	}
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_MoveRequest::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_MoveRequest constructor
*/
CPacket_MoveRequest::CPacket_MoveRequest(void) : CPacket( kPacket_MoveRequest )
{
	mType = kPacket_MoveRequest;
}

/*!
	@brief		Destructor
*/
CPacket_MoveRequest::~CPacket_MoveRequest(void)
{
}