/*! =========================================================================
      
      @file    CPacket_StopUnit.h
      @author  YOUR NAME HERE
      @brief   Interface to the StopUnit Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_StopUnit_H_
#define _C_PACKET_StopUnit_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"
#include "CUnit.h"

static const int kPacket_StopUnit = nlFOURCODE( 's', 't', 'u', 'n' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_StopUnit : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_StopUnit(void);
	~CPacket_StopUnit(void);

	nsl::bstream stream;

	std::vector<CUnit *> units;
	std::vector<int> unitIDs;
	int mType;

private:
};


#endif  /* _C_PACKET_StopUnit_H_ */
