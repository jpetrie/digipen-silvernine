/*! =========================================================================
      
      @file    CEventFactory_HostNetworkGame.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_HostNetworkGame.h"
#include "CEvent_HostNetworkGame.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_HostNetworkGame CEventFactory_HostNetworkGame::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_HostNetworkGame::CEventFactory_HostNetworkGame(void)
: CEventFactory(kEvent_HostNetworkGame)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_HostNetworkGame::~CEventFactory_HostNetworkGame(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_HostNetworkGame::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_HostNetworkGame);
}