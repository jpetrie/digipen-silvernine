/*! =========================================================================
      
      @file    CEvent_ArmyBegin.cpp
      @brief   Begins army management.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_ArmyBegin.h"
#include "CEvent_LevelBegin.h"
#include "CTag_army.h"

/*                                                        internal prototypes
----------------------------------------------------------------------------- */

void FillStoreList(nsl::stringlist &list,const std::string &path,const std::string &mask,int limit);

// This should by synched with the StartSP and StartMP events
namespace
{
  const std::string  ikPreload     = "data/preload/single.pre";
  const std::string  ikMultiPreload= "data/preload/multi.pre";
  const std::string  ikNewGameSave = "data/preload/newgame.sta";
};


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_ArmyBegin::CEvent_ArmyBegin(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_ArmyBegin)
{
}


/*  _________________________________________________________________________ */
CEvent_ArmyBegin::~CEvent_ArmyBegin(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_ArmyBegin::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
  // Load the UI.
  CGame->LoadUIScreen("data/script/ui_armymain.uis");
  
  if(CGame->RequestState()->army_Briefing != 0)
  {
    delete CGame->RequestState()->army_Briefing;
    CGame->RequestState()->army_Briefing = 0;
  }
  
  // Control the team at index zero.
  CGame->attacksAvail.clear();
  CGame->attacksAvail.push_back("mini");
  CGame->attacksAvail.push_back("chan");
  CGame->attacksAvail.push_back("snip");
  CGame->attacksAvail.push_back("rail");
 
 
  // Set from network data -- plaukait
  if(CGame->NetGame())
  {
	  // currentUserID will have the ID assigned by the server prior to getting here
	  //data->thisTeam = CGame->RequestState()->currentUserID;
	  //data->thisPlayer = CGame->RequestState()->currentUserID;
	  data->thisTeam = CGame->RequestState()->thisPlayer;
	  data->thisPlayer = CGame->RequestState()->thisPlayer;
  }
  else
  {
	data->thisTeam = 0;    
	data->thisPlayer = 0;  
  }

  // Make sure mask files exist.
  if(!nsl::fdexists("data/mask/unit.msk"))
    nlTHROWV(XUnitMaskNotFound,nsl::stformat("Unit maskfile not found."));  
  FillStoreList(data->unitShop,"data/patch/units/","data/mask/unit.msk",kShop_UnitSize);
  

  // Check that there are enough teams in the vector to access the proper member
  if(data->thisTeam >= CGame->RequestState()->teams.size())
  {
	  int numToAdd = data->thisTeam - CGame->RequestState()->teams.size();
	  for(int i = 0; i <= numToAdd; ++i)
		  CGame->RequestState()->teams.push_back(0);
  }

  if(0 == CGame->RequestState()->teams[data->thisTeam])
  {
	CGame->RequestState()->teams[data->thisTeam] = new CArmy;
		
	// Unarchive the new game state and copy relevant data.
	//data->Load(ikNewGameSave);
  }

  // The gamestate is loaded at position 0 -> copy the pointer to the proper location
  CArmy * temp = CGame->RequestState()->teams[0];
  CGame->RequestState()->teams[0] = 0;
  CGame->RequestState()->teams[data->thisTeam] = temp;

  
CGameState *state  = CGame->RequestState();
UIScreen   *screen = CGame->RequestScreen();
  
  // Build the army list.
  state->army_PlayerUnitsList = screen->NewButtonBox(25,100,200,375,"lstparts",0,0,"");
  for( int i = 0; i < state->teams[data->thisTeam]->GetSizeofAvailable(); ++i)
  {
  char *s = new char[state->teams[data->thisTeam]->GetUnit(i)->Name().size() + 1];
  
    sprintf(s,"%s",state->teams[data->thisTeam]->GetUnit(i)->Name().c_str());
    screen->NewGroupedButton(state->army_PlayerUnitsList,"lstparts",1 + state->teams[data->thisTeam]->GetUnit(i)->Mech()->kind,kArmyListBiasLo + i,s);
    delete[] s;
  }
  
  // Show the mission briefing.
std::ifstream  file(nsl::stformat("data/text/%s_brief.txt",data->level.c_str()).c_str());
std::string    text;
  
  file.seekg(0,ios_base::end);
int sz = file.tellg();
file.seekg(0,ios_base::beg);
char *buffer = new char[sz + 1];

  memset(buffer,0,sz + 1);
  file.read(buffer,1000);//FIXME force only the first 550 of the file, due to wrapping bug
  text = buffer;
  file.close();
  delete[] buffer;
  
  //state->army_Briefing = new CText(text,14,"Terminal");
  //state->army_Briefing = new UIText();
  //state->army_Briefing->AddText();
  
  //state->army_Briefing->SetAbsPos(400,100);
  //state->army_Briefing->SetAbsSize(400,375);
  //state->army_Briefing->FullText->SetColor4f(0.3f,0.3f,0.3f,1.0f);
  //CGame->RequestScreen()->NewText(400,50,400,375,0,text.c_str());
  //Here to prevent crashing on start
  //Only need either single line above line below lines
  state->army_Briefing = new CText(text.c_str(),14,"Terminal");//To avoid crashing somewhere else, not used
  
  state->army_Briefing->SetWorldX(400);
  state->army_Briefing->SetWorldY(100);
  state->army_Briefing->SetWidth(400);
  state->army_Briefing->SetHeight(375);
  state->army_Briefing->SetZOrder(-2000);
  state->army_Briefing->SetColor4f(0.3f,0.3f,0.3f,1.0f);
  
}


void FillStoreList(nsl::stringlist &list,const std::string &path,const std::string &mask,int limit)
{
std::ifstream    tMaskFile;
nsl::stringlist  tTagList;
nsl::stringlist  tLegalList;
list.clear();
  for(unsigned int i = 0; i < CGame->RequestState()->hireUnits.size(); ++i)
    delete CGame->RequestState()->hireUnits[i];
  CGame->RequestState()->hireUnits.clear();


  // The mask file is used to make sure we don't allow things to be purchased that shouldn't
  // (for example, special map units, Jade, bad guys, &c.). Only the names in the mask file
  // are legal for purchase.
  nsl::fdenum_files(path,tTagList);
  tMaskFile.open(mask.c_str());
  while(!tMaskFile.eof())
  {
  char                       tBuffer[256];
  nsl::stringlist::iterator  tIter;
  
    // 256 is big enough; tag names cannot be more than 8 characters.
    tMaskFile.getline(tBuffer,256);
    
    // If the mask is in the tag list, add it to the legal list.
    tIter = std::find(tTagList.begin(),tTagList.end(),tBuffer);
    if(tIter != tTagList.end())
      tLegalList.push_back(tBuffer);
  }
  tMaskFile.close();
  
  // Prevent divide by zero.
  if(tLegalList.size() == 0)
    return;
  
  for(int i = 0; i < limit; ++i)
  {
    list.push_back(tLegalList[rand() % tLegalList.size()]);
    CGame->RequestState()->hireUnits.push_back(new CUnit(list[i]));
  }
}