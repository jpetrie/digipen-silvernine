/*! =========================================================================
      
      @file    CTag.h
      @brief   Interface to tag base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAG_H_
#define _C_TAG_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

// limits
const nsl::size_t  kTag_NameLimit = 8;
const nsl::size_t  kTag_DescLimit = 255;


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTag
/*! @brief Tag base class.
*/
{
  // contracts
  nlCONTRACT_NOCOPY(CTag);

  public:
    // typedefs
    typedef nsl::uint32_t  ID;
    
    
    // ct and dt
             CTag(ID id);
    virtual ~CTag(void);
    
    // accessors
    ID          Ident(void) const { return (mID); }
    std::string Name(void) const  { return (mName); }
    std::string Desc(void) const  { return (mDesc); }
    
    // manipulators
    void Name(const std::string &n) { mName = n; }
    void Desc(const std::string &d) { mDesc = d; }
   
    
  private:
    // data members
    const ID  mID;
    
    std::string  mName;  // Identifier, kTag_NameLimit max.
    std::string  mDesc;  // Descriptive, kTag_DescLimit max.
};


#endif  /* _C_TAG_H_ */
