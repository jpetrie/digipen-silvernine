/*!
	@file	UIMenu.h
	@author	Eric Roberts
	@date	October 23, 2003

	@brief	Defines a base class for menu objects
___________________________________________________________*/

#ifndef __UIMenu_H_
#define __UIMenu_H_

#include "precompiled.h"
#include "UIPane.h"
#include "UIRadioButton.h"
#include "UIButtonGroup.h"

class UIMenu:public UIButtonGroup
{
public:
UIMenu(char* spriteCollection = "chicky");
~UIMenu();

//void Draw(bool show, float positionx =-1, float positiony=-1);
bool Select(int index);
//ResponseCode Respond(iCode input, float x=BEYOND_MIN, float y=BEYOND_MIN);
void AddButton(UIPane* button);
ResponseCode Submit();

};
#endif