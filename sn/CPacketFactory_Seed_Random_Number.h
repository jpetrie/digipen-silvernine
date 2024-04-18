/*! =========================================================================
      
      @file    CPacketFactory_SEED_RANDOM_NUMBER.h
      @author  YOUR NAME HERE
      @brief   Interface to the SEED_RANDOM_NUMBER Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_SEED_RANDOM_NUMBER_H_
#define _C_PACKETFACTORY_SEED_RANDOM_NUMBER_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_Seed_Random_Number : public CPacketFactory
/*! @brief	Packet factory class for SEED_RANDOM_NUMBER Packets.

    @par	Creates a SEED_RANDOM_NUMBER Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_Seed_Random_Number);

  public:
	  CPacketFactory_Seed_Random_Number(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_Seed_Random_Number registrar;
};


#endif  /* _C_PACKETFACTORY_SEED_RANDOM_NUMBER_H_ */
