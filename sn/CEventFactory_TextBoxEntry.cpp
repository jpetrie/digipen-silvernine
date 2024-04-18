/*! =========================================================================
      
      @file    CEventFactory_TextBoxEntry.cpp
      @brief   Implementation of event factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory_TextBoxEntry.h"
#include "CEvent_TextBoxEntry.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CEventFactory_TextBoxEntry CEventFactory_TextBoxEntry::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CEventFactory_TextBoxEntry::CEventFactory_TextBoxEntry(void)
: CEventFactory(kEvent_TextBoxEntry)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
CEventFactory_TextBoxEntry::~CEventFactory_TextBoxEntry(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
CEvent* CEventFactory_TextBoxEntry::nConstruct(void)
/*! @brief Construction method.

    @return
    A new event.
*/
{
  return (new CEvent_TextBoxEntry);
}