/*! =========================================================================
      
      @file    CPacketFactory_StartGameResponse.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the StartGameResponse Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_StartGameResponse.h"
#include "CPacket_StartGameResponse.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_StartGameResponse CPacketFactory_StartGameResponse::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_StartGameResponse::Construct(void)
{
	return new CPacket_StartGameResponse;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_StartGameResponse::CPacketFactory_StartGameResponse(void) : CPacketFactory( kPacket_StartGameResponse )
{
}


/*  _________________________________________________________________________ */
