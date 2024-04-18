/*! =========================================================================
      
      @file    CEventFactory_DestroyProjectile.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_DestroyProjectile.h"
#include "CEvent_DestroyProjectile.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_DestroyProjectile CEventFactory_DestroyProjectile::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_DestroyProjectile::CEventFactory_DestroyProjectile(void)
: CEventFactory(kEvent_DestroyProjectile)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_DestroyProjectile::~CEventFactory_DestroyProjectile(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_DestroyProjectile::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_DestroyProjectile);
}