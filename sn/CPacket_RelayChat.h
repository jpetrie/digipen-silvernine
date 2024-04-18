/*! =========================================================================
      
      @file    CPacket_RelayChat.h
      @author  YOUR NAME HERE
      @brief   Interface to the RelayChat Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_RelayChat_H_
#define _C_PACKET_RelayChat_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"

static const int kPacket_RelayChat = nlFOURCODE( 'r', 'l', 'c', 't' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_RelayChat : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_RelayChat(void);
	~CPacket_RelayChat(void);

	nsl::bstream stream;
	int mType;
	std::string	message;

private:
};


#endif  /* _C_PACKET_RelayChat_H_ */
