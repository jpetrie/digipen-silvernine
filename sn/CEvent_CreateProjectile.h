/*! =========================================================================
      
      @file    CEvent_CreateProjectile.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_CREATEPROJECTILE_H_
#define _C_EVENT_CREATEPROJECTILE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_CreateProjectile = nlFOURCODE('c','r','t','p');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_CreateProjectile : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_CreateProjectile(void);
    ~CEvent_CreateProjectile(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    /* PROPERTY DATA GOES HERE */
	std::string tag;
	CUnit *owner;
	CUnit *target;
	float originX;
	float originY;
	float destX;
	float destY;
	int   life;

  std::string ammoFor; //attack given when ammo proj picked up
};


#endif  /* _C_EVENT_CREATEPROJECTILE_H_ */
