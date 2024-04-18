/*! =========================================================================
      
      @file    CPacketFactory_QueryForNetGames.cpp
      @author  plaukait
      @brief   Implementation of the QueryForNetGames Packet event factory class.
	  @date	   January 28, 2004
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CPacketFactory_QueryForNetGames.h"
#include "CPacket_QueryForNetGames.h"


/*                                                             static members
----------------------------------------------------------------------------- */
CPacketFactory_QueryForNetGames CPacketFactory_QueryForNetGames::registrar;

/*                                                           function members
----------------------------------------------------------------------------- */

/*!
	@brief		Construction method for the Test Packet object
*/
CPacket * CPacketFactory_QueryForNetGames::Construct(void)
{
	return new CPacket_QueryForNetGames;
}

/*!
	@brief		Constructor -> provides registration capability
*/
CPacketFactory_QueryForNetGames::CPacketFactory_QueryForNetGames(void) : CPacketFactory( kPacket_QueryForNetGames )
{
}


/*  _________________________________________________________________________ */
