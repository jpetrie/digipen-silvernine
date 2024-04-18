/*! =========================================================================
      
      @file    CEventFactory_DestroyProjectile.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_DESTROYPROJECTILE_H_
#define _C_EVENTFACTORY_DESTROYPROJECTILE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_DestroyProjectile : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_DestroyProjectile);

  public:
    // ct and dt
	   CEventFactory_DestroyProjectile(void);
	  ~CEventFactory_DestroyProjectile(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_DestroyProjectile  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_DESTROYPROJECTILE_H_ */
