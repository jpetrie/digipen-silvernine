/*! =========================================================================
      
      @file    CPacketFactory_RequestUnitAttack.h
      @author  YOUR NAME HERE
      @brief   Interface to the RequestUnitAttack Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_RequestUnitAttack_H_
#define _C_PACKETFACTORY_RequestUnitAttack_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_RequestUnitAttack : public CPacketFactory
/*! @brief	Packet factory class for RequestUnitAttack Packets.

    @par	Creates a RequestUnitAttack Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_RequestUnitAttack);

  public:
	  CPacketFactory_RequestUnitAttack(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_RequestUnitAttack registrar;
};


#endif  /* _C_PACKETFACTORY_RequestUnitAttack_H_ */
