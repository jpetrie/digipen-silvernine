/*! =========================================================================
      
      @file    CEventFactory_StopNetwork.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_STOPNETWORK_H_
#define _C_EVENTFACTORY_STOPNETWORK_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_StopNetwork : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_StopNetwork);

  public:
    // ct and dt
	   CEventFactory_StopNetwork(void);
	  ~CEventFactory_StopNetwork(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_StopNetwork  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_STOPNETWORK_H_ */
