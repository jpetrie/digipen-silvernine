/*! =========================================================================
      
      @file    CPacketFactory.h
      @author  plaukait
      @brief   Interface to packet factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_PACKETFACTORY_H_
#define _C_PACKETFACTORY_H_


/*                                                                   includes
----------------------------------------------------------------------------- */
#include "precompiled.h"
#include "NSL.h"

#include "CPacket.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CPacketFactory
/*! @brief Packet factory class.

    Packet factories allow for the construction of CPacket objects. Every
    subclass of CPacket should have a corrisponding subclass of CPacketFactory
    that implements the protected Construct() method to create a new event of
    the appropriate type.
    
    Events can be constructed in a general fashion by using the static
    ConstructEvent() method of CPacketFactory, which takes an event ID and
    returns a pointer to the appropriate type of packet.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CPacketFactory);

  public:
    // ct and dt
             CPacketFactory(CPacket::ID id);
    virtual ~CPacketFactory(void);
    
    // generic construction
    static CPacket* ConstructPacket(CPacket::ID id);
  
  
  protected:
    // specific construction
    virtual CPacket* Construct(void) = 0;
    
    
  private:
     // data members
     static std::map< CPacket::ID,CPacketFactory* >  smFactories;
};


#endif  /* _C_PACKETFACTORY_H_ */
