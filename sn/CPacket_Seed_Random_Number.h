/*! =========================================================================
      
      @file    CPacket_SEED_RANDOM_NUMBER.h
      @author  YOUR NAME HERE
      @brief   Interface to the SEED_RANDOM_NUMBER Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_SEED_RANDOM_NUMBER_H_
#define _C_PACKET_SEED_RANDOM_NUMBER_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"

#define SEED_VAL 100;		// Value used as the random seed for all clients
static const int kPacket_Seed_Random_Number = nlFOURCODE( 's', 'r', 'n', 'd' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_Seed_Random_Number : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_Seed_Random_Number(void);
	~CPacket_Seed_Random_Number(void);

	nsl::bstream stream;
	int seed;

private:
	int mType;
};


#endif  /* _C_PACKET_SEED_RANDOM_NUMBER_H_ */
