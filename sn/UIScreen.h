/*!
	@file	UIScreen.h
	@author	Eric Roberts
	@date	October 23, 2003

	@brief	Defines a base class for menu objects
___________________________________________________________*/
#ifndef __UISCREEN_H_
#define __UISCREEN_H_

const float FLICK_DISTANCE = 40.f;//How much to move the mouse before it is considered a flick
#include "precompiled.h"
#include "CSprite.h"//For drawing
#include "CEvent.h"
#include "UIPane.h"//UIScreens contain these
#include "CScriptableM.h"
#include "UIRingMenu.h"

//#include "precompiled.h"
/*!
\class UIScreen
Class encapsulating menu screens (as opposed to just menus)
Also perhaps class from which Army management screens will derive
*/

class UIScreen: public CScriptableM<UIScreen>
{
public:

	UIScreen();
	~UIScreen();
	
	point absPosition;
	EXPORT void Show(bool show, float x=0, float y=0);//Renders screen and all menus in screen or hides them
	CEvent::ID UIScreenName;//For identifying this screen to the shell

	int focusedControl;//Control(pane) to receive undirected input
	bool SetFocus(bool setVal=true);//Sets focus to setVal, returns previous state
	bool isFocused;//
	int NextPane(int current = -1);
	int PrevPane(int current = -1);

	ResponseCode RespondToLClick(float x, float y);
	ResponseCode RespondToRClick(float x, float y);
	ResponseCode RespondToWheelUp();
	ResponseCode RespondToWheelDn();
	ResponseCode RespondToKeyStroke();
	ResponseCode RespondToMouseMove(float x, float y);

	CSprite* bgSprite;
	CRect* indicator;

	EXPORT int NewButton(float x,float y, char* spriteCollection, int seq, int code, char* text);//Adds generic button to screen
	EXPORT int NewGroupedButton(int group, char* spriteCollection, int seq, int code, char* text, float height = BEYOND_MIN);//Adds generic button to specified group
	EXPORT int NewText(float x,float y, float w, float h, int seq, const char* text, int fontSize = 16);//Adds generic button to screen
	EXPORT void ClearScreen();//Clears the screen

	//temporary
	EXPORT int NewButtonColSize(float x,float y, char* spriteCollection, int seq, int code, char* text, float colWidth, float colHeight, float hitOrX=0, float hitOrY=0);
	//EXPORT int NewButtonBox(float x,float y, char* spriteCollection, int seq, int code, char* text);
	EXPORT int NewButtonBox(float x,float y, float width, float height, char* spriteCollection, int seq, int code, char* text);
	UIPane* GetButton(int index);
	int AddToScreen(UIPane* newButton);//Adds button to the screen
	int RemoveFromScreen(UIPane* toDie);//Removes a button

	vector<UIPane*> MenuList;//List of menus in screen

	bool flickMode;//Ready to flick
	nsl::point2D<float> flickPoint;//From whence we came
	UIRingMenu* flickMenu;
	protected:
	
	
	long bgSequenceIndex;//Animation sequence index?
	string text;//Heading, menu text, etc
	EXPORT void Switch(const char* Script);//Switches screens
	
};
#endif