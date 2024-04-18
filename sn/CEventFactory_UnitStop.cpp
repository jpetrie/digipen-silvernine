/*! =========================================================================
      
      @file    CEventFactory_UnitStop.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_UnitStop.h"
#include "CEvent_UnitStop.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_UnitStop CEventFactory_UnitStop::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_UnitStop::CEventFactory_UnitStop(void)
: CEventFactory(kEvent_UnitStop)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_UnitStop::~CEventFactory_UnitStop(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_UnitStop::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_UnitStop);
}