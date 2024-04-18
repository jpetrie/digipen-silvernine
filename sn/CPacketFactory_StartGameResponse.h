/*! =========================================================================
      
      @file    CPacketFactory_StartGameResponse.h
      @author  YOUR NAME HERE
      @brief   Interface to the StartGameResponse Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_STARTGAMERESPONSE_H_
#define _C_PACKETFACTORY_STARTGAMERESPONSE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_StartGameResponse : public CPacketFactory
/*! @brief	Packet factory class for StartGameResponse Packets.

    @par	Creates a StartGameResponse Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_StartGameResponse);

  public:
	  CPacketFactory_StartGameResponse(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_StartGameResponse registrar;
};


#endif  /* _C_PACKETFACTORY_STARTGAMERESPONSE_H_ */
