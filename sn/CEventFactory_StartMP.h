/*! =========================================================================
      
      @file    CEventFactory_StartMP.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_STARTMP_H_
#define _C_EVENTFACTORY_STARTMP_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_StartMP : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_StartMP);

  public:
    // ct and dt
	   CEventFactory_StartMP(void);
	  ~CEventFactory_StartMP(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_StartMP  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_STARTMP_H_ */
