/*! =========================================================================
      
      @file    CEventFactory.h
      @brief   Interface to event factory class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENTFACTORY_H_
#define _C_EVENTFACTORY_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEventFactory
/*! @brief Event factory class.

    Event factories allow for the construction of CEvent objects. Every
    subclass of CEvent should have a corrisponding subclass of CEventFactory
    that implements the protected Construct() method to create a new event of
    the appropriate type.
    
    Events can be constructed in a general fashion by using the static
    ConstructEvent() method of CEventFactory, which takes an event ID and
    returns a pointer to the appropriate type of event.
*/
{ 
  // contracts
  nlCONTRACT_NOCOPY(CEventFactory);

  public:
    // ct and dt
             CEventFactory(CEvent::ID id);
    virtual ~CEventFactory(void);
    
    // generic construction
    static CEvent* ConstructEvent(CEvent::ID id);
  
  
  protected:
    // specific construction
    virtual CEvent* nConstruct(void) = 0;
    
    
  private:
     // typedefs
     typedef std::map< CEvent::ID,CEventFactory* >  TFactoryMap;
     
     
     // data members
     static TFactoryMap  smFactories;
};


#endif  /* _C_EVENTFACTORY_H_ */
