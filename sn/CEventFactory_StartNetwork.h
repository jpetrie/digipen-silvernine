/*! =========================================================================
      
      @file    CEventFactory_StartNetwork.h
      @brief   Interface to the StartNetwork event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_STARTNETWORK_H_
#define _C_EVENTFACTORY_STARTNETWORK_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_StartNetwork : public CEventFactory
/*! @brief  Factory for Starting the network layer (multiplayer)
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_StartNetwork);

  public:
    // ct and dt
	   CEventFactory_StartNetwork(void);
	  ~CEventFactory_StartNetwork(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_StartNetwork  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_STARTNETWORK_H_ */
