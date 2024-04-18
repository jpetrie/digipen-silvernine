/*! =========================================================================
      
      @file    CTag_mech.h
      @author  jmccrory
      @brief   'mech' Mechs
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAG_MECH_H_
#define _C_TAG_MECH_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "NSL.h"

#include "CTag.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// tag id
const CTag::ID  kTag_mech = nlFOURCODE('m','e','c','h');

// tag id strings
const std::string  kTag_mech_TypeStr = "mech";
const std::string  kTag_mech_KindStr = "mechs";


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTag_mech : public CTag
/*! @brief mech Mechs tag.
*/
{
  // contracts
  nlCONTRACT_NOCOPY(CTag_mech);

  // friends
  friend class CTagFactory_mech;
  
  public:
    // ct and dt
     CTag_mech(void) : CTag(kTag_mech) { physCnt = mentCnt = 0; }
    ~CTag_mech(void)                   { }
    
    // properties
    std::string		objeTag;
    std::string		sprcTag;
    
    int  idleSeqncIndx;      // Idle sequence index.
    int  walkSeqncIndx;      // 
    int  flinchSeqncIndx;    // 
    int  fire1SeqncIndx;     // 
    int  fire2SeqncIndx;     // 
    int  fire3SeqncIndx;     // 
    int  softSeqncIndx;      // Soft death sequence index.
    int  hardSeqncIndx;      // Hard death sequence index.
    int  tauntSeqncIndx;     // 
    int  portraitSeqncIndx;  // Army screen sequence index.
    
    float  baseSpeed;
    float  speedModGrass;
    float  speedModPavement;
    float  speedModShallowWater;
    float  speedModDeepWater;
    float  speedModBrush;
    float  speedModRocky;
    float  speedModGroundImpass;
    float  speedModAirImpass;
    
    float  radarRadius;   // How far the mech's radar can see.
    float  visionRadius;  // How far the mech's pilot can see.
    
    unsigned int     physCnt;      // Count of physical attacks.
    unsigned int     mentCnt;      // Count of mental attacks.
    nsl::stringlist  physAttacks;  // List of physical attacks (first is default).
    nsl::stringlist  mentAttacks;  // List of mental attacks.
};


#endif  /* _C_TAG_MECH_H_ */