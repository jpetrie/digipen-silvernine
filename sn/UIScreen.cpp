/*!
	@file	UIScreen.cpp
	@author	Eric Roberts
	@date	October 23, 2003

	@brief	Defines a base class for menu objects
___________________________________________________________*/
#include "precompiled.h"
#include "UIPane.h"
#include "UIScreen.h"
#include "UIButtonGroup.h"
#include "UIStateButton.h"
#include "UIRingMenu.h"
#include "UIButton.h"
#include "UIMenu.h"
#include "UITextMenu.h"
#include "UIText.h"
#include "UIRadioButton.h"
#include "UIRadioGroup.h"
#include "CGameEngine.h"


 float Dist(nsl::point2D<float> rhs, nsl::point2D<float> lhs);//Distance between two points
static void PaneKill(UIPane* victim);//function that calls delete on panes
/*!
  UIScreen::UIScreen
  
  @brief Default constructor for UIScreen.  Now creates a bunch of test UIButtonGroups
***************************************************************************/
UIScreen::UIScreen()
{
	//Here we load the screen from file, or not

	//CGraphicsMgr->BuildQuadTree(0,0,1000, 1000);echan
	
//	indicator = new CSprite(400,400,50,50,"chicky",true,0,5,0);
	indicator = new CRect(0,0,50,50);
	bgSprite = new CSprite(400,400,50,50,"chicky",true,0,5,0);

	indicator->SetVisible(false);
	bgSprite->SetVisible(false);
	flickMenu = 0;
	flickMode = false;

	//CSprite(
	//Show(false);
	//indicator->SetVisible(false);
	
	/*UIButtonGroup* group1 = new UIRingMenu;
	group1->SetAbsPos(500.f,500.f);
	UIButton button(nlFOURCODE('S','P','S','T'),nlFOURCODE('Q','U','I','T'),nlFOURCODE('Q','U','I','T'),nlFOURCODE('S','P','S','T'),nlFOURCODE('Q','U','I','T'),group1);
	group1->AddButton(button);
	group1->SetExtent();
	
	MenuList.push_back(group1);
	/*group1->AddButton(button);
	group1->AddButton(button);
	group1->AddButton(button);
	group1->AddButton(button);
	group1->AddButton(button);
	group1->AddButton(button);
		group1->AddButton(button);
	group1->AddButton(button);
	group1->AddButton(button);
		group1->AddButton(button);
	group1->AddButton(button);
	group1->AddButton(button);




	group1->SetExtent();
	MenuList.push_back(group1);
*/
	//Make destuctors for buttons virtual!!!
	/*UIText* text = new UIText();
<<<<<<< .mine
	//text->FullText->SetText("Ogun is the God of War, Energy and Metal Ogun keeps matter in motionOgun is the sustainer of lifeOgun lives in the knife, and with it, clears a path for man.   Ogun is the force within your computer.  Ogun is technology. Ogun is the force of gravity, the force of attraction. Ogun represents the tools that shape man,  bringing  out a person's potential, enhancing one's life. Ogun controles life and death.  Ogun is our heart beat and the final contraction during birth.  Ogun is auto accidents and gun wounds. Ogun is the warrior, hunter and farmer. Ogun is the God of loyalty and life long friendships. Ogun is the master of secrets, skills, crafts, professions and creations. Syncretization Saint Peter");
	text->FullText->SetText("UIScreen constructor, deletedddd dd ddd ddddd d me!. \n");
=======
	//text->//FullText.SetText("Ogun is the God of War, Energy and Metal Ogun keeps matter in motionOgun is the sustainer of lifeOgun lives in the knife, and with it, clears a path for man.   Ogun is the force within your computer.  Ogun is technology. Ogun is the force of gravity, the force of attraction. Ogun represents the tools that shape man,  bringing  out a person's potential, enhancing one's life. Ogun controles life and death.  Ogun is our heart beat and the final contraction during birth.  Ogun is auto accidents and gun wounds. Ogun is the warrior, hunter and farmer. Ogun is the God of loyalty and life long friendships. Ogun is the master of secrets, skills, crafts, professions and creations. Syncretization Saint Peter");
	text->//FullText.SetText("UIScreen constructor, deletedddd dd ddd ddddd d me!. \n");
>>>>>>> .r51
	text->SetAbsPos(500,300);
<<<<<<< .mine
	text->FullText->SetStartLine();
=======
	text->//FullText.SetStartLine();
>>>>>>> .r51
	//text->Draw(true);
	UIButtonGroup* group1 = new UITextMenu;
	group1->absPosition.x = 400;
	group1->absPosition.y = 400;
	UIButton* button = new UIButton (nlFOURCODE('s','t','s','p'), 0,0,0,0, group1);
	

	//button.SetRelPos(200,-200);	
	button->SetSC(nlFOURCODE('s','t','s','p'));
   //button.SetRelPos(-100, 100);
	group1->AddButton(button);
	button = new UIButton (nlFOURCODE('s','t','s','p'), 0,0,0,0, group1);
	group1->AddButton(button);
	button = new UIButton (nlFOURCODE('s','t','s','p'), 0,0,0,0, group1);
	group1->AddButton(button);
	/*group1->AddButton(button);
	group1->AddButton(button);
	group1->AddButton(button);
	group1->AddButton(button);
	group1->AddButton(button);
	
	group1->SetExtent();
	
	MenuList.push_back(text);
	
	text = new UIText();
<<<<<<< .mine
	text->FullText->SetText("UIScreen constructor, deletedddd dd ddd ddddd d me!. \n");
=======
	text->//FullText.SetText("UIScreen constructor, deletedddd dd ddd ddddd d me!. \n");
>>>>>>> .r51
	text->SetAbsPos(300,500);
	text->SetAbsSize(200,400);
<<<<<<< .mine
	text->FullText->SetStartLine();
=======
	text->//FullText.SetStartLine();
>>>>>>> .r51

	MenuList.push_back(text);
	MenuList.push_back(group1);
	
*/
	focusedControl=0;
	
}

