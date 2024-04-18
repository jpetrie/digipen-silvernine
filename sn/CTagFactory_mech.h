/*! =========================================================================
      
      @file    CTagFactory_mech.h
      @brief   'mech' tag factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAGFACTORY_MECH_H_
#define _C_TAGFACTORY_MECH_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory.h"
#include "CTag_mech.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTagFactory_mech : public CTagFactory
/*! @brief mech tag factory.
*/
{
  public:
    // ct and dt
             CTagFactory_mech(void) : CTagFactory(kTag_mech,kTag_mech_TypeStr,kTag_mech_KindStr) { }
    virtual ~CTagFactory_mech(void)                                                              { }
   
   
  protected:
    // specific construction
    virtual CTag* DoCreate(void) { return new CTag_mech; };
    
    // specific archival
    virtual void  DoUnarchive(CTag *tag,nsl::bstream &bytes);
    virtual void  DoArchive(CTag *tag,nsl::bstream &bytes);
    
        
  private:
    // data members
    static CTagFactory_mech  smRegistrar;
};


#endif  /* _C_TAGFACTORY_MECH_H_ */