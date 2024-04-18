/*! =========================================================================
      
      @file    CPacket_JoinRequest.h
      @author  plaukait
      @brief   Interface to the JoinRequest Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_JOINREQUEST_H_
#define _C_PACKET_JOINREQUEST_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"

static const int kPacket_JoinRequest = nlFOURCODE('j', 'n', 'r', 'q');

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_JoinRequest : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_JoinRequest(void);
	~CPacket_JoinRequest(void);

	nsl::bstream stream;

private:
	int mType;
};


#endif  /* _C_PACKET_JOINREQUEST_H_ */
