/*! =========================================================================
      
      @file    CPacketFactory_QueryForPlayerID.h
      @author  YOUR NAME HERE
      @brief   Interface to the QueryForPlayerID Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_QueryForPlayerID_H_
#define _C_PACKETFACTORY_QueryForPlayerID_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_QueryForPlayerID : public CPacketFactory
/*! @brief	Packet factory class for QueryForPlayerID Packets.

    @par	Creates a QueryForPlayerID Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_QueryForPlayerID);

  public:
	  CPacketFactory_QueryForPlayerID(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_QueryForPlayerID registrar;
};


#endif  /* _C_PACKETFACTORY_QueryForPlayerID_H_ */
