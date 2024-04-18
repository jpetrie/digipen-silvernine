/*! =========================================================================
      
      @file    CPacket_RequestUnitAttack.cpp
      @author  YOUR NAME HERE
      @brief   RequestUnitAttack Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_RequestUnitAttack.h"
#include "CPacketFactory_RequestUnitAttack.h"
#include "CPacket_RespondUnitAttack.h"
#include "CNetworkMgrS.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_RequestUnitAttack::Handle(void * GameState, void * Socket)
{
	CPacket_RespondUnitAttack * response = rcast<CPacket_RespondUnitAttack *>(NetworkManager->MakePacket(kPacket_RespondUnitAttack));

	// Fill in the vector of attacking units
	response->ground = ground;
	response->ground_x = ground_x;
	response->ground_y = ground_y;

	if(false == ground)
        response->targetID = targetID;

	response->unitsToDoAttack = this->unitsToAttack;

	// send to everyone
	std::vector<CSocket>::iterator socks = NetworkManager->sockList.end();
	--socks;

	for(; socks != (NetworkManager->sockList.begin() + 1); --socks)
		(*socks).Send(*response);
}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_RequestUnitAttack::Serialize()
{
	assert(2 == sizeof(short));
	
	stream << (short)(0) << mType;

	char grnd = (char)ground;

	stream << grnd << ground_x << ground_y;

	std::vector<CUnit *>::iterator it = units.begin();
	stream << units.size();
	for(; it != units.end(); ++it)
		stream << (unsigned int)((*it)->Ident());

	if(false == ground)
        stream << (unsigned int)(target->Ident());

	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());

	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveRequest DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_RequestUnitAttack::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	short temp;
	stream.raw_set(rawData, len);
	stream >> temp;
	stream >> mType;

	char grnd;

	stream >> grnd;
	ground = (bool)grnd;
	stream >> ground_x;
	stream >> ground_y;
	int size;
	stream >> size;

	int num;
	for(int i = 0; i < size; ++i)
	{
		stream >> num;

		// push back into the vector of units to attack
		unitsToAttack.push_back(num);
	}

	if(false == grnd)
		stream >> targetID;
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_RequestUnitAttack::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_RequestUnitAttack constructor
*/
CPacket_RequestUnitAttack::CPacket_RequestUnitAttack(void) : CPacket( kPacket_RequestUnitAttack )
{
	mType = kPacket_RequestUnitAttack;
}

/*!
	@brief		Destructor
*/
CPacket_RequestUnitAttack::~CPacket_RequestUnitAttack(void)
{
}