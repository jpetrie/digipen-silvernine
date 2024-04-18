/*! =========================================================================
      
      @file    CPacket_StopUnitResponse.cpp
      @author  YOUR NAME HERE
      @brief   StopUnitResponse Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_StopUnitResponse.h"
#include "CPacketFactory_StopUnitResponse.h"
#include "CEvent_UnitStop.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_StopUnitResponse::Handle(void * GameState, void * Socket)
{
	// Make an event to stop units
	CEvent_UnitStop * evnt = rcast<CEvent_UnitStop *>(NetworkManager->MakePacket(kEvent_UnitStop));

	std::vector<CUnit *>::iterator it = CGame->RequestState()->map->mUnitList.begin();
	for(; it != CGame->RequestState()->map->mUnitList.end(); ++it)
	{
		for(int i = 0; i < unitIDs.size(); ++i)
		{
			int ident1 = (*it)->Ident();
			int unitident1 = unitIDs[i];

			if((*it)->Ident() == unitIDs[i])
				evnt->units.push_back((*it));
		}
	}

	// Set the validation flag
	CGame->RequestState()->RequireStopValidation = true;

	CGame->PostEvent(evnt);
}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_StopUnitResponse::Serialize()
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
void CPacket_StopUnitResponse::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
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
unsigned int CPacket_StopUnitResponse::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_StopUnitResponse constructor
*/
CPacket_StopUnitResponse::CPacket_StopUnitResponse(void) : CPacket( kPacket_StopUnitResponse )
{
	mType = kPacket_StopUnitResponse;
}

/*!
	@brief		Destructor
*/
CPacket_StopUnitResponse::~CPacket_StopUnitResponse(void)
{
}