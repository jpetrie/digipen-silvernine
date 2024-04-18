/*! =========================================================================
      
      @file    CPacketFactory_QueryForNetGames.h
      @author  plaukait
      @brief   Interface to the QueryForNetGames Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_QueryForNetGames_H_
#define _C_PACKETFACTORY_QueryForNetGames_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_QueryForNetGames : public CPacketFactory
/*! @brief	Packet factory class for QueryForNetGames Packets.

    @par	Creates a QueryForNetGames Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_QueryForNetGames);

  public:
	  CPacketFactory_QueryForNetGames(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_QueryForNetGames registrar;
};


#endif  /* _C_PACKETFACTORY_QueryForNetGames_H_ */
