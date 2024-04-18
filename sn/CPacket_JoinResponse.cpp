/*! =========================================================================
      
      @file    CPacket_JoinResponse.cpp
      @author  plaukait
      @brief   JoinResponse Packet implementation
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket_JoinResponse.h"
#include "CPacketFactory_JoinResponse.h"
#include "CPacket_StartGameCommand.h"
#include "CPacketFactory_StartGameCommand.h"
#include "CEvent_ArmyBegin.h"
#include "CEvent_LevelBegin.h"
#include "CEvent_StartSP.h"

/*                                                           member functions
----------------------------------------------------------------------------- */


/*!
	@brief		Does server-side processing on the packet
	@par		All necessary information should be in the GameState
*/
void CPacket_JoinResponse::Handle(void * GameState, void * Socket)
{
	// Add the ID of the client to the list for future processing
	// For now, just send a start game packet -- change this later!!! FIXEME

	if(response)
	{
		CPacket * pPacket = (CNetworkMgrS::instance())->MakePacket(kPacket_StartGameCommand);
		CSocket * pSocket = (CSocket *)Socket;
		pSocket->Send(*pPacket);

		CEvent * pStartLevel = (CGameEngine::instance())->MakeEvent(kEvent_StartSP);
		(CGameEngine::instance())->PostEvent(pStartLevel);
		CEvent * pStartArmy = (CGameEngine::instance())->MakeEvent(kEvent_ArmyBegin);
		(CGameEngine::instance())->PostEvent(pStartArmy);
	}
}

/*! 
	@brief		CPacket_MoveRequest serialization function
	@par		Converts internal data to a bytestream
*/
nsl::byte_t * CPacket_JoinResponse::Serialize()
{
	// The size field must be two bytes
	assert(2 == sizeof(short));
	
	stream << (short)0 << mType;
	stream << response;
	(*(reinterpret_cast<short *>(stream.raw_get()))) = htons(Size());
	return stream.raw_get();
}

/*!
	@brief		CPacket_MoveRequest DeSerialization function
	@par		Extracts data from a bytestream
*/
void CPacket_JoinResponse::DeSerialize(const nsl::byte_t * rawData, unsigned int len)
{
	stream.raw_set(rawData, len);
	short temp;
	stream >> temp;
	stream >> mType;
	stream >> response;
}

/*!
	@brief		Returns the size of the data currently in stream in bytes
*/
unsigned int CPacket_JoinResponse::Size()
{
	return stream.size();
}

/*!
	@brief	CPacket_JoinResponse constructor
*/
CPacket_JoinResponse::CPacket_JoinResponse(void) : CPacket( kPacket_JoinResponse )
{
	mType = kPacket_JoinResponse;
	response = false;
}

/*!
	@brief		Destructor
*/
CPacket_JoinResponse::~CPacket_JoinResponse(void)
{
}