/*! =========================================================================
      
      @file    CPacketFactory_SEED_RANDOM_NUMBER.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the SEED_RANDOM_NUMBER Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_Seed_Random_Number.h"
#include "CPacket_Seed_Random_Number.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_Seed_Random_Number CPacketFactory_Seed_Random_Number::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_Seed_Random_Number::Construct(void)
{
	return new CPacket_Seed_Random_Number;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_Seed_Random_Number::CPacketFactory_Seed_Random_Number(void) : CPacketFactory( kPacket_Seed_Random_Number )
{
}


/*  _________________________________________________________________________ */
