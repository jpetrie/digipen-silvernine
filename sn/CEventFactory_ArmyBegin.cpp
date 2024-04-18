/*! =========================================================================
      
      @file    CEventFactory_ArmyBegin.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_ArmyBegin.h"
#include "CEvent_ArmyBegin.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_ArmyBegin CEventFactory_ArmyBegin::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_ArmyBegin::CEventFactory_ArmyBegin(void)
: CEventFactory(kEvent_ArmyBegin)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_ArmyBegin::~CEventFactory_ArmyBegin(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_ArmyBegin::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_ArmyBegin);
}