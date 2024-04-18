/*! =========================================================================
      
      @file    CPacketFactory_StopUnit.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the StopUnit Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_StopUnit.h"
#include "CPacket_StopUnit.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_StopUnit CPacketFactory_StopUnit::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_StopUnit::Construct(void)
{
	return new CPacket_StopUnit;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_StopUnit::CPacketFactory_StopUnit(void) : CPacketFactory( kPacket_StopUnit )
{
}


/*  _________________________________________________________________________ */
