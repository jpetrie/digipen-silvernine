/*! =========================================================================
      
      @file    CPacketFactory_JoinRequest.cpp
      @author  plaukait
      @brief   Implementation of the JoinRequest Packet event factory class.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_JoinRequest.h"
#include "CPacket_JoinRequest.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_JoinRequest CPacketFactory_JoinRequest::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_JoinRequest::Construct(void)
{
	return new CPacket_JoinRequest;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_JoinRequest::CPacketFactory_JoinRequest(void) : CPacketFactory( kPacket_JoinRequest )
{
}


/*  _________________________________________________________________________ */