/*!
  UIScreen::~UIScreen
  
  @brief Destructor for UIScreen.  Destroys UIPanes contained by UIScreen
***************************************************************************/
UIScreen::~UIScreen()
{
vector<UIPane*>::iterator current = MenuList.begin();
delete indicator;
while(current!=MenuList.end())
{
	PaneKill(*current);
	current++;
}
MenuList.clear();

}

/*!
  UIScreen::Show
  
  @brief Calls 'Draw' on all contained panes with argument 'show'
***************************************************************************/
void UIScreen::Show(bool show, float x, float y)//Renders screen and all menus in screen
{
  y;x;//Unused as of yet
  //Draw all panes for screen
	
	//jpetrie short circuited this to prevent crash on empty screen
	if(MenuList.empty())
	  return;
	
	vector<UIPane*>::iterator currPane = MenuList.begin();
	while(currPane != MenuList.end())
	{
		(*currPane)->Draw(show);
		
		currPane++;
	}

	/*Draw indicator*/
	//indicator->SetVisible(false);
	UIPane* focused = MenuList[focusedControl];
	if(bgSprite)
	{
	bgSprite->SetWidth(scast<float>(CConfigMgr->GetValueAsInt("gfx_resx")));
	bgSprite->SetHeight(scast<float>(CConfigMgr->GetValueAsInt("gfx_resy")));
	bgSprite->SetWorldX(scast<float>(CConfigMgr->GetValueAsInt("gfx_resx")/2));
	bgSprite->SetWorldY(scast<float>(CConfigMgr->GetValueAsInt("gfx_resy")/2));
	bgSprite->SetVisible(false);//No background
	}
	//Commented out in anticipation of making indicator appear with hover
	/*indicator->SetWorldX(focused->absPosition.x - indicator->GetWidth() - 10);
	indicator->SetWorldY(focused->absPosition.y);
	indicator->SetVisible(show);*/
  
}

/*!
  UIScreen::RespondToLClick
  
  @brief Responds to Left click
***************************************************************************/
ResponseCode UIScreen::RespondToMouseMove(float x, float y)
{

if(!flickMenu)
{
	throw std::exception("This should never happen. It is bad");
}

nsl::point2D<float> pos;
pos.x = x;
pos.y = y;
double minDistance = BEYOND_MAX;


vector<UIPane*>::iterator curr = flickMenu->ButtonList.begin();
vector<UIPane*>::iterator closest;

if(FLICK_DISTANCE <= Dist(pos, flickPoint))
{
	//Go through all of the flickMenu's buttons
	while(curr != flickMenu->ButtonList.end())
	{
		if(minDistance > Dist(pos, (*curr)->GetAbsPos() ) )
		{
			closest = curr;
			minDistance = Dist(pos, (*curr)->GetAbsPos() );
		}
	curr++;
	}
	//look for closest one, but if even that is farther than the flickPoint, leave it alone
    if(minDistance > Dist(pos, flickPoint) )
	{
		return 0;
	}
	else
	{
		flickMode=false;
		flickMenu=NULL;
		flickPoint.x = flickPoint.y = BEYOND_MAX;

		return (*closest)->GetLC();
	}
}

return 0;

}


