/*!
	@file	UIText.h
	@author	Eric Roberts
	@date	October 23, 2003

	@brief	Defines a base class for menu objects
___________________________________________________________*/
#ifndef __UITEXT_H_
#define __UITEXT_H_

#include "UIPane.h"
#include "UIScrollBar.h"

class UIText : public UIPane
{
public:
	UIText(const char* text = "Nancy dancy", int fontSize = 16);
	virtual ~UIText();

	CText *FullText;


	int currentLine;
	bool Select(bool state = true);
	string textString;

	const char* GetText();
	void AddText(const char*);
	void Clear();

	ResponseCode Respond(iCode input, float x = BEYOND_MIN, float y = BEYOND_MIN, int vKeyCode=BEYOND_MIN);
	void Draw(bool show=true, float positionx = -1, float positiony = -1);
	bool isInside(float x, float y);
	int currentPage;
	int totalPages;
	
	
protected:
	//UIScrollBar* scroll;


friend UIScrollBar;
};

#endif