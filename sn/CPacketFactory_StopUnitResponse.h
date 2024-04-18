/*! =========================================================================
      
      @file    CPacketFactory_StopUnitResponse.h
      @author  YOUR NAME HERE
      @brief   Interface to the StopUnitResponse Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_StopUnitResponse_H_
#define _C_PACKETFACTORY_StopUnitResponse_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_StopUnitResponse : public CPacketFactory
/*! @brief	Packet factory class for StopUnitResponse Packets.

    @par	Creates a StopUnitResponse Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_StopUnitResponse);

  public:
	  CPacketFactory_StopUnitResponse(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_StopUnitResponse registrar;
};


#endif  /* _C_PACKETFACTORY_StopUnitResponse_H_ */
