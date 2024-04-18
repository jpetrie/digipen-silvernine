/*! =========================================================================
      
      @file    CEventFactory_ArmyShop.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_ARMYSHOP_H_
#define _C_EVENTFACTORY_ARMYSHOP_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_ArmyShop : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_ArmyShop);

  public:
    // ct and dt
	   CEventFactory_ArmyShop(void);
	  ~CEventFactory_ArmyShop(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_ArmyShop  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_ARMYSHOP_H_ */
