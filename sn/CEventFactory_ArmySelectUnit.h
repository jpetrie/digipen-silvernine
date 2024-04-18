/*! =========================================================================
      
      @file    CEventFactory_ArmySelectUnit.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_ARMYSELECTUNIT_H_
#define _C_EVENTFACTORY_ARMYSELECTUNIT_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_ArmySelectUnit : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_ArmySelectUnit);

  public:
    // ct and dt
	   CEventFactory_ArmySelectUnit(void);
	  ~CEventFactory_ArmySelectUnit(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_ArmySelectUnit  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_ARMYSELECTUNIT_H_ */
