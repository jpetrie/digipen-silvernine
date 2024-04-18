/*! =========================================================================
      
      @file    CTag_cphy.h
      @author  jpetrie
      @brief   'scri' Scripts
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAG_SCRI_H_
#define _C_TAG_SCRI_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "NSL.h"

#include "CTag.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// tag id
const CTag::ID  kTag_scri = nlFOURCODE('s','c','r','i');

// tag id strings
const std::string  kTag_scri_TypeStr = "scri";
const std::string  kTag_scri_KindStr = "scripts";


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTag_scri : public CTag
/*! @brief scri Scripts tag.
*/
{
  // stereotypes
  nlCONTRACT_NOCOPY(CTag_scri);
  
  // friends
  friend class CTagFactory_scri;
  
  public:
    // ct and dt
     CTag_scri(void) : CTag(kTag_scri) { }
    ~CTag_scri(void)                   { }


    // data members
    std::string  uncompiled;  // Uncompiled Lua code.
};


#endif  /* _C_TAG_SCRI_H_ */
