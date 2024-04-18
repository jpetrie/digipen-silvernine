/*!
	@file	UIButtonGroup.h
	@author	Eric Roberts
	@date	October 23, 2003

	@brief	Defines a base class for menu objects
___________________________________________________________*/
#include "precompiled.h"
#include "UIButtonGroup.h"


/*!
	UIButtonGroup::UIButtonGroup

	@brief	Position defaults to (600,600)
______________________________________________________________________________*/
UIButtonGroup::UIButtonGroup(char* spriteCollection) :UIPane(0,0,0,0,0,spriteCollection)
{
//absPosition.x = absPosition.y = 600;
}

/*!
	UIButtonGroup::UIButtonGroup

	@brief	Does nothing
______________________________________________________________________________*/
UIButtonGroup::~UIButtonGroup()
{
	vector<UIPane*>::iterator curr = ButtonList.begin();
	while(curr != ButtonList.end())
	{
		delete (*curr);
		curr++;
	}
}

/*!
	UIButtonGroup::Draw

	@brief	Draws all of contained buttons and own buttons, last 2 arguments ignored
______________________________________________________________________________*/
void UIButtonGroup::Draw(bool show, float positionx, float positiony)
{
	vector<UIPane*>::iterator curr;
	curr = ButtonList.begin();
	
	
	while(curr != ButtonList.end())
	{
		//should set absolute positions based on relative positions
		(*curr)->SetAbsPos(absPosition.x+(*curr)->relPosition.x,absPosition.y+(*curr)->relPosition.y);
		(*curr)->Draw(show);
		curr++;
	}

	positionx;positiony;//unused as of yet
//	baseSprite->SetBorderColor(.03f,.7f,.9f,.5f);
//	baseSprite->SetInteriorColor(.6f,.9f,.0f,.7f);
	positiony = baseSprite->GetZOrder();//preserve zOrder
	
	baseSprite->SetVisible(false);
	baseSprite->SetWorldX(absPosition.x);
	baseSprite->SetWorldY(absPosition.y);
	baseSprite->SetWidth(absSize.x);
	baseSprite->SetHeight(absSize.y);

	baseSprite->SetZOrder(positiony);//preserve zOrder
	
}

/*!
	UIButtonGroup::SetExtent

	@brief	Sets proper size of baseSprite according to the buttons contained.
	Must call after inserting all buttons, otherwise active shell will most likely
	not check for contained buttons
______________________________________________________________________________*/
void UIButtonGroup::SetExtent()//Sets absolute size and position based on position of buttons contained
{
    float left=BEYOND_MAX, right=BEYOND_MIN, top=BEYOND_MIN, bottom=BEYOND_MAX;

	vector<UIPane*>::iterator curr;
	curr = ButtonList.begin();
	while(curr != ButtonList.end())
	{
		if((absPosition.x + (*curr)->relPosition.x)<left)
		{
			left = absPosition.x +(*curr)->relPosition.x;
		}

		if((absPosition.x + (*curr)->relPosition.x+(*curr)->absSize.x)>right)
		{
			right = absPosition.x +(*curr)->absSize.x+(*curr)->relPosition.x;
		}

		if( (absPosition.y + (*curr)->relPosition.y)<bottom)
		{
			bottom = absPosition.y + (*curr)->relPosition.y;//-(*curr)->absSize.y;
		}

		if(((*curr)->relPosition.y+absPosition.y+(*curr)->absSize.y)>top)
		{
			top = absPosition.y +(*curr)->relPosition.y+(*curr)->absSize.y;
		}
    
	curr++;
	}
	
	absSize.x = fabs((right-left));
	//absPosition.x = left;//-absSize.x/2;

	absSize.y = fabs((top-bottom));
	//absPosition.y = bottom;// - absSize.y/2;
	
	curr=ButtonList.begin();
	while(curr !=ButtonList.end())
	{
		//curr->relPosition.x -= absSize.x/2;
		//curr->relPosition.y -= absSize.y/2;
		curr++;

	}

	
}

/*!
	UIButtonGroup::Select

	@brief	Selects one of the buttons in the list
______________________________________________________________________________*/
bool UIButtonGroup::Select(int index)
{
	if(index == currentSelected)//Skips selection for already done things
	{
		return false;
	}

	ButtonList[currentSelected]->Select(false);
	ButtonList[index]->Select(true);
	return true;
}

/*!
  UIButtonGroup::AddButton
  
      
  @brief Adds button to group, just adds it to bottom
***************************************************************************/
void UIButtonGroup::AddButton(UIPane* button)//insert into vector, re-set extent
{

/*	
	button.absPosition.x = absPosition.x + button.relPosition.x;
	button.absPosition.y = absPosition.y + button.relPosition.y;
	
	ButtonList.push_back(button);
*/
	int lastButton;
	if((lastButton = scast<int>(ButtonList.size())) == 0)
	{
		button->relPosition.x = 0;
		button->relPosition.y = 0;
	}
	else
	{
		lastButton-=1;
		button->relPosition.x = ButtonList[lastButton]->relPosition.x;
		button->relPosition.y = ButtonList[lastButton]->relPosition.y+ButtonList[lastButton]->absSize.y;
	}
	ButtonList.push_back(button);
	//SetExtent();
	
}


/*!
  UIButtonGroup::Respond
  
  @brief Returns response code of some internal button (in which point (x,y) lies
  or 0 if (x,y) is nothing
***************************************************************************/
ResponseCode UIButtonGroup::Respond(iCode input, float x, float y, int vKeyCode)
{
	int index = scast<int>(ButtonList.size());
	
	while(--index>-1)
	{
		if(ButtonList[index]->isInside(x,y))
		{
			//Select(index);
			 //MessageBox(0,"Happiness","is Happy",MB_OK); what the hell
			return ButtonList[index]->Respond(input);
		}
	}
	return 0;
}

/*!
  UIButtonGroup::Move
  
  @brief Moves button group to world point (x,y) along with buttons contained
***************************************************************************/
void UIButtonGroup::Move(float x,float y)
{
 absPosition.x = x;
 absPosition.y = y;
 SetExtent();
 Draw(true);
}

