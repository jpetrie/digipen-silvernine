/*! =========================================================================
      
      @file    CEventFactory_UnitDestroy.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_UNITDESTROY_H_
#define _C_EVENTFACTORY_UNITDESTROY_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_UnitDestroy : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_UnitDestroy);

  public:
    // ct and dt
	   CEventFactory_UnitDestroy(void);
	  ~CEventFactory_UnitDestroy(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_UnitDestroy  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_UNITDESTROY_H_ */
