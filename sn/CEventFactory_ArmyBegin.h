/*! =========================================================================
      
      @file    CEventFactory_ArmyBegin.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_ARMYBEGIN_H_
#define _C_EVENTFACTORY_ARMYBEGIN_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_ArmyBegin : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_ArmyBegin);

  public:
    // ct and dt
	   CEventFactory_ArmyBegin(void);
	  ~CEventFactory_ArmyBegin(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_ArmyBegin  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_ARMYBEGIN_H_ */
