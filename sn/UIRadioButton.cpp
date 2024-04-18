/*!
	@file	UIRadioButton.h
	@author	Eric Roberts
	@date	November 13, 2003

	@brief	Defines a button object
___________________________________________________________*/
#include "UIRadioButton.h"

/*!
  UIRadioButton::UIRadioButton
  
  @brief Default constructor for UIRadioButton.  Does nothing
***************************************************************************/
UIRadioButton::UIRadioButton()
{
}

/*!
  UIRadioButton::UIRadioButton
  
  @brief Constructor for UIRadioButton. Sets submitCode and parent through UIStateButton constructor
***************************************************************************/
UIRadioButton::UIRadioButton(ResponseCode rcSubmitCode, UIPane* parent):UIStateButton(rcSubmitCode, parent)
{
}

/*!
  UIRadioButton::UIRadioButton
  
  @brief Copy constructor.  Creates new baseSprite
***************************************************************************/
UIRadioButton::UIRadioButton(const UIRadioButton& original)
{
relPosition = original.relPosition;
absPosition = original.absPosition;//Absolute screen position in pixels
relSize= original.relSize;// percentage of normal size for enlarging/shrinking
absSize= original.absSize;//Normal size of pane
isFocused = original.isFocused;//Whether or not input will be directed at this UIPane

//baseSprite = new CRect(0,0,0,0);//change to CSprite
(*baseSprite) = (*original.baseSprite);

rcLeftClick = original.rcLeftClick;
rcRightClick = original.rcRightClick;
rcMiddleClick = original.rcMiddleClick;
rcKeyPress = original.rcKeyPress;
rcSubmitCode = original.rcSubmitCode;
}

/*
UIRadioButton::UIRadioButton(ResponseCode rcSubmitCode, UIPane* parent):UIPane(0,0,0,0)
{
parentControl  = parent;
}

UIRadioButton::~UIRadioButton()
{
	


}*/

/*!
  UIRadioButton::Select
  
  @brief Changes pisSelected and Sequence index
***************************************************************************/
bool UIRadioButton::Select(bool state)
{
	bool retval = pisSelected;
	pisSelected = state;
	bgSequenceIndex=(pisSelected)?SelectedSeqIndex:NonSelectedSeqIndex;

	/*Temporary*/
	if(pisSelected)
	retval;//baseSprite->SetInteriorColor(.5f,.9f,.3f,1.f);
	else
	retval;//baseSprite->SetInteriorColor(.9f,.9f,.9f,.5f);
	/*Temporary*/
	return retval;//Return old value
}
/*
bool UIRadioButton::MakeSelectable(bool state=true)
{
	isSelectable = state;
	bgSequenceIndex = (isSelectable)?NonSelectedSeqIndex:UnSelectedSeqIndex;
}*/