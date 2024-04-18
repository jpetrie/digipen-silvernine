/*! =========================================================================
      
      @file    CEventFactory_DetonateProjectile.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_DETONATEPROJECTILE_H_
#define _C_EVENTFACTORY_DETONATEPROJECTILE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_DetonateProjectile : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_DetonateProjectile);

  public:
    // ct and dt
	   CEventFactory_DetonateProjectile(void);
	  ~CEventFactory_DetonateProjectile(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_DetonateProjectile  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_DETONATEPROJECTILE_H_ */
