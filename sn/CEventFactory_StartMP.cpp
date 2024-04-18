/*! =========================================================================
      
      @file    CEventFactory_StartMP.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_StartMP.h"
#include "CEvent_StartMP.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_StartMP CEventFactory_StartMP::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_StartMP::CEventFactory_StartMP(void)
: CEventFactory(kEvent_StartMP)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_StartMP::~CEventFactory_StartMP(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_StartMP::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_StartMP);
}