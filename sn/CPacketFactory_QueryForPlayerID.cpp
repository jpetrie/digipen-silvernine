/*! =========================================================================
      
      @file    CPacketFactory_QueryForPlayerID.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the QueryForPlayerID Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_QueryForPlayerID.h"
#include "CPacket_QueryForPlayerID.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_QueryForPlayerID CPacketFactory_QueryForPlayerID::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_QueryForPlayerID::Construct(void)
{
	return new CPacket_QueryForPlayerID;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_QueryForPlayerID::CPacketFactory_QueryForPlayerID(void) : CPacketFactory( kPacket_QueryForPlayerID )
{
}


/*  _________________________________________________________________________ */
