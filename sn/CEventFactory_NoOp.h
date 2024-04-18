/*! =========================================================================
      
      @file    CEventFactory_NoOp.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_NOOP_H_
#define _C_EVENTFACTORY_NOOP_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_NoOp : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_NoOp);

  public:
    // ct and dt
	   CEventFactory_NoOp(void);
	  ~CEventFactory_NoOp(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_NoOp  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_NOOP_H_ */
