/*! =========================================================================
      
      @file    CEventFactory_NoOp.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_NoOp.h"
#include "CEvent_NoOp.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_NoOp CEventFactory_NoOp::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_NoOp::CEventFactory_NoOp(void)
: CEventFactory(kEvent_NoOp)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_NoOp::~CEventFactory_NoOp(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_NoOp::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_NoOp);
}