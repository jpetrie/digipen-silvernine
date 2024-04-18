/*! =========================================================================
      
      @file    CPacketFactory_JoinResponse.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the JoinResponse Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_JoinResponse.h"
#include "CPacket_JoinResponse.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_JoinResponse CPacketFactory_JoinResponse::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_JoinResponse::Construct(void)
{
	return new CPacket_JoinResponse;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_JoinResponse::CPacketFactory_JoinResponse(void) : CPacketFactory( kPacket_JoinResponse )
{
}


/*  _________________________________________________________________________ */
