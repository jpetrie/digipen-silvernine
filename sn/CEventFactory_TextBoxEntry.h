/*! =========================================================================
      
      @file    CEventFactory_TextBoxEntry.h
      @brief   Interface to event factory.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_TEXTBOXENTRY_H_
#define _C_EVENTFACTORY_TEXTBOXENTRY_H_


/*                                                                   includes
----------------------------------------------------------------------------- */


#include "precompiled.h"

#include "CEventFactory.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory_TextBoxEntry : public CEventFactory
/*! @brief  Factory for level begin events.
*/
{ 
  // stereotypes
  nlCONTRACT_NOCOPY(CEventFactory_TextBoxEntry);

  public:
    // ct and dt
	   CEventFactory_TextBoxEntry(void);
	  ~CEventFactory_TextBoxEntry(void);
	
	
	protected:
	  // construction
	  CEvent* nConstruct(void);
         
         
  private:
     // data members
     static CEventFactory_TextBoxEntry  smRegistrar;
};


#endif  /* _C_EVENTFACTORY_TEXTBOXENTRY_H_ */
