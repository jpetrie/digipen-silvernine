/*! =========================================================================
      
      @file    CPacket_QueryForPlayerID.h
      @author  YOUR NAME HERE
      @brief   Interface to the QueryForPlayerID Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_QueryForPlayerID_H_
#define _C_PACKET_QueryForPlayerID_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"

static const int kPacket_QueryForPlayerID = nlFOURCODE( 'q', 'f', 'p', 'I' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_QueryForPlayerID : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_QueryForPlayerID(void);
	~CPacket_QueryForPlayerID(void);

	nsl::bstream stream;

private:
	int mType;
};


#endif  /* kPacket_QueryForPlayerID_H_ */
