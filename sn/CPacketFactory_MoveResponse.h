/*! =========================================================================
      
      @file    CPacketFactory_MoveResponse.h
      @author  plaukait
      @brief   Interface to the Move Response Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_MOVERESPONSE_H_
#define _C_PACKETFACTORY_MOVERESPONSE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_MoveResponse : public CPacketFactory
/*! @brief	Packet factory class for Move Response Packets.

    @par	Creates a Move Response Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_MoveResponse);

  public:
	  CPacketFactory_MoveResponse(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_MoveResponse registrar;
};


#endif  /* _C_PACKETFACTORY_MOVERESPONSE_H_ */
