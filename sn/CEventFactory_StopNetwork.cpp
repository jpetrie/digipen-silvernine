/*! =========================================================================
      
      @file    CEventFactory_StopNetwork.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_StopNetwork.h"
#include "CEvent_StopNetwork.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_StopNetwork CEventFactory_StopNetwork::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_StopNetwork::CEventFactory_StopNetwork(void)
: CEventFactory(kEvent_StopNetwork)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_StopNetwork::~CEventFactory_StopNetwork(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_StopNetwork::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_StopNetwork);
}