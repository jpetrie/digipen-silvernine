/*! =========================================================================
      
      @file    CEventFactory_LevelBegin.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_LEVELBEGIN_H_
#define _C_EVENTFACTORY_LEVELBEGIN_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_LevelBegin : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_LevelBegin);

  public:
    // ct and dt
	   CEventFactory_LevelBegin(void);
	  ~CEventFactory_LevelBegin(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_LevelBegin  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_LEVELBEGIN_H_ */
