/*! =========================================================================
      
      @file    CEventFactory_LevelBegin.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_LevelBegin.h"
#include "CEvent_LevelBegin.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_LevelBegin CEventFactory_LevelBegin::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_LevelBegin::CEventFactory_LevelBegin(void)
: CEventFactory(kEvent_LevelBegin)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_LevelBegin::~CEventFactory_LevelBegin(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_LevelBegin::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_LevelBegin);
}