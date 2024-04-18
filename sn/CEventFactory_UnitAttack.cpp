/*! =========================================================================
      
      @file    CEventFactory_UnitAttack.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_UnitAttack.h"
#include "CEvent_UnitAttack.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_UnitAttack CEventFactory_UnitAttack::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_UnitAttack::CEventFactory_UnitAttack(void)
: CEventFactory(kEvent_UnitAttack)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_UnitAttack::~CEventFactory_UnitAttack(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_UnitAttack::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_UnitAttack);
}