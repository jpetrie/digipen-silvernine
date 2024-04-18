/*! =========================================================================
      
      @file    CPacketFactory_MoveRequest.h
      @author  YOUR NAME HERE
      @brief   Interface to the MoveRequest Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_MoveRequest_H_
#define _C_PACKETFACTORY_MoveRequest_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_MoveRequest : public CPacketFactory
/*! @brief	Packet factory class for MoveRequest Packets.

    @par	Creates a MoveRequest Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_MoveRequest);

  public:
	  CPacketFactory_MoveRequest(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_MoveRequest registrar;
};


#endif  /* _C_PACKETFACTORY_MoveRequest_H_ */
