/*!
	@file	UIRadioGroup.h
	@author	Eric Roberts
	@date	November 13, 2003

	@brief	Defines a button object
___________________________________________________________*/
#include "UIRadioGroup.h"

/*!
  UIRadioGroup::UIRadioGroup
  
  @brief Default constructor for UIRadioGroup.  Initialises currentSelected to 0
***************************************************************************/
UIRadioGroup::UIRadioGroup()
{
currentSelected = 0;
}

/*!
  UIRadioGroup::~UIRadioButton
  
  @brief Destructor for UIRadioGroup. Does nothing
***************************************************************************/
UIRadioGroup::~UIRadioGroup()
{
}

/*!
  UIRadioGroup::Respond
  
  @brief 'Selects' contained button which contains point (x,y), does not call 'Respond'
  with it
***************************************************************************/
ResponseCode UIRadioGroup::Respond(iCode input, float x, float y, int vKeyCode)
{
	input;//unused
	int index = scast<int>(ButtonList.size());
	
	while(--index>-1)
	{
		if(ButtonList[index]->isInside(x,y))
		{
			Select(index);
			//return ButtonList[index].Respond(input);
		}
	}
	return 0;
}

/*!
  UIRadioGroup::Select
  
  @brief Deselects currentSelected button, selects button indexed by 'index'
***************************************************************************/
bool UIRadioGroup::Select(int index)
{
	if(index == currentSelected)//Skips selection for already done things
	{
		return false;
	}

	ButtonList[currentSelected]->Select(false);
	ButtonList[index]->Select(true);

	//This was superugly because was not using pointers in ButtonList
	//(*((UIRadioButton*)(&(ButtonList[currentSelected])))).Select(false); //pcha
	//(*((UIRadioButton*)(&(ButtonList[index])))).Select(true);
	
	//ButtonList[currentSelected].Select(false);
	
	currentSelected = index;
	return true;
}

/*int lastButton;
	if((lastButton = ButtonList.size()) == 0)
	{
		button.relPosition.x = 0;
		button.relPosition.y = -1*foldedSize.y;
	}
	else
	{
		lastButton-=1;
		button.relPosition.x = ButtonList[lastButton].relPosition.x;
		button.relPosition.y = ButtonList[lastButton].relPosition.y-ButtonList[lastButton].absSize.y;
	}
	ButtonList.push_back(button);
	//SetExtent();*/