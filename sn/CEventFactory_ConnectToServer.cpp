/*! =========================================================================
      
      @file    CEventFactory_ConnectToServer.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_ConnectToServer.h"
#include "CEvent_ConnectToServer.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_ConnectToServer CEventFactory_ConnectToServer::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_ConnectToServer::CEventFactory_ConnectToServer(void)
: CEventFactory(kEvent_ConnectToServer)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_ConnectToServer::~CEventFactory_ConnectToServer(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_ConnectToServer::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_ConnectToServer);
}