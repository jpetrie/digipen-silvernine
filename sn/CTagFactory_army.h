/*! =========================================================================
      
      @file    CTagFactory_army.h
      @brief   'army' tag factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAGFACTORY_ARMY_H_
#define _C_TAGFACTORY_ARMY_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory.h"
#include "CTag_army.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTagFactory_army : public CTagFactory
/*! @brief army tag factory.
*/
{
  public:
    // ct and dt
             CTagFactory_army(void) : CTagFactory(kTag_army,kTag_army_TypeStr,kTag_army_KindStr) { }
    virtual ~CTagFactory_army(void)                          { }
   
   
  protected:
    // specific construction
    virtual CTag* DoCreate(void) { return new CTag_army; };
    
    // specific archival
    virtual void  DoUnarchive(CTag *tag,nsl::bstream &bytes);
    virtual void  DoArchive(CTag *tag,nsl::bstream &bytes);
    
        
  private:
    // data members
    static CTagFactory_army  smRegistrar;
};


#endif  /* _C_TAGFACTORY_ARMY_H_ */
