/*! =========================================================================
      
      @file    CPacketFactory_RespondUnitAttack.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the RespondUnitAttack Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_RespondUnitAttack.h"
#include "CPacket_RespondUnitAttack.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_RespondUnitAttack CPacketFactory_RespondUnitAttack::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_RespondUnitAttack::Construct(void)
{
	return new CPacket_RespondUnitAttack;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_RespondUnitAttack::CPacketFactory_RespondUnitAttack(void) : CPacketFactory( kPacket_RespondUnitAttack )
{
}


/*  _________________________________________________________________________ */
