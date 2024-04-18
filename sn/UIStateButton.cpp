/*!
	@file	UIStateButton.cpp
	@author	Eric Roberts
	@date	November 14, 2003

	@brief	Defines a button object
___________________________________________________________*/
#include "UIStateButton.h"

/*!
  UIStateButton::UIStateButton
  
  @brief Default constructor.  Sets size
***************************************************************************/
UIStateButton::UIStateButton(ResponseCode SC, UIPane* parent):UIPane(0,0,0,0, SC)
{
parentControl  = parent;
//absPosition.x = absPosition.y = rand()%300;
//relPosition.y = relPosition.x = rand()%300;
//absSize.y = absSize.x = rand()%120;
}

/*!
  UIStateButton::~UIStateButton
  
  @brief Destructor of UIStateButton. Does nothing
***************************************************************************/
UIStateButton::~UIStateButton()
{
	
}

/*!
  UIStateButton::Select
  
  @brief Changes pisSelected and animation sequence index
***************************************************************************/
bool UIStateButton::Select(bool state)
{
	bool retval = pisSelected;
	pisSelected = state;
	bgSequenceIndex=(pisSelected)?SelectedSeqIndex:NonSelectedSeqIndex;
	return retval;
}

/*!
  UIStateButton::MakeSelectable
  
  @brief Changes pisSelectable and animation sequence index
***************************************************************************/
bool UIStateButton::MakeSelectable(bool state)
{
	bool retval = pisSelectable;
	pisSelectable = state;
	bgSequenceIndex = (pisSelectable)?NonSelectedSeqIndex:UnSelectableSeqIndex;
	return retval;
}