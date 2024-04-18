/*! =========================================================================
      
      @file    CPacketFactory_RespondUnitAttack.h
      @author  YOUR NAME HERE
      @brief   Interface to the RespondUnitAttack Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_RespondUnitAttack_H_
#define _C_PACKETFACTORY_RespondUnitAttack_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_RespondUnitAttack : public CPacketFactory
/*! @brief	Packet factory class for RespondUnitAttack Packets.

    @par	Creates a RespondUnitAttack Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_RespondUnitAttack);

  public:
	  CPacketFactory_RespondUnitAttack(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_RespondUnitAttack registrar;
};


#endif  /* _C_PACKETFACTORY_RespondUnitAttack_H_ */
