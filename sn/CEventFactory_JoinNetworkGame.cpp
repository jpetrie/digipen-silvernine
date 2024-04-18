/*! =========================================================================
      
      @file    CEventFactory_JoinNetworkGame.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_JoinNetworkGame.h"
#include "CEvent_JoinNetworkGame.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_JoinNetworkGame CEventFactory_JoinNetworkGame::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_JoinNetworkGame::CEventFactory_JoinNetworkGame(void)
: CEventFactory(kEvent_JoinNetworkGame)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_JoinNetworkGame::~CEventFactory_JoinNetworkGame(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_JoinNetworkGame::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_JoinNetworkGame);
}