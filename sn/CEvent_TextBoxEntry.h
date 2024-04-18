/*! =========================================================================
      
      @file    CEvent_TextBoxEntry.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_EVENT_TEXTBOXENTRY_H_
#define _C_EVENT_TEXTBOXENTRY_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent.h"
#include "CGameEngine.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// ID
const CEvent::ID  kEvent_TextBoxEntry = nlFOURCODE('T','B','E','T');


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CEvent_TextBoxEntry : public CEvent
/*! @brief 
*/
{
  public:
    // ct and dt
     CEvent_TextBoxEntry(void);
    ~CEvent_TextBoxEntry(void);
    
    // handling
    void Handle(CGameState *data);
  
    
    // properties
    /* PROPERTY DATA GOES HERE */
	std::string text;
};


#endif  /* _C_EVENT_TEXTBOXENTRY_H_ */
