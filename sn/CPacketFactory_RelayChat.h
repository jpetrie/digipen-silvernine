/*! =========================================================================
      
      @file    CPacketFactory_RelayChat.h
      @author  YOUR NAME HERE
      @brief   Interface to the RelayChat Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_RelayChat_H_
#define _C_PACKETFACTORY_RelayChat_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_RelayChat : public CPacketFactory
/*! @brief	Packet factory class for RelayChat Packets.

    @par	Creates a RelayChat Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_RelayChat);

  public:
	  CPacketFactory_RelayChat(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_RelayChat registrar;
};


#endif  /* _C_PACKETFACTORY_RelayChat_H_ */
