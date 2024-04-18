/*! =========================================================================
      
      @file    CEventFactory_DetonateProjectile.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_DetonateProjectile.h"
#include "CEvent_DetonateProjectile.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_DetonateProjectile CEventFactory_DetonateProjectile::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_DetonateProjectile::CEventFactory_DetonateProjectile(void)
: CEventFactory(kEvent_DetonateProjectile)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_DetonateProjectile::~CEventFactory_DetonateProjectile(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_DetonateProjectile::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_DetonateProjectile);
}