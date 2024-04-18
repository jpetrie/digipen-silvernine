/*! =========================================================================
      
      @file    CTagFactory_scri.cpp
      @brief   'scri' tag factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory_scri.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CTagFactory_scri  CTagFactory_scri::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
void CTagFactory_scri::DoUnarchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Unarchives a tag from a stream of bytes.

    @param tag    Pointer to the tag to unarchive into.
    @param bytes  The bytestream containing the tag data.
*/
{
CTag_scri* tTag = dcast< CTag_scri* >(tag);
  
  if(0 != tTag)
  {
    // Pull uncompiled script.
    bytes >> tTag->uncompiled;
  }
}


/*  _________________________________________________________________________ */
void CTagFactory_scri::DoArchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Archives a tag to a stream of bytes.

    @param tag    Pointer to the tag to archive from.
    @param bytes  The bytestream to contain the tag data.
*/
{
CTag_scri* tTag = dcast< CTag_scri* >(tag);
  
  if(0 != tTag)
  { 
    // Push the uncompiled script.
    bytes << tTag->uncompiled;
  }
}
