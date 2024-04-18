/*! =========================================================================
      
      @file    CEventFactory_UnitStop.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_UNITSTOP_H_
#define _C_EVENTFACTORY_UNITSTOP_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_UnitStop : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_UnitStop);

  public:
    // ct and dt
	   CEventFactory_UnitStop(void);
	  ~CEventFactory_UnitStop(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_UnitStop  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_UNITSTOP_H_ */
