/*! =========================================================================
      
      @file    CPacket_JoinResponse.h
      @author  plaukait
      @brief   Interface to the JoinResponse Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_JOINRESPONSE_H_
#define _C_PACKET_JOINRESPONSE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"

static const int kPacket_JoinResponse = nlFOURCODE( 'j', 'n', 'r', 'p' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_JoinResponse : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_JoinResponse(void);
	~CPacket_JoinResponse(void);

	nsl::bstream stream;
	char response;

private:
	int mType;
};


#endif  /* _C_PACKET_JOINRESPONSE_H_ */
