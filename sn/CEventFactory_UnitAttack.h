/*! =========================================================================
      
      @file    CEventFactory_UnitAttack.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_UNITATTACK_H_
#define _C_EVENTFACTORY_UNITATTACK_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_UnitAttack : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_UnitAttack);

  public:
    // ct and dt
	   CEventFactory_UnitAttack(void);
	  ~CEventFactory_UnitAttack(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_UnitAttack  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_UNITATTACK_H_ */
