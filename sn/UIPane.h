/*!
	@file	UIPane.h
	@author	Eric Roberts
	@date	October 23, 2003

	@brief	Defines a base class for menu objects
___________________________________________________________*/

#ifndef __UIPANE_H_
#define __UIPANE_H_

#define BEYOND_MIN -9999
#define BEYOND_MAX 9999

#include "precompiled.h"
#include "cSprite.h"
#include "CRect.h"//temporary
#include "CText.h"
#include "CSprite.h"
#include "CScriptableM.h"

using namespace std;//For string
//
typedef unsigned long ResponseCode;

typedef struct point //for clearer code
{
	float x;
	float y;
} size;

enum iCode{LClick, RClick, MClick, KeyPress, ScrollUp, ScrollDown};

class UIScreen;//For pointers below
class CUnit;
//
/*!
\class UIPane
Class from which menus' items will be derived
*/


class UIPane
{
public://Need copy constructor
	//UIPane();

	UIPane(const UIPane& original);
	UIPane(ResponseCode lc=0, ResponseCode rc=0, ResponseCode mc=0, ResponseCode kb=0, ResponseCode sc=0, string spriteCollection = "chicky");
	//Ought to be virtual, but is not
	~UIPane();

virtual bool Select(bool state=true);
bool SetFocus(bool setVal=true);//Sets focus to setVal, returns previous state
virtual void Draw(bool show, float positionx =-1, float positiony=-1);
nsl::point2D<float> relPosition;//Position relative to parent in pixels
nsl::point2D<float> absPosition;//Absolute screen position in pixels
size relSize;// percentage of normal size for enlarging/shrinking
size absSize;//Normal size of pane
bool isFocused;//Whether or not input will be directed at this UIPane

bool SetRelPos(float x=0, float y=0);

virtual bool SetAbsPos(float x=0, float y=0);
virtual bool SetAbsSize(float x=0, float y=0);
virtual nsl::point2D<float> GetAbsPos();

bool SetRelSize(float x=0, float y=0);
virtual ResponseCode Respond(iCode input, float x=BEYOND_MIN, float y=BEYOND_MIN, int vKeyCode = BEYOND_MIN );

virtual bool isInside(float x, float y);
CSprite* baseSprite;

ResponseCode GetLC(){return rcLeftClick;}
ResponseCode GetMC(){return rcMiddleClick;}
ResponseCode GetRC(){return rcRightClick;}
ResponseCode GetKP(){return rcKeyPress;}
ResponseCode Submit(){return rcSubmitCode;}


ResponseCode SetLC(ResponseCode newCode){return rcLeftClick = newCode;}
ResponseCode SetMC(ResponseCode newCode){return rcMiddleClick = newCode;}
ResponseCode SetRC(ResponseCode newCode){return rcRightClick = newCode;}
ResponseCode SetKC(ResponseCode newCode){return rcKeyPress = newCode;}
ResponseCode SetSC(ResponseCode newCode){return rcSubmitCode = newCode;}

CText* MenuText;
protected:
ResponseCode rcLeftClick, rcRightClick, rcMiddleClick, rcKeyPress, rcSubmitCode;//should be protected?
union //Pointer to parent, will probably become void pointer for more flexibility
{
UIPane* parentControl;
UIScreen* parentScreen;
CUnit* parentUnit;
};


long bgSequenceIndex;//Animation sequence index?
string text;//Heading, menu text, etc
};
#endif
