/*! =========================================================================
      
      @file    CEventFactory_StartNetworkGame.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_StartNetworkGame.h"
#include "CEvent_StartNetworkGame.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_StartNetworkGame CEventFactory_StartNetworkGame::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_StartNetworkGame::CEventFactory_StartNetworkGame(void)
: CEventFactory(kEvent_StartNetworkGame)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_StartNetworkGame::~CEventFactory_StartNetworkGame(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_StartNetworkGame::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_StartNetworkGame);
}