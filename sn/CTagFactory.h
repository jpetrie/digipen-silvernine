/*! =========================================================================
      
      @file    CTagFactory.h
      @brief   Interface to tag factory base class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAGFACTORY_H_
#define _C_TAGFACTORY_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTag.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTagFactory
/*! @brief Tag factory base class.
*/
{
  // contracts
  nlCONTRACT_NOCOPY(CTagFactory);
  
  
  public:
    // ct and dt
             CTagFactory(CTag::ID id,const std::string &typestr,const std::string &kindstr);
    virtual ~CTagFactory(void);
    
    // accessors
    CTag::ID     Ident(void) const      { return (mID); }
    std::string  TypeString(void) const { return (mTypeStr); }
    std::string  KindString(void) const { return (mKindStr); }
  
    // factory workers
    virtual CTag* DoCreate(void) = 0;
    virtual void  DoUnarchive(CTag *tag,nsl::bstream &bytes) = 0;
    virtual void  DoArchive(CTag *tag,nsl::bstream &bytes) = 0;
  
  
  private:
    // data members
    const CTag::ID     mID;       // ID of the tag this factory constructs.
    const std::string  mTypeStr;  // Stringification of tag ID.
    const std::string  mKindStr;  // Stringification of tag name.
};


#endif  /* _C_TAGFACTORY_H_ */
