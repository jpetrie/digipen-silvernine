/*! =========================================================================
      
      @file    CTagFactory_save.cpp
      @brief   'save' tag factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory_save.h"

#include "CTag_army.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CTagFactory_save  CTagFactory_save::smRegistrar;


/*                                                           member functions
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
void CTagFactory_save::DoUnarchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Unarchives a tag from a stream of bytes.

    @param tag    Pointer to the tag to unarchive into.
    @param bytes  The bytestream containing the tag data.
*/
{
CTag_save* tTag = dcast< CTag_save* >(tag);
  
  if(0 != tTag)
  {
    bytes >> tTag->teamCnt;
    std::cout << "\tSave has: " << (int)tTag->teamCnt << " team(s).\n";
    for(unsigned int i = 0; i < tTag->teamCnt; ++i)
    {
    CTag_army *tArmyTag = dcast< CTag_army* >(CTagMgr->UnarchiveStream(kTag_army,bytes));
    CArmy     *tArmy = new CArmy;
      
      tArmy->InitFromTag(tArmyTag);
      tTag->teams.push_back(tArmy);
    }
  }
}


/*  _________________________________________________________________________ */
void CTagFactory_save::DoArchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Archives a tag to a stream of bytes.

    @param tag    Pointer to the tag to archive from.
    @param bytes  The bytestream to contain the tag data.
*/
{
CTag_save* tTag = dcast< CTag_save* >(tag);
  
  if(0 != tTag)
  {
    bytes << tTag->teamCnt;
    for(unsigned int i = 0; i < tTag->teamCnt; ++i)
    {
      //FIXME
    }
  }
}
