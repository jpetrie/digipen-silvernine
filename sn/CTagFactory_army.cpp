/*! =========================================================================
      
      @file    CTagFactory_army.cpp
      @brief   'army' tag factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory_army.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CTagFactory_army  CTagFactory_army::smRegistrar;


/*                                                           member functions
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
void CTagFactory_army::DoUnarchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Unarchives a tag from a stream of bytes.

    @param tag    Pointer to the tag to unarchive into.
    @param bytes  The bytestream containing the tag data.
*/
{
CTag_army* tTag = dcast< CTag_army* >(tag);
  
  if(0 != tTag)
  {
    bytes >> tTag->cash >> tTag->size;
    for(unsigned int i = 0; i < tTag->size; ++i)
    {
    CTag_army::StUnit  tUnit;
    
      bytes >> tUnit.unitBase >> tUnit.mechBase;
      bytes >> tUnit.armor >> tUnit.armorMax
            >> tUnit.shields >> tUnit.shieldsMax
            >> tUnit.sync >> tUnit.syncMax;
      
      tTag->units.push_back(tUnit);
    }
  }
}


/*  _________________________________________________________________________ */
void CTagFactory_army::DoArchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Archives a tag to a stream of bytes.

    @param tag    Pointer to the tag to archive from.
    @param bytes  The bytestream to contain the tag data.
*/
{
CTag_army* tTag = dcast< CTag_army* >(tag);
  
  if(0 != tTag)
  {
    bytes << tTag->cash << tTag->size;
    for(unsigned int i = 0; i < tTag->size; ++i)
    {
      bytes << tTag->units[i].unitBase << tTag->units[i].mechBase;
      bytes << tTag->units[i].armor << tTag->units[i].armorMax
            << tTag->units[i].shields << tTag->units[i].shieldsMax
            << tTag->units[i].sync << tTag->units[i].syncMax;
    }
  }
}
