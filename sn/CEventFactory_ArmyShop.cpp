/*! =========================================================================
      
      @file    CEventFactory_ArmyShop.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_ArmyShop.h"
#include "CEvent_ArmyShop.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_ArmyShop CEventFactory_ArmyShop::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_ArmyShop::CEventFactory_ArmyShop(void)
: CEventFactory(kEvent_ArmyShop)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_ArmyShop::~CEventFactory_ArmyShop(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_ArmyShop::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_ArmyShop);
}