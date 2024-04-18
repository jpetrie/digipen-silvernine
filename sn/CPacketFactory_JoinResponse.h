/*! =========================================================================
      
      @file    CPacketFactory_JoinResponse.h
      @author  YOUR NAME HERE
      @brief   Interface to the JoinResponse Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_JOINRESPONSE_H_
#define _C_PACKETFACTORY_JOINRESPONSE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_JoinResponse : public CPacketFactory
/*! @brief	Packet factory class for JoinResponse Packets.

    @par	Creates a JoinResponse Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_JoinResponse);

  public:
	  CPacketFactory_JoinResponse(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_JoinResponse registrar;
};


#endif  /* _C_PACKETFACTORY_JoinResponse_H_ */
