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
void CTagFactory_mech::DoUnarchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Unarchives a tag from a stream of bytes.

    @param tag    Pointer to the tag to unarchive into.
    @param bytes  The bytestream containing the tag data.
*/
{
CTag_mech* tTag = dcast< CTag_mech* >(tag);
  
  if(0 != tTag)
  {
    // Pull the tag data from the stream.
    bytes >> tTag->objeTag >> tTag->sprcTag;
    
    // Sequence data.
    bytes >> tTag->idleSeqncIndx;
    /*    << tTag->walkSeqncIndx
          << tTag->flinchSeqncIndx
          << tTag->fire1SeqncIndx
          << tTag->fire2SeqncIndx
          << tTag->fire3SeqncIndx
          << tTag->softSeqncIndx
          << tTag->hardSeqncIndx
          << tTag->tauntSeqncIndx
          << tTag->portraitSeqncIndx;
    */
    
    // Speed and modifier data.
    bytes >> tTag->baseSpeed
          >> tTag->speedModGrass
          >> tTag->speedModPavement
          >> tTag->speedModShallowWater
          >> tTag->speedModDeepWater
          >> tTag->speedModBrush
          >> tTag->speedModRocky
          >> tTag->speedModGroundImpass
          >> tTag->speedModAirImpass;
    
    // Vision/sensor data.
    bytes >> tTag->visionRadius
          >> tTag->radarRadius;
    
    // Attack data.
    bytes >> tTag->physCnt;
    bytes >> tTag->mentCnt;
    for(unsigned int i = 0; i < tTag->physCnt; ++i)
    {
    std::string  tAttack;
    
      bytes >> tAttack;
      tTag->physAttacks.push_back(tAttack);
    }
    for(unsigned int i = 0; i < tTag->mentCnt; ++i)
    {
    std::string  tAttack;
    
      bytes >> tAttack;
      tTag->mentAttacks.push_back(tAttack);
    }
  }
}


/*  _________________________________________________________________________ */
void CTagFactory_mech::DoArchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Archives a tag to a stream of bytes.

    @param tag    Pointer to the tag to archive from.
    @param bytes  The bytestream to contain the tag data.
*/
{
CTag_mech* tTag = dcast< CTag_mech* >(tag);
  
  if(0 != tTag)
  {
    // Push the tag data into the stream.
    bytes << tTag->objeTag << tTag->sprcTag;
    
    // Sequence data.
    bytes << tTag->idleSeqncIndx;
/*        << tTag->walkSeqncIndx
          << tTag->flinchSeqncIndx
          << tTag->fire1SeqncIndx
          << tTag->fire2SeqncIndx
          << tTag->fire3SeqncIndx
          << tTag->softSeqncIndx
          << tTag->hardSeqncIndx
          << tTag->tauntSeqncIndx
          << tTag->portraitSeqncIndx;
  */  
    // Speed and modifier data.
    bytes << tTag->baseSpeed
          << tTag->speedModGrass
          << tTag->speedModPavement
          << tTag->speedModShallowWater
          << tTag->speedModDeepWater
          << tTag->speedModBrush
          << tTag->speedModRocky
          << tTag->speedModGroundImpass
          << tTag->speedModAirImpass;
          
    // Vision / radar.
    bytes << tTag->visionRadius
          << tTag->radarRadius;
    
    // Attacks.
    bytes << tTag->physCnt;
    bytes << tTag->mentCnt;
    for(unsigned int i = 0; i < tTag->physCnt; ++i)
      bytes << tTag->physAttacks[i];
    for(unsigned int i = 0; i < tTag->mentCnt; ++i)
      bytes << tTag->mentAttacks[i];
  }
}