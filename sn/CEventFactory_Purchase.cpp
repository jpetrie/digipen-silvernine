/*! =========================================================================
      
      @file    CEventFactory_Purchase.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_Purchase.h"
#include "CEvent_Purchase.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_Purchase CEventFactory_Purchase::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_Purchase::CEventFactory_Purchase(void)
: CEventFactory(kEvent_Purchase)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_Purchase::~CEventFactory_Purchase(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_Purchase::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_Purchase);
}