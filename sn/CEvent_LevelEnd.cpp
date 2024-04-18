/*! =========================================================================
      
      @file    CEvent_LevelEnd.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_LevelEnd.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_LevelEnd::CEvent_LevelEnd(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_LevelEnd)
{
}


/*  _________________________________________________________________________ */
CEvent_LevelEnd::~CEvent_LevelEnd(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_LevelEnd::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
CGraphicsMgr->Reset();
  std::string level= CGame->RequestState()->level;
CGame->EndGameplay();
  
  //Get text to display
  std::ifstream  file( (nsl::stformat("data/text/%s_end_%c.txt", level.c_str(), (win?'v':'d'))).c_str() );
  std::string    text;
  
  file.seekg(0,ios_base::end);
  int sz = file.tellg();
  file.seekg(0,ios_base::beg);
  char *buffer = new char[sz + 1];

  memset(buffer,0,sz + 1);
  file.read(buffer,1000);//FIXME force only the first 550 of the file, due to wrapping bug
  text = buffer;
  file.close();
  //End of get text

 // CGame->LoadUIScreen("data/script/ui_results.uis");

  if(win)
    CGame->RequestScreen()->NewButton(0,0,"ui_wl",0,nlFOURCODE('n','o','o','p'),"");
  else
    CGame->RequestScreen()->NewButton(0,0,"ui_wl",1,nlFOURCODE('n','o','o','p'),"");
    
  //Added here instead of in Script because this function wacks the script
  
  /*  
  state->army_Briefing->SetWorldX(400);
  state->army_Briefing->SetWorldY(100);
  state->army_Briefing->SetWidth(400);
  state->army_Briefing->SetHeight(375);*/
  CGame->RequestScreen()->NewText(25,100,600,375,14,text.c_str());
}