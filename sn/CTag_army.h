/*! =========================================================================
      
      @file    CTag_army.h
      @brief   'army' tag (armies)
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAG_ARMY_H_
#define _C_TAG_ARMY_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTag.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// tag id
const CTag::ID  kTag_army = nlFOURCODE('a','r','m','y');

// tag id strings
const std::string  kTag_army_TypeStr = "army";
const std::string  kTag_army_KindStr = "armies";


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTag_army : public CTag
/*! @brief army tag (armies).
*/
{
  // contracts
  nlCONTRACT_NOCOPY(CTag_army);


  // friends
  friend class CTagFactory_army;
  

  public:
    // structs
    struct StUnit
    //! Represents a unit.
    {
      std::string    unitBase;
      std::string    mechBase;
      float armor,   armorMax;
      float shields, shieldsMax;
      float sync,    syncMax;
    };
    
    // ct and dt
     CTag_army(void) : CTag(kTag_army) { }
    ~CTag_army(void)                   { }
    
    // properties
    unsigned int           cash;   
    unsigned int           size;   // Number of units in the army.
    std::vector< StUnit >  units;  // Units in the army.
};


#endif  /* _C_TAG_ARMY_H_ */
