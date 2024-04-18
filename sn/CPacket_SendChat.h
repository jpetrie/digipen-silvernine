/*! =========================================================================
      
      @file    CPacket_SendChat.h
      @author  YOUR NAME HERE
      @brief   Interface to the SendChat Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_SendChat_H_
#define _C_PACKET_SendChat_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"

static const int kPacket_SendChat = nlFOURCODE( 's', 'n', 'c', 't' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_SendChat : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_SendChat(void);
	~CPacket_SendChat(void);

	nsl::bstream stream;
	int mType;
	std::string message;

private:
};


#endif  /* _C_PACKET_SendChat_H_ */
