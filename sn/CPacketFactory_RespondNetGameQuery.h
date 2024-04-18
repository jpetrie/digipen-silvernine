/*! =========================================================================
      
      @file    CPacketFactory_RespondNetGameQuery.h
      @author  YOUR NAME HERE
      @brief   Interface to the RespondNetGameQuery Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_RespondNetGameQuery_H_
#define _C_PACKETFACTORY_RespondNetGameQuery_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_RespondNetGameQuery : public CPacketFactory
/*! @brief	Packet factory class for RespondNetGameQuery Packets.

    @par	Creates a RespondNetGameQuery Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_RespondNetGameQuery);

  public:
	  CPacketFactory_RespondNetGameQuery(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_RespondNetGameQuery registrar;
};


#endif  /* _C_PACKETFACTORY_RespondNetGameQuery_H_ */
