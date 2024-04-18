/*! =========================================================================
      
      @file    CPacketFactory_MoveRequest.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the MoveRequest Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_MoveRequest.h"
#include "CPacket_MoveRequest.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_MoveRequest CPacketFactory_MoveRequest::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_MoveRequest::Construct(void)
{
	return new CPacket_MoveRequest;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_MoveRequest::CPacketFactory_MoveRequest(void) : CPacketFactory( kPacket_MoveRequest )
{
}


/*  _________________________________________________________________________ */
