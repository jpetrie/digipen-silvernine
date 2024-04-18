/*! =========================================================================
      
      @file    CEventFactory_CreateProjectile.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_CreateProjectile.h"
#include "CEvent_CreateProjectile.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_CreateProjectile CEventFactory_CreateProjectile::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_CreateProjectile::CEventFactory_CreateProjectile(void)
: CEventFactory(kEvent_CreateProjectile)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_CreateProjectile::~CEventFactory_CreateProjectile(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_CreateProjectile::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_CreateProjectile);
}