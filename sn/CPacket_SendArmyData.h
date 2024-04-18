/*! =========================================================================
      
      @file    CPacket_SendArmyData.h
      @author  YOUR NAME HERE
      @brief   Interface to the SendArmyData Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_SendArmyData_H_
#define _C_PACKET_SendArmyData_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"

static const int kPacket_SendArmyData = nlFOURCODE( 's', 'a', 'r', 'd' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_SendArmyData : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_SendArmyData(void);
	~CPacket_SendArmyData(void);

	nsl::bstream stream;
	int mType;
	int playerID;

private:
};


#endif  /* _C_PACKET_SendArmyData_H_ */
