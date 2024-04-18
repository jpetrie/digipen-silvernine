/*! =========================================================================
      
      @file    CPacket_MoveResponse.h
      @author  plaukait
      @brief   Interface to the Move Response Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_MOVERESPONSE_H_
#define _C_PACKET_MOVERESPONSE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "CSocket.h"

static const int kPacket_MoveResponse = nlFOURCODE('M', 'V', 'R', 'E');

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_MoveResponse : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_MoveResponse(void);
	~CPacket_MoveResponse(void);

	nsl::bstream stream;
	float x, y;
	std::vector<int> unitIDs;
	bool moveOk;
	int mType;
private:
};


#endif  /* _C_PACKET_MOVERESPONSE_H_ */
