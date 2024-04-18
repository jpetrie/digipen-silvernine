/*! =========================================================================
      
      @file    CPacket.h
      @author  plaukait
      @brief   Interface to packet base class.
  	@par	Modifications:
			January 15, 2004	--	plaukait	--	Ported to new SN libraries
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKET_H_
#define _C_PACKET_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "NSL.h"
#include "precompiled.h"
#include <cassert>

/*																	  defines
----------------------------------------------------------------------------- */
/*! Length of the size field in the packet's bytestream*/
#define PACKET_SIZE_FIELD_LEN 2		// 2 bytes
#define PACKET_TYPE_FIELD_LEN 4		// 4 bytes

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacket
/*! @brief Packet base class.

    A packet is a collection of data that is intended to be sent over the network. 
	A CPacket subclass contains the data to send, along with methods to serialize
	the data into a bytestream.  Data fields for packet size and packet type, 
	are also required.  See the packet format for a description of the required sizes.
    
	The packet is transmitted by passing it to the CSocket send() method.
	Prior to passing the packet, however, the socket must be connected() to 
	a remote host.
     
    Arguments cannot be passed to the constructors of CPacket subclasses; the
    preferred means of sending data with a packet is to store the data in
    public member fields.

	@par	Suggested Packet Format:
			
			| PACKET SIZE - 2 BYTES | PACKET TYPE - 4 BYTES | PAYLOAD - X BYTES |

			Note that the packet size is the size of the entire packet, including the size
			and type fields.

			Note that the maximum payload size is not a standard.  Implementations may 
			restrict the size, so please keep it to a reasonalbe number (under 8,000 bytes)
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacket);
  
  public:
    // typedefs
    typedef unsigned long ID;
  
    // ct and dt
             CPacket(ID id);
    virtual ~CPacket(void);
    
    // accessors
    ID Ident(void) const;

	// Marshal the size (0) and the type into the provided bytestream
	// Should be invoked by every base class before sending
	void MarshalData(nsl::bstream & stream, unsigned int type);
    
	// Serialization to a bytestream
	virtual nsl::byte_t * Serialize() = 0;

	// Re-Construct the packet from a bytestream
	virtual void DeSerialize(const nsl::byte_t * rawData, unsigned int len) = 0;

	// Returns the size of the data currently in stream (in bytes)
	virtual unsigned int Size() = 0;

	// Handles the necessary server-side processing on the packet (just like events)
	virtual void Handle(void * GameState, void * Socket) = 0;

  private:
    const ID  mID;  
};


#endif  /* _C_PACKET_H_ */
