/*! =========================================================================
      
      @file    CPacketFactory_SendChat.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the SendChat Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_SendChat.h"
#include "CPacket_SendChat.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_SendChat CPacketFactory_SendChat::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_SendChat::Construct(void)
{
	return new CPacket_SendChat;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_SendChat::CPacketFactory_SendChat(void) : CPacketFactory( kPacket_SendChat )
{
}


/*  _________________________________________________________________________ */
