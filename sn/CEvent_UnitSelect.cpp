/*! =========================================================================
      
      @file    CEvent_UnitSelect.cpp
      @brief   yayss
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_UnitSelect.h"

#include "UIButton.h"
#include "UIRingMenu.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_UnitSelect::CEvent_UnitSelect(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_UnitSelect)
{
}


/*  _________________________________________________________________________ */
CEvent_UnitSelect::~CEvent_UnitSelect(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_UnitSelect::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
  if(!unit->Selected())
  {
    unit->Selected(true);
    data->selected.push_back(unit);
  }
  else
  {
  std::vector< CUnit* >::iterator  tItr = data->selected.begin();
  
    // Find selected unit and deselect it.
    unit->Selected(false);
    while(tItr != data->selected.end())
    {
      if((*tItr)->Ident() == unit->Ident())
      {
        data->selected.erase(tItr);
        break;
      }
      ++tItr;
    }
  }
}