/*! =========================================================================
      
      @file    CEventFactory_UnitMove.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_UnitMove.h"
#include "CEvent_UnitMove.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_UnitMove CEventFactory_UnitMove::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_UnitMove::CEventFactory_UnitMove(void)
: CEventFactory(kEvent_UnitMove)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_UnitMove::~CEventFactory_UnitMove(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_UnitMove::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_UnitMove);
}