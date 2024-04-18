/*! =========================================================================
      
      @file    CEvent_DetonateProjectile.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_DETONATEPROJECTILE_H_
#define _C_EVENT_DETONATEPROJECTILE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_DetonateProjectile = nlFOURCODE('d','e','t','p');


/*                                                                    classes
----------------------------------------------------------------------------- */
// forward references
class CProjectile;
class CMech;

/*  _________________________________________________________________________ */
class CEvent_DetonateProjectile : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_DetonateProjectile(void);
    ~CEvent_DetonateProjectile(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    /* PROPERTY DATA GOES HERE */
	CProjectile * This;
	CMech * HitMe;
};


#endif  /* _C_EVENT_DETONATEPROJECTILE_H_ */
