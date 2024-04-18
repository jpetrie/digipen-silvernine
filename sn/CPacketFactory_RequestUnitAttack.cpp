/*! =========================================================================
      
      @file    CPacketFactory_RequestUnitAttack.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the RequestUnitAttack Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_RequestUnitAttack.h"
#include "CPacket_RequestUnitAttack.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_RequestUnitAttack CPacketFactory_RequestUnitAttack::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_RequestUnitAttack::Construct(void)
{
	return new CPacket_RequestUnitAttack;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_RequestUnitAttack::CPacketFactory_RequestUnitAttack(void) : CPacketFactory( kPacket_RequestUnitAttack )
{
}


/*  _________________________________________________________________________ */
