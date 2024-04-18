/*! =========================================================================
      
      @file    CPacketFactory_StartGameCommand.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the StartGameCommand Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_StartGameCommand.h"
#include "CPacket_StartGameCommand.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_StartGameCommand CPacketFactory_StartGameCommand::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_StartGameCommand::Construct(void)
{
	return new CPacket_StartGameCommand;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_StartGameCommand::CPacketFactory_StartGameCommand(void) : CPacketFactory( kPacket_StartGameCommand )
{
}


/*  _________________________________________________________________________ */
