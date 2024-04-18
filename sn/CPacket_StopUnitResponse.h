/*! =========================================================================
      
      @file    CPacket_StopUnitResponse.h
      @author  YOUR NAME HERE
      @brief   Interface to the StopUnitResponse Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_StopUnitResponse_H_
#define _C_PACKET_StopUnitResponse_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"
#include "CUnit.h"

static const int kPacket_StopUnitResponse = nlFOURCODE( 's', 't', 'r', 'p' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_StopUnitResponse : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_StopUnitResponse(void);
	~CPacket_StopUnitResponse(void);

	nsl::bstream stream;
	std::vector<int> unitIDs;
	std::vector<CUnit *> units;
	int mType;

private:
};


#endif  /* _C_PACKET_StopUnitResponse_H_ */
