/*! =========================================================================
      
      @file    CEventFactory_LevelEnd.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_LEVELEND_H_
#define _C_EVENTFACTORY_LEVELEND_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_LevelEnd : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_LevelEnd);

  public:
    // ct and dt
	   CEventFactory_LevelEnd(void);
	  ~CEventFactory_LevelEnd(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_LevelEnd  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_LEVELEND_H_ */
