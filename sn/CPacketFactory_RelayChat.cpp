/*! =========================================================================
      
      @file    CPacketFactory_RelayChat.cpp
      @author  YOUR NAME HERE
      @brief   Implementation of the RelayChat Packet event factory class.
	  @date	   CURRENT DATE HERE
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_RelayChat.h"
#include "CPacket_RelayChat.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_RelayChat CPacketFactory_RelayChat::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_RelayChat::Construct(void)
{
	return new CPacket_RelayChat;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_RelayChat::CPacketFactory_RelayChat(void) : CPacketFactory( kPacket_RelayChat )
{
}


/*  _________________________________________________________________________ */
