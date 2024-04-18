/*! =========================================================================
      
      @file    CEventFactory_StartSP.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_STARTSP_H_
#define _C_EVENTFACTORY_STARTSP_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_StartSP : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_StartSP);

  public:
    // ct and dt
	   CEventFactory_StartSP(void);
	  ~CEventFactory_StartSP(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_StartSP  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_STARTSP_H_ */
