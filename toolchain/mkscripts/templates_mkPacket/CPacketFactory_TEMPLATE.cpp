/*! =========================================================================
      
      @file    CPacketFactory_TEMPLATE.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the TEMPLATE Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_TEMPLATE.h"
#include "CPacket_TEMPLATE.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_TEMPLATE CPacketFactory_TEMPLATE::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_TEMPLATE::Construct(void)
{
	return new CPacket_TEMPLATE;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_TEMPLATE::CPacketFactory_TEMPLATE(void) : CPacketFactory( kPacket_TEMPLATE )
{
}


/*  _________________________________________________________________________ */
