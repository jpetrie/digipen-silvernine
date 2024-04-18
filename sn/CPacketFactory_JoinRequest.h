/*! =========================================================================
      
      @file    CPacketFactory_JoinRequest.h
      @author  plaukait
      @brief   Interface to the JoinRequest Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_JOINREQUEST_H_
#define _C_PACKETFACTORY_JOINREQUEST_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_JoinRequest : public CPacketFactory
/*! @brief	Packet factory class for JoinRequest Packets.

    @par	Creates a JoinRequest Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_JoinRequest);

  public:
	  CPacketFactory_JoinRequest(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_JoinRequest registrar;
};


#endif  /* _C_PACKETFACTORY_JOINREQUEST_H_ */
