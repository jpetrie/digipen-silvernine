/*! =========================================================================
      
      @file    CEventFactory_UnitSelect.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_UnitSelect.h"
#include "CEvent_UnitSelect.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_UnitSelect CEventFactory_UnitSelect::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_UnitSelect::CEventFactory_UnitSelect(void)
: CEventFactory(kEvent_UnitSelect)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_UnitSelect::~CEventFactory_UnitSelect(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_UnitSelect::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_UnitSelect);
}