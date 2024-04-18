/*! =========================================================================
      
      @file    CTagFactory_unit.h
      @brief   'unit' tag factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAGFACTORY_UNIT_H_
#define _C_TAGFACTORY_UNIT_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory.h"
#include "CTag_unit.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTagFactory_unit : public CTagFactory
/*! @brief unit tag factory.
*/
{
  public:
    // ct and dt
             CTagFactory_unit(void) : CTagFactory(kTag_unit,kTag_unit_TypeStr,kTag_unit_KindStr) { }
    virtual ~CTagFactory_unit(void)                                                              { }
   
   
  protected:
    // specific construction
    virtual CTag* DoCreate(void) { 
    return (new CTag_unit);
     };
  
    // specific archival
    virtual void  DoUnarchive(CTag *tag,nsl::bstream &bytes);
    virtual void  DoArchive(CTag *tag,nsl::bstream &bytes);
    
        
  private:
    // data members
    static CTagFactory_unit  smRegistrar;
};


#endif  /* _C_TAGFACTORY_UNIT_H_ */
