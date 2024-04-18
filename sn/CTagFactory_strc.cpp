/*! =========================================================================
      
      @file    CTagFactory_strc.cpp
      @brief   'strc' tag factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory_strc.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CTagFactory_strc  CTagFactory_strc::smRegistrar;


/*                                                           member functions
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
void CTagFactory_strc::DoUnarchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Unarchives a tag from a stream of bytes.

    @param tag    Pointer to the tag to unarchive into.
    @param bytes  The bytestream containing the tag data.
*/
{
CTag_strc* tTag = dcast< CTag_strc* >(tag);
  
  if(0 != tTag)
  {
    bytes >> tTag->stringCnt;
    for(unsigned int i = 0; i < tTag->stringCnt; ++i)
    {
    std::string  tStr;
    
      bytes >> tStr;
      tTag->strings.push_back(tStr);
    }
  }
}


/*  _________________________________________________________________________ */
void CTagFactory_strc::DoArchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Archives a tag to a stream of bytes.

    @param tag    Pointer to the tag to archive from.
    @param bytes  The bytestream to contain the tag data.
*/
{
CTag_strc* tTag = dcast< CTag_strc* >(tag);
  
  if(0 != tTag)
  {
    bytes << tTag->stringCnt;
    for(unsigned int i = 0; i < tTag->stringCnt; ++i)
    {
      bytes << tTag->strings[i];
    }
  }
}
