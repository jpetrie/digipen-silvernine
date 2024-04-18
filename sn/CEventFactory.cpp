/*! =========================================================================
      
      @file    CEventFactory.cpp
      @brief   Implementation of event factory base class.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory::TFactoryMap  CEventFactory::smFactories;


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEventFactory::CEventFactory(CEvent::ID id)
/*! @brief Constructor.

    @param id  The ID of the event types this factory constructs.
*/
{
  smFactories.insert(std::make_pair(id,this));
}


/*  _________________________________________________________________________ */
CEventFactory::~CEventFactory(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory::ConstructEvent(CEvent::ID id)
/*! @brief Constructs a new event of the specified type.

    @param id  The ID of the event type to construct.
    
    @return
    A pointer to the new event.
*/
{
CEventFactory *tFactory = (*smFactories.find(id)).second;

  if(0 == tFactory)
    return (0);//FIXME throw an exception and make this work properly!
  else
    return (tFactory->nConstruct());
}