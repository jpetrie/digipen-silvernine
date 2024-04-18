/*! =========================================================================
      
      @file    CPacket_SendArmyData.cpp
      @author  YOUR NAME HERE
      @brief   SendArmyData Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_SendArmyData.h"
#include "CPacketFactory_SendArmyData.h"
#include "CArmy.h"
#include "CGameEngine.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_SendArmyData::Handle(void * GameState, void * Socket)
{
	// De-Serialization handles all of the necessary handling code
}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_SendArmyData::Serialize()
{
	// The size field must be two bytes
	assert(2 == sizeof(short));
	
	stream << (short)0 << mType;

	int player = -1;

	if(!(CGame->RequestServerState()->IAmServer))
		player = CGame->RequestState()->thisPlayer;
	else
		player = playerID;

	stream << player;

	// Serialize the Army's unit names
	std::vector<CArmy *>::iterator army = CGame->RequestState()->teams.begin();

	// Iterate to the proper 
	for(int i = 0; i < playerID; ++i)
		++army;

		//CGame->RequestState()->teams[CGame->RequestState()->thisTeam];
	int activeSize = (*army)->GetSizeofActive();
	int availableSize = (*army)->GetSizeofAvailable();

	stream << activeSize;
	stream << availableSize;

	for(int i = 0; i < activeSize; ++i)
	{
		stream << (*army)->GetActiveUnit(i)->Name();
		stream << (*army)->GetActiveUnit(i)->tagName;
	}

	for(int i = 0; i < availableSize; ++i)
	{
		stream << (*army)->GetUnit(i)->Name();
		stream << (*army)->GetUnit(i)->tagName;
	}
	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());
	
	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveRequest DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_SendArmyData::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	short temp;
	stream.raw_set(rawData, len);
	stream >> temp;
	stream >> mType;

	stream >> playerID;

	int activeSize;
	int availableSize;

	// DeSerialize the Army's unit names
	stream >> activeSize;
	stream >> availableSize;

	int size = CGame->RequestState()->teams.size();

	// Check that there is enough room in the teams list
	if(playerID >= CGame->RequestState()->teams.size())
	{
		CGame->RequestState()->teams.push_back(0);
		int numToAdd = playerID - size;
		for(int i = 0; i <= numToAdd; ++i)
			CGame->RequestState()->teams.push_back(0);
	}

	// Add a new army if one does not already exist
	if(playerID != CGame->RequestState()->thisPlayer)
        CGame->RequestState()->teams[playerID] = new CArmy;

	std::string unitName;
	std::string tagName;
	for(int i = 0; i < activeSize; ++i)
	{
		stream >> unitName;
		stream >> tagName;

		CUnit * newUnit = new CUnit(tagName, playerID, playerID);
		newUnit->SetName(unitName);
		CGame->RequestState()->teams[playerID]->AddActiveUnit(newUnit);
	}

	for(int i = 0; i < availableSize; ++i)
	{
		stream >> unitName;
		stream >> tagName;

		CUnit * newUnit = new CUnit(tagName, playerID, playerID);
		newUnit->SetName(unitName);
		CGame->RequestState()->teams[playerID]->AddUnit(newUnit);
	}
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_SendArmyData::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_SendArmyData constructor
*/
CPacket_SendArmyData::CPacket_SendArmyData(void) : CPacket( kPacket_SendArmyData )
{
	int playerID = 0;
	mType = kPacket_SendArmyData;
}

/*!
	@brief		Destructor
*/
CPacket_SendArmyData::~CPacket_SendArmyData(void)
{
}