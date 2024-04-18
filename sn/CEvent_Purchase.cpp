/*! =========================================================================
      
      @file    CEvent_Purchase.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_Purchase.h"
#include "CGameEngine.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_Purchase::CEvent_Purchase(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_Purchase)
{
}


/*  _________________________________________________________________________ */
CEvent_Purchase::~CEvent_Purchase(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_Purchase::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
  CGameState *state  = CGame->RequestState();
  std::vector< CUnit* >::iterator iter = state->hireUnits.begin();
  int purchaseTotal = 0;
  
  while(iter != state->hireUnits.end())
  {
    purchaseTotal += (*iter)->Mech()->Cost(); 
    ++iter;
  }
  
  if(purchaseTotal <= state->teams[0]->GetMoney())
  {
  int midx = 0;
  
    state->teams[0]->SetMoney(state->teams[0]->GetMoney() - purchaseTotal);
    CGame->PostEvent(CGame->MakeEvent(nlFOURCODE('a','r','m','b')));
    
    iter = state->hireUnits.begin();
    while(iter != state->hireUnits.end())
    {
      if(std::find(CGame->mWaitingUnits.begin(),CGame->mWaitingUnits.end(),midx) != CGame->mWaitingUnits.end())
      {
        state->teams[0]->AddUnit(*iter);
        *iter = 0;
      }
      ++iter;
      midx++;
    }
  }
  else
  {
    //FIXME should *BEEP* or soemthing here
  }
}