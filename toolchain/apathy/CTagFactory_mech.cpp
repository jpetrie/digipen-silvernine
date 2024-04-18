/*! =========================================================================
      
      @file    CTagFactory_mech.cpp
      @author  jmccrory
      @brief   'mech' tag factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CTagFactory_mech.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CTagFactory_mech  CTagFactory_mech::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
void CTagFactory_mech::DoUnarchive(CTag *tag,NLBytestream &bytes)
/*! @brief Unarchives a tag from a stream of bytes.

    @param tag    Pointer to the tag to unarchive into.
    @param bytes  The bytestream containing the tag data.
*/
{
CTag_mech* tTag = dcast< CTag_mech* >(tag);
  
  if(0 != tTag)
  {
    // Pull the tag data from the stream.
    bytes >> tTag->objeTag >> tTag->imgcTag >> tTag->idleSeqncIndx;
  }
}


/*  _________________________________________________________________________ */
void CTagFactory_mech::DoArchive(CTag *tag,NLBytestream &bytes)
/*! @brief Archives a tag to a stream of bytes.

    @param tag    Pointer to the tag to archive from.
    @param bytes  The bytestream to contain the tag data.
*/
{
CTag_mech* tTag = dcast< CTag_mech* >(tag);
  
  if(0 != tTag)
  {
    // Push the tag data into the stream.
	bytes << tTag->objeTag << tTag->imgcTag << tTag->idleSeqncIndx;
  }
}
 