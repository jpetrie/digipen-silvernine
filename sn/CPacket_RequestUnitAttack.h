/*! =========================================================================
      
      @file    CPacket_RequestUnitAttack.h
      @author  YOUR NAME HERE
      @brief   Interface to the RequestUnitAttack Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_RequestUnitAttack_H_
#define _C_PACKET_RequestUnitAttack_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"
#include "CUnit.h"

static const int kPacket_RequestUnitAttack = nlFOURCODE( 'r', 'q', 'u', 'a' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_RequestUnitAttack : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_RequestUnitAttack(void);
	~CPacket_RequestUnitAttack(void);

	nsl::bstream stream;

	bool                   ground;    // True if attack is ground (XY) based, false if unit based.
    float                  ground_x;  // X coordinate of ground attack.
    float                  ground_y;  // Y coordinate of ground attack.
    CUnit                 *target;    // Target of unit based attack.
    std::vector< CUnit* >  units;     // Units doing the attacking.

	std::vector<int>		unitsToAttack;	// The unit IDs of attacking units
	int						targetID;		// The ID of the target

private:
	int mType;
};


#endif  /* _C_PACKET_RequestUnitAttack_H_ */
