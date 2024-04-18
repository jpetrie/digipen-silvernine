/*! =========================================================================
      
      @file    CEventFactory_Purchase.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_PURCHASE_H_
#define _C_EVENTFACTORY_PURCHASE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_Purchase : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_Purchase);

  public:
    // ct and dt
	   CEventFactory_Purchase(void);
	  ~CEventFactory_Purchase(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_Purchase  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_PURCHASE_H_ */
