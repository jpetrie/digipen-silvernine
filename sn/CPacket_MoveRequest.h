/*! =========================================================================
      
      @file    CPacket_MoveRequest.h
      @author  YOUR NAME HERE
      @brief   Interface to the MoveRequest Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_MoveRequest_H_
#define _C_PACKET_MoveRequest_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"
#include "CUnit.h"

static const int kPacket_MoveRequest = nlFOURCODE( 'm', 'v', 'r', 'q' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_MoveRequest : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_MoveRequest(void);
	~CPacket_MoveRequest(void);

	nsl::bstream stream;
	float x, y;
	std::vector<CUnit *>	units;
	std::vector<int>	unitsToMove;
	int mType;

private:
};


#endif  /* _C_PACKET_MoveRequest_H_ */
