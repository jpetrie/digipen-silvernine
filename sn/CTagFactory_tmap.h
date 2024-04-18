/*! =========================================================================
      
      @file    CTagFactory_tmap.h
      @author  jpetrie
      @brief   'tmap' tag factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAGFACTORY_TMAP_H_
#define _C_TAGFACTORY_TMAP_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory.h"
#include "CTag_tmap.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTagFactory_tmap : public CTagFactory
/*! @brief tmap tag factory.
*/
{
  public:
    // ct and dt
             CTagFactory_tmap(void) : CTagFactory(kTag_tmap,kTag_tmap_TypeStr,kTag_tmap_KindStr) { }
    virtual ~CTagFactory_tmap(void) { }
   
   
  protected:
    // factory workers
    virtual CTag* DoCreate(void) { return new CTag_tmap; };
    virtual void  DoUnarchive(CTag *tag,nsl::bstream &bytes);
    virtual void  DoArchive(CTag *tag,nsl::bstream &bytes);
    

  private:
    // data members
    static CTagFactory_tmap  smRegistrar;
};

#endif  /* _C_TAGFACTORY_TMAP_H_ */
