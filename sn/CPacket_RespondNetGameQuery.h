/*! =========================================================================
      
      @file    CPacket_RespondNetGameQuery.h
      @author  plaukait
      @brief   Interface to the RespondNetGameQuery Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_RespondNetGameQuery_H_
#define _C_PACKET_RespondNetGameQuery_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"

static const int kPacket_RespondNetGameQuery = nlFOURCODE( 'r', 'n', 'g', 'q' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_RespondNetGameQuery : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_RespondNetGameQuery(void);
	~CPacket_RespondNetGameQuery(void);

	nsl::bstream stream;

	std::string serverName;		   // Name of the server sent in response to net game requests
	std::string gameName;		   // Name of the game currently being run on the server
	std::string serverAddress;	   // Address of the server
	int clientID;				   // ID of the client who send the query packet

private:
	int mType;
};


#endif  /* _C_PACKET_RespondNetGameQuery_H_ */
