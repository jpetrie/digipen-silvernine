/*! =========================================================================
      
      @file    CPacketFactory_SendArmyData.h
      @author  YOUR NAME HERE
      @brief   Interface to the SendArmyData Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_SendArmyData_H_
#define _C_PACKETFACTORY_SendArmyData_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_SendArmyData : public CPacketFactory
/*! @brief	Packet factory class for SendArmyData Packets.

    @par	Creates a SendArmyData Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_SendArmyData);

  public:
	  CPacketFactory_SendArmyData(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_SendArmyData registrar;
};


#endif  /* _C_PACKETFACTORY_SendArmyData_H_ */
