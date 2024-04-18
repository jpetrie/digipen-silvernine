/*! =========================================================================
      
      @file    CTag_strc.h
      @brief   'strc' tag (string collections)
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAG_STRC_H_
#define _C_TAG_STRC_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTag.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// tag id
const CTag::ID  kTag_strc = nlFOURCODE('s','t','r','c');

// tag id strings
const std::string  kTag_strc_TypeStr = "strc";
const std::string  kTag_strc_KindStr = "string collections";


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTag_strc : public CTag
/*! @brief strc tag (string collections).
*/
{
  // contracts
  nlCONTRACT_NOCOPY(CTag_strc);


  // friends
  friend class CTagFactory_strc;
  

  public:
    // ct and dt
     CTag_strc(void) : CTag(kTag_strc) { stringCnt = 0; }
    ~CTag_strc(void)                   { }
    
    // properties
    unsigned int     stringCnt;
    nsl::stringlist  strings;
};


#endif  /* _C_TAG_STRC_H_ */
