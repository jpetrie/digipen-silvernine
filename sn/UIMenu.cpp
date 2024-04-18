/*!
	@file	UIMenu.h
	@author	Eric Roberts
	@date	October 23, 2003

	@brief	Defines a base class for menu objects
___________________________________________________________*/
#include "precompiled.h"
#include "UIMenu.h"

/*!
  UIMenu::UIMenu
  
  @brief Does nothing
***************************************************************************/
UIMenu::UIMenu(char* spriteCollection):UIButtonGroup(spriteCollection)
{

}

/*!
  UIMenu::~UIMenu
  
  @brief Does nothing
***************************************************************************/
UIMenu::~UIMenu()
{

}

/*void UIMenu::Draw(bool show, float positionx, float positiony)
{
	vector<UIPane>::iterator curr;
	curr = ButtonList.begin();

	while(curr != ButtonList.end())
	{
		curr->Draw(show);
		curr++;
	}

	positionx;positiony;//unused as of yet
	baseSprite->SetBorderColor(.03f,.7f,.9f,.5f);
	baseSprite->SetInteriorColor(.9f,.9f,.4f,.1f);
	baseSprite->SetVisible(show);
	baseSprite->SetWorldX(absPosition.x);
	baseSprite->SetWorldY(absPosition.y);
	baseSprite->SetWidth(absSize.x);
	baseSprite->SetHeight(absSize.y);
}*/
/*
void UIMenu::SetExtent()//Sets absolute size and position based on position of buttons contained
{
	float left=BEYOND_MAX, right=BEYOND_MIN, top=BEYOND_MIN, bottom=BEYOND_MAX;

	vector<UIPane>::iterator curr;
	curr = ButtonList.begin();
	while(curr != ButtonList.end())
	{
		if(curr->absPosition.x<left)
		{
			left = curr->absPosition.x;
		}

		if((curr->absPosition.x+curr->absSize.x)>right)
		{
			right = curr->absSize.x+curr->absPosition.x;
		}

		if(curr->absPosition.y<bottom)
		{
			bottom = curr->absPosition.y;
		}

		if((curr->absPosition.y+curr->absSize.y)>top)
		{
			right = curr->absSize.y+curr->absPosition.y;
		}
    
	curr++;
	}
	absPosition.x = left;
	absSize.x = right-left;
	absPosition.y = top;
	absSize.x = top-bottom;
}*/



/*!
  UIMenu::Select
  
  @brief Selects one of the buttons in the list
  Different completely from UIPane inherited 'Select'
***************************************************************************/
bool UIMenu::Select(int index)
{
	if(index == currentSelected)//Skips selection for already done things
	{
		return false;
	}

/*	ButtonList[currentSelected].Select(false);
	ButtonList[index].Select(true);*/
	return true;
}

/*!
  UIMenu::AddButton
  
  @brief Adds buttons on top of rest
***************************************************************************/
void UIMenu::AddButton(UIPane* button)//insert into vector
{
	//Set relative position based on how many are in the list, then add button
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
  UIMenu::Submit
  
  @brief returns SubmitCode of contained button that is currently selected
***************************************************************************/
ResponseCode UIMenu::Submit()
{
	return ButtonList[currentSelected]->Submit();
}
