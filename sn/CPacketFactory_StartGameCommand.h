/*! =========================================================================
      
      @file    CPacketFactory_StartGameCommand.h
      @author  YOUR NAME HERE
      @brief   Interface to the StartGameCommand Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_STARTGAMECOMMAND_H_
#define _C_PACKETFACTORY_STARTGAMECOMMAND_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_StartGameCommand : public CPacketFactory
/*! @brief	Packet factory class for StartGameCommand Packets.

    @par	Creates a StartGameCommand Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_StartGameCommand);

  public:
	  CPacketFactory_StartGameCommand(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_StartGameCommand registrar;
};


#endif  /* _C_PACKETFACTORY_STARTGAMECOMMAND_H_ */
