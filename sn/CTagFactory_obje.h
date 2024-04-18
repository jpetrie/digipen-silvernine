/*! =========================================================================
      
      @file    CTagFactory_obje.h
      @brief   'obje' tag factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAGFACTORY_OBJE_H_
#define _C_TAGFACTORY_OBJE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory.h"
#include "CTag_obje.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTagFactory_obje : public CTagFactory
/*! @brief obje tag factory.
*/
{
  public:
    // ct and dt
             CTagFactory_obje(void) : CTagFactory(kTag_obje,kTag_obje_TypeStr,kTag_obje_KindStr) { }
    virtual ~CTagFactory_obje(void)                                                              { }
   
   
  protected:
    // specific construction
    virtual CTag* DoCreate(void) { return new CTag_obje; };
    
    // specific archival
    virtual void  DoUnarchive(CTag *tag,nsl::bstream &bytes);
    virtual void  DoArchive(CTag *tag,nsl::bstream &bytes);
    
        
  private:
    // data members
    static CTagFactory_obje  smRegistrar;
};


#endif  /* _C_TAGFACTORY_OBJE_H_ */
