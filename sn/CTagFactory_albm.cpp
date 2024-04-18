/*! =========================================================================
      
      @file    CTagFactory_ablm.cpp
      @author  jpetrie
      @brief   'ablm' tag factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CTagFactory_ablm.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CTagFactory_ablm  CTagFactory_ablm::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
void CTagFactory_ablm::DoUnarchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Unarchives a tag from a stream of bytes.

    @param tag    Pointer to the tag to unarchive into.
    @param bytes  The bytestream containing the tag data.
*/
{
CTag_ablm* tTag = dcast< CTag_ablm* >(tag);
  
  if(0 != tTag)
  {
    // Pull the tag data from the stream.
    bytes >> tTag->collection >> tTag->groupEffect >> tTag->groupFired
          >> tTag->cashCost >> tTag->syncCost
          >> tTag->minDistance >> tTag->maxDistance
          >> tTag->delay;
  }
}


void CTagFactory_ablm::DoArchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Archives a tag to a stream of bytes.

    @param tag    Pointer to the tag to archive from.
    @param bytes  The bytestream to contain the tag data.
*/
{
CTag_ablm* tTag = dcast< CTag_ablm* >(tag);

  if(0 != tTag)
  {
    // Push the tag data into the stream.
    bytes << tTag->collection << tTag->groupEffect << tTag->groupFired
          << tTag->cashCost << tTag->syncCost
          << tTag->minDistance << tTag->maxDistance
          << tTag->delay;
  }
}
