/*!
	@file	UITextMenu.h
	@author	Eric Roberts
	@date	October 23, 2003

	@brief	Defines a base class for menu objects
___________________________________________________________*/

#ifndef __UITEXTMENU_H_
#define __UITEXTMENU_H_

#include "precompiled.h"
#include "UIMenu.h"
#include "UIScrollBar.h"


class UITextMenu:public UIMenu
{
public:
UITextMenu(char* spriteCollection = "ui_mmenu",float foldedX = 200, float foldedY=400);
virtual ~UITextMenu();
bool isFolded; //is menu showing only heading (not all of its options)
void Fold(bool state= true);//changes state of menu to 'state'
void Draw(bool show, float positionx=-1, float positiony=-1);
void AddButton(UIPane* button);


ResponseCode Respond(iCode input, float x=BEYOND_MIN, float y=BEYOND_MIN, int vKeyCode=BEYOND_MIN );
bool isInside(float x, float y);

size foldedSize;

//Scrolling information
int pageSize;//Number of buttons per page
int currentPage;//0 based
int totalPages;//self explanatory
UIScrollBar* scroll;

};
#endif