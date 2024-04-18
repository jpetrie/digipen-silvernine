/*! =========================================================================
      
      @file    CTagFactory_obje.cpp
      @brief   'obje' tag factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory_obje.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CTagFactory_obje  CTagFactory_obje::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
void CTagFactory_obje::DoUnarchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Unarchives a tag from a stream of bytes.

    @param tag    Pointer to the tag to unarchive into.
    @param bytes  The bytestream containing the tag data.
*/
{
CTag_obje* tTag = dcast< CTag_obje* >(tag);
  
  if(0 != tTag)
  {
    // Pull the tag data from the stream.
    bytes >> tTag->armorLo >> tTag->armorHi >> tTag->shieldLo >> tTag->shieldHi
          >> tTag->mass >> tTag->radius >> tTag->height
          >> tTag->flags
          >> tTag->dmgKineticLo    >> tTag->dmgKineticHi
          >> tTag->dmgExplosiveLo  >> tTag->dmgExplosiveHi
          >> tTag->dmgBurningLo    >> tTag->dmgBurningHi
          >> tTag->dmgElectricalLo >> tTag->dmgElectricalHi
          >> tTag->dmgSyncLo       >> tTag->dmgSyncHi;
  }
}


/*  _________________________________________________________________________ */
void CTagFactory_obje::DoArchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Archives a tag to a stream of bytes.

    @param tag    Pointer to the tag to archive from.
    @param bytes  The bytestream to contain the tag data.
*/
{
CTag_obje* tTag = dcast< CTag_obje* >(tag);
  
  if(0 != tTag)
  {
    // Push the tag data into the stream.
    bytes << tTag->armorLo << tTag->armorHi << tTag->shieldLo << tTag->shieldHi
          << tTag->mass << tTag->radius << tTag->height
          << tTag->flags
          << tTag->dmgKineticLo    << tTag->dmgKineticHi
          << tTag->dmgExplosiveLo  << tTag->dmgExplosiveHi
          << tTag->dmgBurningLo    << tTag->dmgBurningHi
          << tTag->dmgElectricalLo << tTag->dmgElectricalHi
          << tTag->dmgSyncLo       << tTag->dmgSyncHi;
  }
}
