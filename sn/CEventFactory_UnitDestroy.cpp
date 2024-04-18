/*! =========================================================================
      
      @file    CEventFactory_UnitDestroy.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_UnitDestroy.h"
#include "CEvent_UnitDestroy.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_UnitDestroy CEventFactory_UnitDestroy::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_UnitDestroy::CEventFactory_UnitDestroy(void)
: CEventFactory(kEvent_UnitDestroy)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_UnitDestroy::~CEventFactory_UnitDestroy(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_UnitDestroy::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_UnitDestroy);
}