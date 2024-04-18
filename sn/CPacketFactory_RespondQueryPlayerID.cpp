/*! =========================================================================
      
      @file    CPacketFactory_RespondQueryPlayerID.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the RespondQueryPlayerID Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_RespondQueryPlayerID.h"
#include "CPacket_RespondQueryPlayerID.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_RespondQueryPlayerID CPacketFactory_RespondQueryPlayerID::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_RespondQueryPlayerID::Construct(void)
{
	return new CPacket_RespondQueryPlayerID;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_RespondQueryPlayerID::CPacketFactory_RespondQueryPlayerID(void) : CPacketFactory( kPacket_RespondQueryPlayerID )
{
}


/*  _________________________________________________________________________ */
