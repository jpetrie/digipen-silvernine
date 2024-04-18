/*! =========================================================================
      
      @file    CPacket_QueryForNetGames.h
      @author  plaukait
      @brief   Interface to the QueryForNetGames Packet base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_QueryForNetGames_H_
#define _C_PACKET_QueryForNetGames_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CPacket.h"
#include "nsl_bstream.h"
#include "CSocket.h"

static const int kPacket_QueryForNetGames = nlFOURCODE( 'q', 'n', 't', 'g' );

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket_QueryForNetGames : public CPacket
{
public: 
	nsl::byte_t * Serialize();
	void DeSerialize(const nsl::byte_t * rawData, unsigned int len);
	unsigned int Size();
	void Handle(void * GameState, void * Socket);
	CPacket_QueryForNetGames(void);
	~CPacket_QueryForNetGames(void);

	nsl::bstream stream;
	
	int clientID;
	std::string clientAddress;
	int clientPort;

private:
	int mType;
};


#endif  /* _C_PACKET_QueryForNetGames_H_ */
