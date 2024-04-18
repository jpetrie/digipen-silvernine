/*! =========================================================================
      
      @file    CEventFactory_UnitSelect.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_UNITSELECT_H_
#define _C_EVENTFACTORY_UNITSELECT_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_UnitSelect : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_UnitSelect);

  public:
    // ct and dt
	   CEventFactory_UnitSelect(void);
	  ~CEventFactory_UnitSelect(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_UnitSelect  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_UNITSELECT_H_ */
