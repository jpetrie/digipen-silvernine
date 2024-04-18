/*! =========================================================================
      
      @file    CTag_unit.h
      @author  Patrick Laukaitis	plaukait@digipen.edu
      @brief   Unit Tag specification
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAG_UNIT_H_
#define _C_TAG_UNIT_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "NSL.h"

#include "CTag.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// tag id
const CTag::ID  kTag_unit= nlFOURCODE('u','n','i','t');

// tag id strings
const std::string  kTag_unit_TypeStr = "unit";
const std::string  kTag_unit_KindStr = "units";

// number of strings
const int kNumStrings = 4;


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTag_unit : public CTag
/*! @brief unit Units tag.
*/
{
  // stereotypes
  nlCONTRACT_NOCOPY(CTag_unit);

  // friends
  friend class CTagFactory_unit;
  
  public:
    // ct and dt
     CTag_unit(void) : CTag(kTag_unit) {
     int foo = 43;
     }
    ~CTag_unit(void)                   { }
    
    
    // data members
	  std::string		mech;
	  std::string		character;
	  std::string		script;
	  
	  std::string   names;
	  std::string   flavor;
};


#endif  /* _C_TAG_CPHY_H_ */
