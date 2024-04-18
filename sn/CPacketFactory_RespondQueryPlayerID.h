/*! =========================================================================
      
      @file    CPacketFactory_RespondQueryPlayerID.h
      @author  YOUR NAME HERE
      @brief   Interface to the RespondQueryPlayerID Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_RespondQueryPlayerID_H_
#define _C_PACKETFACTORY_RespondQueryPlayerID_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_RespondQueryPlayerID : public CPacketFactory
/*! @brief	Packet factory class for RespondQueryPlayerID Packets.

    @par	Creates a RespondQueryPlayerID Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_RespondQueryPlayerID);

  public:
	  CPacketFactory_RespondQueryPlayerID(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_RespondQueryPlayerID registrar;
};


#endif  /* _C_PACKETFACTORY_RespondQueryPlayerID_H_ */
