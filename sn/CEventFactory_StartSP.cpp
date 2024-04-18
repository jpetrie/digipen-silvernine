/*! =========================================================================
      
      @file    CEventFactory_StartSP.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_StartSP.h"
#include "CEvent_StartSP.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_StartSP CEventFactory_StartSP::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_StartSP::CEventFactory_StartSP(void)
: CEventFactory(kEvent_StartSP)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_StartSP::~CEventFactory_StartSP(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_StartSP::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_StartSP);
}