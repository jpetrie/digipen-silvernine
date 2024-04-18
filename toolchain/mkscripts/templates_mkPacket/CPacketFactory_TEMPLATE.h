/*! =========================================================================
      
      @file    CPacketFactory_TEMPLATE.h
      @author  YOUR NAME HERE
      @brief   Interface to the TEMPLATE Packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_TEMPLATE_H_
#define _C_PACKETFACTORY_TEMPLATE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"
#include "CPacketFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory_TEMPLATE : public CPacketFactory
/*! @brief	Packet factory class for TEMPLATE Packets.

    @par	Creates a TEMPLATE Packet using the factory design pattern.
  
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory_TEMPLATE);

  public:
	  CPacketFactory_TEMPLATE(void);
	  CPacket * Construct(void);
         
  private:
     // data members
     static CPacketFactory_TEMPLATE registrar;
};


#endif  /* _C_PACKETFACTORY_TEMPLATE_H_ */
