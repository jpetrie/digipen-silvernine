/*! =========================================================================
      
      @file    CPacket_RespondUnitAttack.h
      @author  YOUR NAME HERE
      @brief   Interface to the RespondUnitAttack Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_RespondUnitAttack_H_
#define _C_PACKET_RespondUnitAttack_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"

static const int kPacket_RespondUnitAttack = nlFOURCODE( 'r', 's', 'u', 'a' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_RespondUnitAttack : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_RespondUnitAttack(void);
	~CPacket_RespondUnitAttack(void);

	nsl::bstream stream;

	bool                   ground;    // True if attack is ground (XY) based, false if unit based.
    float                  ground_x;  // X coordinate of ground attack.
    float                  ground_y;  // Y coordinate of ground attack.
    int					   targetID;    // Target of unit based attack.
    std::vector< int >	   unitsToDoAttack;     // Units doing the attacking.

private:
	int mType;
};


#endif  /* _C_PACKET_RespondUnitAttack_H_ */
