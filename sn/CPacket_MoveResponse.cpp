/*! =========================================================================
      
      @file    CPacket_MoveResponse.cpp
      @author  plaukait
      @brief   Move Response Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacket_MoveResponse.h"
#include "CEvent_UnitMove.h"
/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Handles server side processing on the packet
*/
void CPacket_MoveResponse::Handle(void * GameState, void * Socket)
{
	CEvent_UnitMove * move = rcast<CEvent_UnitMove *>(CGame->MakeEvent(kEvent_UnitMove));
	move->x = x;
	move->y = y;

	/*std::vector<CUnit *>::iterator it = CGame->RequestState()->map->mUnitList.begin();
	for(; it != CGame->RequestState()->map->mUnitList.end(); ++it)
	{
		for(int i = 0; i < unitIDs.size(); ++i)
		{
			int ident1 = (*it)->Ident();
			int unitident1 = unitIDs[i];

			if((*it)->Ident() == unitIDs[i])
				move->units.push_back((*it));
		}
	}*/

	for(int i = 0; i < unitIDs.size(); ++i)
		std::cout << "Moving Unit: " << (unitIDs[i]) << ", Name: " << CGame->RequestState()->map->Unit(unitIDs[i])->Name() << std::endl;
	std::cout << "===============================" << std::endl;

	for(int i = 0; i < unitIDs.size(); ++i)
		move->units.push_back(CGame->RequestState()->map->Unit(unitIDs[i]));

	CGame->RequestState()->RequiresMoveValidation = false;
	CGame->PostEvent(move);
}

/*! 
	@brief		CPacket_MoveResponse serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_MoveResponse::Serialize()
{
	// The size field must be two bytes
	assert(2 == sizeof(short));
	
	stream << (short)0 << mType;
	stream << x;
	stream << y;
	stream << (int)moveOk;
	stream << unitIDs.size();
	
	for(int i = 0; i < unitIDs.size(); ++i)
		stream << unitIDs[i];

	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());
	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveResponse DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_MoveResponse::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	stream.raw_set(rawData, len);
	short temp;
	stream >> temp;
	stream >> mType;
	stream >> x;
	stream >> y;
	int result;
	stream >> result;

	moveOk = (bool)result;
	
	int size;
	stream >> size;

	for(int i = 0; i < size; ++i)
	{
		int num;
		stream >> num;
		unitIDs.push_back(num);
	}
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_MoveResponse::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_MoveResponse constructor
*/
CPacket_MoveResponse::CPacket_MoveResponse(void) : CPacket(kPacket_MoveResponse)
{
	x = 0;
	y = 0;
	mType = kPacket_MoveResponse;
	moveOk = false;
}

/*!
	@brief		Destructor
*/
CPacket_MoveResponse::~CPacket_MoveResponse(void)
{
}