/*! =========================================================================
      
      @file    CPacketFactory_SendArmyData.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the SendArmyData Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_SendArmyData.h"
#include "CPacket_SendArmyData.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_SendArmyData CPacketFactory_SendArmyData::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_SendArmyData::Construct(void)
{
	return new CPacket_SendArmyData;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_SendArmyData::CPacketFactory_SendArmyData(void) : CPacketFactory( kPacket_SendArmyData )
{
}


/*  _________________________________________________________________________ */
