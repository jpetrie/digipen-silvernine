/*! =========================================================================
      
      @file    CEventFactory_StartNetworkGame.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_STARTNETWORKGAME_H_
#define _C_EVENTFACTORY_STARTNETWORKGAME_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_StartNetworkGame : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_StartNetworkGame);

  public:
    // ct and dt
	   CEventFactory_StartNetworkGame(void);
	  ~CEventFactory_StartNetworkGame(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_StartNetworkGame  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_STARTNETWORKGAME_H_ */
