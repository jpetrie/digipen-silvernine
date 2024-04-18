/*! =========================================================================
      
      @file    CPacketFactory_SendChat.h
      @author  YOUR NAME HERE
      @brief   Interface to the SendChat Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_SendChat_H_
#define _C_PACKETFACTORY_SendChat_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_SendChat : public CPacketFactory
/*! @brief	Packet factory class for SendChat Packets.

    @par	Creates a SendChat Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_SendChat);

  public:
	  CPacketFactory_SendChat(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_SendChat registrar;
};


#endif  /* _C_PACKETFACTORY_SendChat_H_ */