/*!
  UIScreen::RespondToLClick
  
  @brief Responds to Left click
***************************************************************************/
ResponseCode UIScreen::RespondToLClick(float x, float y)
{

	vector<UIPane*>::reverse_iterator currPane = MenuList.rbegin();
	//vector<UIPane*>::iterator currPane = MenuList.begin();
	
	int index = (int)MenuList.size()-1;
	//int index = 0;
	ResponseCode temp =0;
	while(currPane != MenuList.rend())
	//while(currPane != MenuList.end())
	{
		if((*currPane)->isInside(x,y))//if inside
		{	

			//if pane has no left click response code
			//if(! ((*currPane)->GetLC()) )
			if(! (temp = (*currPane)->Respond(LClick, x,y)))
			{
				//SetIndicator(*currPane);
				focusedControl = index;
				return 0;//No event
			}
			
			//return (*currPane)->Respond(LClick, x, y);
			return temp;
		}
		currPane++;
		//index++;
		index--;
	}
return 0;//Nothing was clicked
}

/*!
  UIScreen::RespondToRClick
  
  @brief Responds to right click
***************************************************************************/
ResponseCode UIScreen::RespondToRClick(float x, float y)
{
	vector<UIPane*>::iterator currPane = MenuList.begin();
	while(currPane != MenuList.end())
	{
		if((*currPane)->isInside(x,y))
		{
			return (*currPane)->Respond(RClick, x,y);
		}
		currPane++;
	}
return 0;//Nothing was clicked

}
/*!
  UIScreen::RespondToScrollUp
  
  @brief Responds to right click
***************************************************************************/
ResponseCode UIScreen::RespondToWheelUp()
{
	MenuList[focusedControl]->Respond(ScrollUp);
	return 0;
}

int UIScreen::NextPane(int current)
{
	if(current = -1)//If just incrementing
		current = focusedControl;//Use internal
	
	current++;
	focusedControl = (current > scast<int>((MenuList.size()-1)) ) ? 0 : current;
	return focusedControl;
}

int UIScreen::PrevPane(int current)
{
	if(current = -1)//If just incrementing
		current = focusedControl;//Use internal
	
	current--;
	focusedControl = (current < 0) ? scast<int>((MenuList.size()-1)) : current;
	return focusedControl;
}
/*!
  PaneKill
  
  @brief calls delete on argument
***************************************************************************/
void PaneKill(UIPane* victim)//function that calls delete on panes
{
delete victim;
}


/*void UIScreen::NewButton(float x,float y, int seq, int code, char* text)//Adds generic button to screen
{
  UIButton *tButton = new UIButton(code,0,0,0,0,0);
	
  tButton->baseSprite->SetSequence(seq,0);
  tButton->SetAbsPos(x,y);
  //tButton->Draw(true);

  MenuList.push_back(tButton);
}*/

int UIScreen::NewButton(float x,float y, char* spriteCollection, int seq, int code, char* text)//Adds generic button to screen
{
  UIButton *tButton = new UIButton(code,seq,0,0,0, spriteCollection, 0);
  //To proper sequence
  //tButton->baseSprite->SetSequence(seq,0);
  
  //re-size button to size of this sequence
  //Should add to constructor UIPane? probably
  tButton->SetAbsSize(tButton->baseSprite->GetWidth(), tButton->baseSprite->GetHeight());
  
  tButton->SetAbsPos(x,y);
  tButton->MenuText->SetText(text);
  
  CGame->RequestScreen()->AddToScreen(tButton);
  tButton->Draw(true);
  return (int)MenuList.size()-1;//Returns 'name' of button, its position in the MenuList 
}

int UIScreen::NewButtonColSize(float x,float y, char* spriteCollection, int seq, int code, char* text, float colWidth, float colHeight,float hitOrX, float hitOrY)//Adds generic button to screen
{
	UIButton *tButton = new UIButton(code,seq,0,0,0, spriteCollection, 0);
  //To proper sequence
  //tButton->baseSprite->SetSequence(seq,0);
  
  //re-size button to size of this sequence
  //Should add to constructor UIPane? probably
  tButton->SetAbsSize(tButton->baseSprite->GetWidth(), tButton->baseSprite->GetHeight());
  
  tButton->SetAbsPos(x,y);
  tButton->MenuText->SetText(text);
  //MenuList.push_back(tButton);
  CGame->RequestScreen()->AddToScreen(tButton);
  tButton->SetHitSize(colWidth, colHeight);
  tButton->SetHitOrigin(hitOrX, hitOrY);
  tButton->Draw(true);
  
  return (int)MenuList.size()-1;//Returns 'name' of button, its position in the MenuList 		 
}

