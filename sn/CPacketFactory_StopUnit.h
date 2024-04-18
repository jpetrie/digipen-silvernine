/*! =========================================================================
      
      @file    CPacketFactory_StopUnit.h
      @author  YOUR NAME HERE
      @brief   Interface to the StopUnit Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_StopUnit_H_
#define _C_PACKETFACTORY_StopUnit_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_StopUnit : public CPacketFactory
/*! @brief	Packet factory class for StopUnit Packets.

    @par	Creates a StopUnit Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_StopUnit);

  public:
	  CPacketFactory_StopUnit(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_StopUnit registrar;
};


#endif  /* _C_PACKETFACTORY_StopUnit_H_ */
