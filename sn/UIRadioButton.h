/*!
	@file	UIRadioButton.h
	@author	Eric Roberts
	@date	November 13, 2003

	@brief	Defines a button object
___________________________________________________________*/
#ifndef __UIRADIOBUTTON_H_
#define __UIRADIOBUTTON_H_
#include "UIPane.h"
#include "UIStateButton.h"

class UIRadioButton: public UIStateButton
{
public:
	UIRadioButton();
	UIRadioButton(ResponseCode rcSubmitCode, UIPane* parent=NULL);
	UIRadioButton(const UIRadioButton& original);
	//Decided no need for virtual destuctor
	bool Select(bool state= true);
	
};

/*
class UIRadioButton: public UIPane
{
public:
	bool isSelected(){return isSelected;}
	bool isSelectable(){return isSelectable;}

	bool Select(bool state=true);
	bool MakeSelectable(bool state=true);

	ResponseCode Submit(){return rcSubmitCode;}
	
private:
	bool isSelected;
	bool isSelectable;
	
	//Response code for when RadioGroup is 'Submitted'
	ResponseCode rcSubmitCode;
	
	//Change state and animation			
	long SelectedSeqIndex;
	long NonSelectedSeqIndex;
	long UnselectableSeqIndex;
}*/
#endif