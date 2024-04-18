/*! =========================================================================
      
      @file    CEventFactory_Quit.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_QUIT_H_
#define _C_EVENTFACTORY_QUIT_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_Quit : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_Quit);

  public:
    // ct and dt
	   CEventFactory_Quit(void);
	  ~CEventFactory_Quit(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_Quit  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_QUIT_H_ */
