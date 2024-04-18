/*! =========================================================================
      
      @file    CEventFactory_LevelEnd.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_LevelEnd.h"
#include "CEvent_LevelEnd.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_LevelEnd CEventFactory_LevelEnd::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_LevelEnd::CEventFactory_LevelEnd(void)
: CEventFactory(kEvent_LevelEnd)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_LevelEnd::~CEventFactory_LevelEnd(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_LevelEnd::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_LevelEnd);
}