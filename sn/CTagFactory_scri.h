/*! =========================================================================
      
      @file    CTagFactory_scri.h
      @brief   'scri' tag factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAGFACTORY_SCRI_H_
#define _C_TAGFACTORY_SCRI_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory.h"
#include "CTag_scri.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTagFactory_scri : public CTagFactory
/*! @brief scri tag factory.
*/
{
  public:
    // ct and dt
             CTagFactory_scri(void) : CTagFactory(kTag_scri,kTag_scri_TypeStr,kTag_scri_KindStr) { }
    virtual ~CTagFactory_scri(void)                                                              { }
   
   
  protected:
    // specific construction
    virtual CTag* DoCreate(void) { return new CTag_scri; };
    
    // specific archival
    virtual void  DoUnarchive(CTag *tag,nsl::bstream &bytes);
    virtual void  DoArchive(CTag *tag,nsl::bstream &bytes);
    
        
  private:
    // data members
    static CTagFactory_scri  smRegistrar;
};


#endif  /* _C_TAGFACTORY_SCRI_H_ */
