/*!
	@file	UIScrollBar.h
	@author	Eric Roberts
	@date	February 3, 2004

	@brief	Defines a base class for menu objects
___________________________________________________________*/
#ifndef __UISCROLLBAR_H_
#define __UISCROLLBAR_H_

#include "UIPane.h"
#define FULL_BAR 6//
class UIScrollBar : public UIPane
{
public:
	UIScrollBar(UIPane* Parent);
	virtual ~UIScrollBar();

	ResponseCode Respond(iCode input, float x = BEYOND_MIN, float y = BEYOND_MIN, int vKeyCode=BEYOND_MIN);
	void Draw(bool show=true, float positionx = -1, float positiony = -1);
	bool isInside(float x, float y);

	
	
	UIPane* parent;
	CSprite* indicator;
	CSprite* up_arrow;
	CSprite* down_arrow;
	float spriteDimension;

};

#endif