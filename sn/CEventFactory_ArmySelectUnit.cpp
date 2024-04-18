/*! =========================================================================
      
      @file    CEventFactory_ArmySelectUnit.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_ArmySelectUnit.h"
#include "CEvent_ArmySelectUnit.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_ArmySelectUnit CEventFactory_ArmySelectUnit::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_ArmySelectUnit::CEventFactory_ArmySelectUnit(void)
: CEventFactory(kEvent_ArmySelectUnit)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_ArmySelectUnit::~CEventFactory_ArmySelectUnit(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_ArmySelectUnit::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_ArmySelectUnit);
}