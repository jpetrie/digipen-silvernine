/*! =========================================================================
      
      @file    CTag_save.h
      @brief   'save' tag (saved games)
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAG_SAVE_H_
#define _C_TAG_SAVE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTag.h"

#include "CArmy.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// tag id
const CTag::ID  kTag_save = nlFOURCODE('s','a','v','e');

// tag id strings
const std::string  kTag_save_TypeStr = "save";
const std::string  kTag_save_KindStr = "saved games";


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTag_save : public CTag
/*! @brief save tag (saved games).
*/
{
  // contracts
  nlCONTRACT_NOCOPY(CTag_save);


  // friends
  friend class CTagFactory_save;
  

  public:
    // ct and dt
     CTag_save(void) : CTag(kTag_save) { }
    ~CTag_save(void)                   { }
    
    // properties
    nsl::uint8_t           teamCnt;
    std::vector< CArmy* >  teams; 
};


#endif  /* _C_TAG_SAVE_H_ */
