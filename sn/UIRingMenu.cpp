/*!
	@file	UIRingMenu.cpp
	@author	Eric Roberts
	@date	October 23, 2003

	@brief	Defines a base class for menu objects
___________________________________________________________*/
#include "precompiled.h"
#include "UIRingMenu.h"

const float two_pi = 6.283185307f;
const float bias = two_pi/4.f;//To start at top instead of right

/*!
  UIRingMenu::UIRingMenu
  
  @brief Default constructor for RingMenu.  Sets default size and position
***************************************************************************/
UIRingMenu::UIRingMenu(float positionx, float positiony, float width, float height)
{
	absPosition.x = positionx;
	absPosition.y = positiony;
	//absSize.x  = width+200;
	//absSize.y = height+200;
}


/*!
  UIRingMenu::AddButton
  
  @brief Resets all buttons so that they are arranged in circular pattern
***************************************************************************/
void UIRingMenu::AddButton(UIPane* button)
{
	ButtonList.push_back(button);
	int i = scast<int>(ButtonList.size() - 1);
	float total = (float)i+1;//will never be zero
	float current;
	float radius = absSize.x/2;// - button.absSize.x/2.f;//could have used y, doesn't matter

	for(;i>-1;i--)
	{
		current = (float)i;
		ButtonList[i]->relPosition.x = (cos(((current/total)*two_pi+bias))*radius)-ButtonList[i]->absSize.x/2.f;//pcha
		//ButtonList[i].absPosition.x = ButtonList[i].relPosition.x+ absPosition.x;

		ButtonList[i]->relPosition.y = (sin(((current/total)*two_pi+bias))*radius)-ButtonList[i]->absSize.y/2.f;//pcha
		//ButtonList[i].absPosition.y = ButtonList[i].relPosition.y + absPosition.y;
	}

}
/*!
	UIRingMenu::SetExtent

	@brief	Sets proper size of baseSprite according to the buttons contained.
	Must call after inserting all buttons, otherwise active shell will most likely
	not check for contained buttons
______________________________________________________________________________*/
void UIRingMenu::SetExtent()//Sets absolute size and position based on position of buttons contained
{
    float left=BEYOND_MAX, right=BEYOND_MIN, top=BEYOND_MIN, bottom=BEYOND_MAX;

	vector<UIPane*>::iterator curr;//pcha
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
			bottom = absPosition.y + (*curr)->relPosition.y;//-curr->absSize.y;
		}

		if(((*curr)->relPosition.y+absPosition.y+(*curr)->absSize.y)>top)
		{
			top = absPosition.y +(*curr)->relPosition.y+(*curr)->absSize.y;
		}
    
	curr++;
	}
	
	absSize.x = fabs((right-left));
	//absPosition.x = left - absSize.x/2.f;

	absSize.y = fabs((top-bottom));
	//absPosition.y = bottom - absSize.y/2.f;
	
	curr=ButtonList.begin();
	while(curr != ButtonList.end())
	{
		//curr->relPosition.x += absSize.x/2.f;
		//curr->relPosition.y += absSize.y/2.f;
		curr++;
	}

	
}

UIRingMenu::~UIRingMenu()
{
	return;
}
