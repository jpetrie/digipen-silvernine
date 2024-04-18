/*! =========================================================================
      
      @file    CTag_obje.h
      @author  jpetrie
      @brief   'obje' Objects
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAG_OBJE_H_
#define _C_TAG_OBJE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "NSL.h"

#include "CTag.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// tag id
const CTag::ID  kTag_obje = nlFOURCODE('o','b','j','e');

// tag id strings
const std::string  kTag_obje_TypeStr = "obje";
const std::string  kTag_obje_KindStr = "objects";

// flags
const int  kObject_IgnoreCollision = 1;
const int  kObject_DrawSelection   = 2;
const int  kObject_DrawStatus      = 4;


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTag_obje : public CTag
/*! @brief obje Objects tag.
*/
{
  // stereotypes
  nlCONTRACT_NOCOPY(CTag_obje);

  // friends
  friend class CTagFactory_obje;
  
  public:
    // ct and dt
     CTag_obje(void) : CTag(kTag_obje) { }
    ~CTag_obje(void)                   { }
    
    // data members
    float  armorLo;
    float  armorHi;
    float  shieldLo;
    float  shieldHi;
    
    float  mass;
    float  radius;
    float  height;
    
    int    flags;
    
    float  dmgKineticLo;
    float  dmgKineticHi;
    float  dmgExplosiveLo;
    float  dmgExplosiveHi;
    float  dmgBurningLo;
    float  dmgBurningHi;
    float  dmgElectricalLo;
    float  dmgElectricalHi;
    float  dmgSyncLo;
    float  dmgSyncHi;
};


#endif  /* _C_TAG_OBJE_H_ */
