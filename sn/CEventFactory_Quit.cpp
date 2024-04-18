/*! =========================================================================
      
      @file    CEventFactory_Quit.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_Quit.h"
#include "CEvent_Quit.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_Quit CEventFactory_Quit::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_Quit::CEventFactory_Quit(void)
: CEventFactory(kEvent_Quit)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_Quit::~CEventFactory_Quit(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_Quit::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_Quit);
}