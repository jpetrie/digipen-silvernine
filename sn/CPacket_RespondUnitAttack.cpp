/*! =========================================================================
      
      @file    CPacket_RespondUnitAttack.cpp
      @author  YOUR NAME HERE
      @brief   RespondUnitAttack Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_RespondUnitAttack.h"
#include "CPacketFactory_RespondUnitAttack.h"
#include "CEvent_UnitAttack.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_RespondUnitAttack::Handle(void * GameState, void * Socket)
{
	CEvent_UnitAttack * attack = rcast<CEvent_UnitAttack *>(CGame->MakeEvent(kEvent_UnitAttack));
	attack->ground = ground;
	attack->ground_x = ground_x;
	attack->ground_y = ground_y;

	std::vector<CUnit *>::iterator it = CGame->RequestState()->map->mUnitList.begin();
	for(; it != CGame->RequestState()->map->mUnitList.end(); ++it)
	{
		for(int i = 0; i < unitsToDoAttack.size(); ++i)
		{
			int ident1 = (*it)->Ident();
			int unitident1 = unitsToDoAttack[i];

			attack->units.push_back((*it));
		}
	}

	// If ground == true, the target is bogus
	if(ground == false)
	{
		attack->target = CGame->RequestState()->map->Unit(targetID);
	}
}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_RespondUnitAttack::Serialize()
{
	assert(2 == sizeof(short));
	
	stream << (short)(0) << mType;

	/* 
	bool                   ground;    // True if attack is ground (XY) based, false if unit based.
    float                  ground_x;  // X coordinate of ground attack.
    float                  ground_y;  // Y coordinate of ground attack.
    int					   targetID;    // Target of unit based attack.
    std::vector< int >	   unitsToDoAttack;     // Units doing the attacking.

	*/

	char grnd = (char)ground;
	stream << grnd << ground_x << ground_y;

	stream << unitsToDoAttack.size();

	for(int i = 0; i < unitsToDoAttack.size(); ++i)
		stream << unitsToDoAttack[i];
	
	if(false == ground)
		stream << targetID;

	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());

	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveRequest DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_RespondUnitAttack::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	short temp;
	stream.raw_set(rawData, len);
	stream >> temp;
	stream >> mType;

	char grnd;
	stream >> grnd;
	stream >> ground_x;
	stream >> ground_y;

	int size;
	stream >> size;

	int num;
	for(int i = 0; i < size; ++i)
	{
		stream >> num;
		unitsToDoAttack.push_back(num);
	}

	if(false == grnd)
		stream >> targetID;
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_RespondUnitAttack::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_RespondUnitAttack constructor
*/
CPacket_RespondUnitAttack::CPacket_RespondUnitAttack(void) : CPacket( kPacket_RespondUnitAttack )
{
	mType = kPacket_RespondUnitAttack;
}

/*!
	@brief		Destructor
*/
CPacket_RespondUnitAttack::~CPacket_RespondUnitAttack(void)
{
}