/*! =========================================================================
      
      @file    CPacketFactory.cpp
      @author  plaukait
      @brief   Implementation of packet factory base class.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CPacketFactory.h"


/*                                                             static members
----------------------------------------------------------------------------- */

std::map< CPacket::ID,CPacketFactory* >  CPacketFactory::smFactories;


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CPacketFactory::CPacketFactory(CPacket::ID id)
/*! @brief Constructor.

    @param id  The ID of the packet types this factory constructs.
*/
{
  smFactories.insert(std::make_pair(id,this));
}


/*  _________________________________________________________________________ */
CPacketFactory::~CPacketFactory(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CPacket* CPacketFactory::ConstructPacket(CPacket::ID id)
/*! @brief Constructs a new packet of the specified type.

    @param id  The ID of the packet type to construct.
    
    @return
    A pointer to the new packet.
*/
{
CPacketFactory *tFactory = (*smFactories.find(id)).second;

  if(0 == tFactory)
    return (0);//TODO: throw an exception
  else
    return (tFactory->Construct());
}