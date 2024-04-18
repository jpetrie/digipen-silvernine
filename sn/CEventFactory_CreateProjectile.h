/*! =========================================================================
      
      @file    CEventFactory_CreateProjectile.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_CREATEPROJECTILE_H_
#define _C_EVENTFACTORY_CREATEPROJECTILE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_CreateProjectile : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_CreateProjectile);

  public:
    // ct and dt
	   CEventFactory_CreateProjectile(void);
	  ~CEventFactory_CreateProjectile(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_CreateProjectile  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_CREATEPROJECTILE_H_ */
