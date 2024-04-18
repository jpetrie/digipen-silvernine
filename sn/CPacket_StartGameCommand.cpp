/*! =========================================================================
      
      @file    CPacket_StartGameCommand.cpp
      @author  plaukait
      @brief   StartGameCommand Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_StartGameCommand.h"
#include "CPacketFactory_StartGameCommand.h"
#include "CEvent_ArmyBegin.h"
#include "CEventFactory_ArmyBegin.h"
#include "CEvent_StartSP.h"
#include "CEvent_LevelBegin.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_StartGameCommand::Handle(void * GameState, void * Socket)
{
	CGame->RequestState()->okToStartNetGame = (bool)startNetGame;

	// Start the level
	CEvent_LevelBegin * lvl = rcast<CEvent_LevelBegin *>(CGame->MakeEvent(kEvent_LevelBegin));
	CGame->PostEvent(lvl);
}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_StartGameCommand::Serialize()
{
	// The size field must be two bytes
	assert(2 == sizeof(short));
	
	stream << (short)0 << mType;
	stream << response;
	stream << startNetGame;
	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());
	
	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveRequest DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_StartGameCommand::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	short temp;
	stream.raw_set(rawData, len);
	stream >> temp;
	stream >> mType;
	stream >> response;
	stream >> startNetGame;
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_StartGameCommand::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_StartGameCommand constructor
*/
CPacket_StartGameCommand::CPacket_StartGameCommand(void) : CPacket( kPacket_StartGameCommand )
{
	mType = kPacket_StartGameCommand;
}

/*!
	@brief		Destructor
*/
CPacket_StartGameCommand::~CPacket_StartGameCommand(void)
{
}