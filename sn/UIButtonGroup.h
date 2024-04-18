/*!
	@file	UIButtonGroup.h
	@author	Eric Roberts
	@date	October 23, 2003

	@brief	Defines a base class for menu objects, needs to be
	redone so that ButtonList is a vector of pointers because
	misconception that C++ was not conceived and implemented by
	baboons...
___________________________________________________________*/

#ifndef __UIBUTTONGROUP_H_
#define __UIBUTTONGROUP_H_

#include "precompiled.h"
#include "UIPane.h"
#include "UIRadioButton.h"

class UIButtonGroup:public UIPane
{
public:
UIButtonGroup(char* spriteCollection= "chicky");
virtual ~UIButtonGroup();

void Draw(bool show, float positionx =-1, float positiony=-1);
ResponseCode Respond(iCode input, float x=BEYOND_MIN, float y=BEYOND_MIN, int vKeyCode = BEYOND_MIN );
void Move(float x, float y);//Move to this position

int currentSelected;//index of currently selected button in vector
virtual void AddButton(UIPane* button);//insert into vector

vector<UIPane*> ButtonList;

virtual void SetExtent();//Sets absolute size and position based on position of buttons contained
ResponseCode Submit();
protected:

//virtual bool Select(int index);//Selects one of the buttons in the list(and deselects the others)
virtual bool Select(int index);
};
#endif