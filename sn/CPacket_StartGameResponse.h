/*! =========================================================================
      
      @file    CPacket_StartGameResponse.h
      @author  plaukait
      @brief   Interface to the StartGameResponse Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_STARTGAMERESPONSE_H_
#define _C_PACKET_STARTGAMERESPONSE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"

static const int kPacket_StartGameResponse = nlFOURCODE( 's', 't', 'g', 'c' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_StartGameResponse : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_StartGameResponse(void);
	~CPacket_StartGameResponse(void);

	nsl::bstream stream;
	
	int mType;
	char response;

private:
};


#endif  /* _C_PACKET_STARTGAMERESPONSE_H_ */
