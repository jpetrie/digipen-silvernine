/*! =========================================================================
      
      @file    CEventFactory_StartNetwork.cpp
      @brief   Implementation of the StartNetwork event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */



#include "precompiled.h"

#include "CEventFactory_StartNetwork.h"
#include "CEvent_StartNetwork.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_StartNetwork CEventFactory_StartNetwork::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_StartNetwork::CEventFactory_StartNetwork(void)
: CEventFactory(kEvent_StartNetwork)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_StartNetwork::~CEventFactory_StartNetwork(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_StartNetwork::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_StartNetwork);
}