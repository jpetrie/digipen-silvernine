/*! =========================================================================
      
      @file    CTagFactory_strc.h
      @brief   'strc' tag factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAGFACTORY_STRC_H_
#define _C_TAGFACTORY_STRC_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory.h"
#include "CTag_strc.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTagFactory_strc : public CTagFactory
/*! @brief strc tag factory.
*/
{
  public:
    // ct and dt
             CTagFactory_strc(void) : CTagFactory(kTag_strc,kTag_strc_TypeStr,kTag_strc_KindStr) { }
    virtual ~CTagFactory_strc(void)                          { }
   
   
  protected:
    // specific construction
    virtual CTag* DoCreate(void) { return new CTag_strc; };
    
    // specific archival
    virtual void  DoUnarchive(CTag *tag,nsl::bstream &bytes);
    virtual void  DoArchive(CTag *tag,nsl::bstream &bytes);
    
        
  private:
    // data members
    static CTagFactory_strc  smRegistrar;
};


#endif  /* _C_TAGFACTORY_STRC_H_ */
