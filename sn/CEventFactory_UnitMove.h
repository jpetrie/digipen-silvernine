/*! =========================================================================
      
      @file    CEventFactory_UnitMove.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_UNITMOVE_H_
#define _C_EVENTFACTORY_UNITMOVE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_UnitMove : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_UnitMove);

  public:
    // ct and dt
	   CEventFactory_UnitMove(void);
	  ~CEventFactory_UnitMove(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_UnitMove  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_UNITMOVE_H_ */
