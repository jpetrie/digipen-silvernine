/*! =========================================================================
      
      @file    CTagFactory_save.h
      @brief   'save' tag factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAGFACTORY_SAVE_H_
#define _C_TAGFACTORY_SAVE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory.h"
#include "CTag_save.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTagFactory_save : public CTagFactory
/*! @brief save tag factory.
*/
{
  public:
    // ct and dt
             CTagFactory_save(void) : CTagFactory(kTag_save,kTag_save_TypeStr,kTag_save_KindStr) { }
    virtual ~CTagFactory_save(void)                          { }
   
   
  protected:
    // specific construction
    virtual CTag* DoCreate(void) { return new CTag_save; };
    
    // specific archival
    virtual void  DoUnarchive(CTag *tag,nsl::bstream &bytes);
    virtual void  DoArchive(CTag *tag,nsl::bstream &bytes);
    
        
  private:
    // data members
    static CTagFactory_save  smRegistrar;
};


#endif  /* _C_TAGFACTORY_SAVE_H_ */
