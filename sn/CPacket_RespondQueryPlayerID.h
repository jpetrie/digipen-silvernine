/*! =========================================================================
      
      @file    CPacket_RespondQueryPlayerID.h
      @author  YOUR NAME HERE
      @brief   Interface to the RespondQueryPlayerID Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_RespondQueryPlayerID_H_
#define _C_PACKET_RespondQueryPlayerID_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"

static const int kPacket_RespondQueryPlayerID = nlFOURCODE( 'r', 'q', 'p', 'I' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_RespondQueryPlayerID : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_RespondQueryPlayerID(void);
	~CPacket_RespondQueryPlayerID(void);

	nsl::bstream stream;
	int yourID;

private:
	int mType;
};


#endif  /* kPacket_RespondQueryPlayerID_H_ */
