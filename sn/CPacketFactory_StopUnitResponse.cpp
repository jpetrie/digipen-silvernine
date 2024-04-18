/*! =========================================================================
      
      @file    CPacketFactory_StopUnitResponse.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the StopUnitResponse Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_StopUnitResponse.h"
#include "CPacket_StopUnitResponse.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_StopUnitResponse CPacketFactory_StopUnitResponse::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_StopUnitResponse::Construct(void)
{
	return new CPacket_StopUnitResponse;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_StopUnitResponse::CPacketFactory_StopUnitResponse(void) : CPacketFactory( kPacket_StopUnitResponse )
{
}


/*  _________________________________________________________________________ */
