/*! =========================================================================
      
      @file    CTagFactory_unit.cpp
      @author  Patrick Laukaitis
      @brief   'unit' tag factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CTagFactory_unit.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CTagFactory_unit  CTagFactory_unit::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
void CTagFactory_unit::DoUnarchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Unarchives a tag from a stream of bytes.

    @param tag    Pointer to the tag to unarchive into.
    @param bytes  The bytestream containing the tag data.
*/
{
CTag_unit* tTag = dcast< CTag_unit* >(tag);
  
  if(0 != tTag)
  {
    // Pull the tag data from the stream.
    bytes >> tTag->mech >> tTag->character >> tTag->script;
    bytes >> tTag->names >> tTag->flavor;
  }
}


void CTagFactory_unit::DoArchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Archives a tag to a stream of bytes.

    @param tag    Pointer to the tag to archive from.
    @param bytes  The bytestream to contain the tag data.
*/
{
CTag_unit* tTag = dcast< CTag_unit* >(tag);

  if(0 != tTag)
  {
    // Push the tag data into the stream.
    bytes << tTag->mech << tTag->character << tTag->script;
    bytes << tTag->names << tTag->flavor;
  }
}
