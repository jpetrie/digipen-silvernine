/*! =========================================================================
      
      @file    CPacketFactory_RespondNetGameQuery.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the RespondNetGameQuery Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_RespondNetGameQuery.h"
#include "CPacket_RespondNetGameQuery.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_RespondNetGameQuery CPacketFactory_RespondNetGameQuery::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_RespondNetGameQuery::Construct(void)
{
	return new CPacket_RespondNetGameQuery;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_RespondNetGameQuery::CPacketFactory_RespondNetGameQuery(void) : CPacketFactory( kPacket_RespondNetGameQuery )
{
}


/*  _________________________________________________________________________ */
