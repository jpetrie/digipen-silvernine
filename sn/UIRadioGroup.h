/*!
	@file	UIRadioGroup.h
	@author	Eric Roberts
	@date	November 13, 2003

	@brief	Defines a button object
___________________________________________________________*/
#ifndef __UIRADIOGROUP_H_
#define __UIRADIOGROUP_H_
#include "UIPane.h"
#include "UIRadioButton.h"
#include "UIButtonGroup.h"

class UIRadioGroup: public UIButtonGroup
{
public:
UIRadioGroup();
~UIRadioGroup();

ResponseCode Respond(iCode input, float x=BEYOND_MIN, float y=BEYOND_MIN, int vKeyCode=BEYOND_MIN);
bool Select(int index);
//vector<UIRadioButton> ButtonList;
//void AddButton(UIPane& button);//insert into vector
};

/*
ResponseCode Respond(iCode input, float x=BEYOND_MIN, float y=BEYOND_MIN );

int currentSelected;//index of currently selected button in vector

ResponseCode Submit();

//virtual bool Select(int index);//Selects one of the buttons in the list(and deselects the others)
*/

#endif