/*! =========================================================================
      
      @file    CPacket_TEMPLATE.h
      @author  YOUR NAME HERE
      @brief   Interface to the TEMPLATE Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_TEMPLATE_H_
#define _C_PACKET_TEMPLATE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"

static const int kPacket_TEMPLATE = nlFOURCODE( PACKET_CONSTANT_ID_HERE );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_TEMPLATE : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_TEMPLATE(void);
	~CPacket_TEMPLATE(void);

	nsl::bstream stream;

private:
	int mType;
};


#endif  /* _C_PACKET_TEMPLATE_H_ */
