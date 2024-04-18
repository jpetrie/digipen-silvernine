/*! =========================================================================
      
      @file    CEventFactory_ConnectToServer.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_CONNECTTOSERVER_H_
#define _C_EVENTFACTORY_CONNECTTOSERVER_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_ConnectToServer : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_ConnectToServer);

  public:
    // ct and dt
	   CEventFactory_ConnectToServer(void);
	  ~CEventFactory_ConnectToServer(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_ConnectToServer  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_CONNECTTOSERVER_H_ */
