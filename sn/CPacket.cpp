/*! =========================================================================
      
      @file    CPacket.cpp
      @author  plaukait
      @brief   Implementation of packet base class.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CPacket.h"


/*                                                           member functions
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CPacket::CPacket(CPacket::ID id)
/*! @brief Constructor.

    @param id  The type of packet to construct.
*/
: mID(id)
{
}


/*  _________________________________________________________________________ */
CPacket::~CPacket(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CPacket::ID CPacket::Ident(void) const
/*! @brief Returns the ID of the packet.

    @return
    The type of the packet.
*/
{
  return (mID);
}

/*  _________________________________________________________________________ */
/*!
	@brief  Inserts the size (short 0) and the type into the bytestream
	@par	Derived packets should call this (and modify the size afterward)
*/
void CPacket::MarshalData(nsl::bstream & stream, unsigned int type)
{
	stream << scast<unsigned short>(0) << type;
}