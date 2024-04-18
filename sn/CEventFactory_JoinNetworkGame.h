/*! =========================================================================
      
      @file    CEventFactory_JoinNetworkGame.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_JOINNETWORKGAME_H_
#define _C_EVENTFACTORY_JOINNETWORKGAME_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_JoinNetworkGame : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_JoinNetworkGame);

  public:
    // ct and dt
	   CEventFactory_JoinNetworkGame(void);
	  ~CEventFactory_JoinNetworkGame(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_JoinNetworkGame  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_JOINNETWORKGAME_H_ */
