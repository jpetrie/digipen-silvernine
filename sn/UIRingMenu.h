/*!
	@file	UIRingMenu.h
	@author	Eric Roberts
	@date	October 23, 2003

	@brief	Defines a base class for menu objects
___________________________________________________________*/

#ifndef __UIRINGMENU_H_
#define __UIRINGMENU_H_

#include "precompiled.h"
#include "UIPane.h"
#include "UIButtonGroup.h"

class UIRingMenu: public UIButtonGroup
{
public:
	UIRingMenu(float positionx = 500, float positiony = 500, float width = 100, float height=100);
	virtual ~UIRingMenu();
   void AddButton(UIPane* button);//insert into vector
   void SetExtent();
   //void Draw(bool show, float positionx =-1, float positiony=-1);
   

};
#endif