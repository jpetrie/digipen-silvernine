/*! =========================================================================
      
      @file    CPacket_StartGameCommand.h
      @author  plaukait
      @brief   Interface to the StartGameCommand Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_STARTGAMECOMMAND_H_
#define _C_PACKET_STARTGAMECOMMAND_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"

static const int kPacket_StartGameCommand = nlFOURCODE( 's', 't', 'g', 'c' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_StartGameCommand : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_StartGameCommand(void);
	~CPacket_StartGameCommand(void);

	nsl::bstream stream;

	int startNetGame;
	int mType;
	char response;

private:
};


#endif  /* _C_PACKET_STARTGAMECOMMAND_H_ */
