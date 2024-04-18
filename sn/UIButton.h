/*!
	@file	UIButton.h
	@author	Eric Roberts
	@date	November 13, 2003

	@brief	Defines a button object
___________________________________________________________*/
#ifndef  __UIBUTTON_H_
#define __UIBUTTON_H_

#include "precompiled.h"
#include "UIPane.h"

class UIButton: public UIPane
{
public:
	UIButton(ResponseCode lc=0, ResponseCode rc=0, ResponseCode mc=0, ResponseCode kb=0, ResponseCode sc = 0, char* spriteCollection ="chicky",UIPane* parent=0);
	//UIButton(ResponseCode, ResponseCode, ResponseCode, ResponseCode, ResponseCode, char*, UIPane*);
	UIButton::UIButton(const UIButton& original);
	//void Draw(bool show, float positionx =-1, float positiony = -1);
	
	

	
	size hitSize;
	nsl::point2D<float> hitOrigin;
	void SetHitSize(float x, float y);
	void SetHitOrigin(float x, float y);
	
	//Redefined for buttons to account for hitSize/origin
	bool SetAbsPos(float x=0, float y=0);
	bool SetAbsSize(float x=0, float y=0);

	bool UIButton::isInside(float x, float y);

	
	virtual ~UIButton();

};

#endif