int UIScreen::NewGroupedButton(int group, char* spriteCollection, int seq, int code, char* text, float height)
{
	//Create new button
	UIButton* temp = new UIButton(code,seq,0,0,0,spriteCollection, 0);
	temp->MenuText->SetText(text);
	if(height > 1)
	temp->SetAbsSize(temp->absSize.x, height);
	//Add to appropriate list
	((UIButtonGroup*)(MenuList[group]))->AddButton(temp);
	
	
	//Redraw screen
	CGame->RequestScreen()->Show(true);

	//What was this return value for again?
	return (int)((UIButtonGroup*)(MenuList[group]))->ButtonList.size()-1;
}

int UIScreen::NewText(float x,float y, float w, float h, int seq, const char* text, int fontSize)
{
  UIText *T = new UIText(text, fontSize);
  /*T->SetAbsPos(x,y);
  T->SetAbsSize(w,h);
  T->FullText->SetHeight(h);
  T->FullText->SetWidth(w);*/
  /*T->FullText->SetWorldX(400);
  T->FullText->SetWorldY(100);
  T->FullText->SetWidth(400);
  T->FullText->SetHeight(375);
  T->FullText->SetZOrder(-2000);
  T->FullText->SetColor4f(0.9f,0.3f,0.3f,1.0f);*/
  T->SetAbsPos(x,y);
  T->SetAbsSize(w,h);
  
  T->FullText->SetZOrder(-2000);
  T->FullText->SetColor4f(0.3f,0.3f,0.3f,1.0f);
  
 // T->baseSprite->SetSequence(seq,0);
  

  //T->//FullText.SetText(text);
//  T->Draw(true);
  //MenuList.push_back(T);
  CGame->RequestScreen()->AddToScreen(T);
  T->Draw(true);T->FullText;
  //T->MenuText->SetText(text);
  return (int)MenuList.size()-1;//Returns 'name' of button, its position in the MenuList 
}


void UIScreen::ClearScreen()
{
	vector<UIPane*>::iterator curr = MenuList.begin();
	while(curr != MenuList.end())
	{
		
		delete (*curr);
		++curr;
	}
	MenuList.clear();
	//Clean other stuff
	focusedControl=0;
	//delete indicator;
	
}
/*!
@brief Adds pane to screen, returns screens place in menulist
@param UIPane pointer to be added
*/
int UIScreen::AddToScreen(UIPane* newButton)
{
	
	newButton->baseSprite->SetZOrder(-.01f*MenuList.size()+.02f);
	MenuList.push_back(newButton);
	Show(false);//Positions everything correctly and notwhat
	return (int)MenuList.size()-1;
}

/*!
@brief Remove pane from screen
@param toDie UIPane to be removed
*/
int UIScreen::RemoveFromScreen(UIPane* toDie)//Removes a button
{
	vector<UIPane*>::iterator curr = MenuList.begin();
	while(curr != MenuList.end())
	{
		if(toDie == (*curr))
		{
			delete (*curr);
			MenuList.erase(curr);
			break;
		}
		curr++;
	}
	/*delete toDie;
	remove(MenuList.begin(), MenuList.end(), toDie);*/
	
		
	return (int)MenuList.size();
}

int UIScreen::NewButtonBox(float x,float y, float width, float height, char* spriteCollection, int seq, int code, char* text)
{
  UITextMenu *tButton = new UITextMenu(spriteCollection);
	
  tButton->baseSprite->SetSequence(seq,0);
  tButton->SetAbsPos(x,y);
  tButton->SetAbsSize(width,height);
  tButton->MenuText->SetText(text);
  
  //MenuList.push_back(tButton);
  CGame->RequestScreen()->AddToScreen(tButton);
  tButton->Draw(true);

  
  return (int)MenuList.size()-1;//Returns 'name' of button, its position in the MenuList 
}


 UIPane* UIScreen::GetButton(int index)
 {
	 return MenuList[index];
 }

 
/*Also New Group, TextMenu, what not
EXPORT void NewButton(float x,float y,float w,float h,int seq,int code);
void NewButton(float x,float y,float w,float h,int seq,int code)
{
UIButton *tButton = new UIButton(code,0,0,0,0,0);

  tButton->baseSprite->SetSequence(seq,0);
  tButton->SetAbsPos(x,y);
  tButton->absSize.x = w;
  tButton->absSize.y = h;
  tButton->Draw(true);
  gUIElems.push_back(tButton);

  
  gSession->menuShell.CurrentScreen->MenuList.push_back(tButton);
}*/

float Dist(nsl::point2D<float> rhs, nsl::point2D<float> lhs)//Distance between two points
{
	return (float) sqrt((pow(lhs.x-rhs.x,2)+pow(lhs.y -rhs.y,2)));
}