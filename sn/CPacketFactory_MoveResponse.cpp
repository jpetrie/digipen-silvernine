/*! =========================================================================
      
      @file    CPacketFactory_MoveResponse.cpp
      @author  plaukait
      @brief   Implementation of the Move Response Packet event factory class.
	  @date	   November 15, 2003
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_MoveResponse.h"
#include "CPacket_MoveResponse.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_MoveResponse CPacketFactory_MoveResponse::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_MoveResponse::Construct(void)
{
	return new CPacket_MoveResponse;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_MoveResponse::CPacketFactory_MoveResponse(void) : CPacketFactory(kPacket_MoveResponse)
{
}


/*  _________________________________________________________________________ */
