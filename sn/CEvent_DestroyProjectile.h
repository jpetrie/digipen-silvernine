/*! =========================================================================
      
      @file    CEvent_DestroyProjectile.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_DESTROYPROJECTILE_H_
#define _C_EVENT_DESTROYPROJECTILE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_DestroyProjectile = nlFOURCODE('d','s','t','p');

// forward reference
class CProjectile;
/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_DestroyProjectile : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_DestroyProjectile(void);
    ~CEvent_DestroyProjectile(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    /* PROPERTY DATA GOES HERE */
	CProjectile *This;
};


#endif  /* _C_EVENT_DESTROYPROJECTILE_H_ */
