/*! =========================================================================
      
      @file    CEventFactory_HostNetworkGame.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_HOSTNETWORKGAME_H_
#define _C_EVENTFACTORY_HOSTNETWORKGAME_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_HostNetworkGame : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_HostNetworkGame);

  public:
    // ct and dt
	   CEventFactory_HostNetworkGame(void);
	  ~CEventFactory_HostNetworkGame(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_HostNetworkGame  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_HOSTNETWORKGAME_H_ */
