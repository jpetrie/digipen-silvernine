/*!
	@file	UIButton.cpp
	@author	Eric Roberts
	@date	November 13, 2003

	@brief	Defines a base class for menu objects
___________________________________________________________*/
#include "precompiled.h"
#include "UIButton.h"

/*!
	UIButton::UIButton

	@brief	constructor that accepts, leftClick, RightClick, MiddleClick,
	keyBoard, and Submit ResponseCodes and pointer to parent, all defaulted to 0
______________________________________________________________________________*/
UIButton::UIButton(ResponseCode lc, ResponseCode rc, ResponseCode mc, ResponseCode kb, ResponseCode sc, char* spriteCollection ,UIPane* parent):UIPane(lc,rc,mc,kb,sc, spriteCollection)
{
	parentControl = parent;
	//Default to sprite's dimensions
	hitSize.x = baseSprite->GetWidth();
	hitSize.y = baseSprite->GetHeight();
	hitOrigin.x = 0;
	hitOrigin.y = 0;

}
/*!
  UIButton::UIButton
  
  @brief Copy constructor for UIPane.  Creates new baseSprite.
***************************************************************************/
UIButton::UIButton(const UIButton& original)
{
relPosition = original.relPosition;
absPosition = original.absPosition;//Absolute screen position in pixels
relSize= original.relSize;// percentage of normal size for enlarging/shrinking
absSize= original.absSize;//Normal size of pane
isFocused = original.isFocused;//Whether or not input will be directed at this UIPane

//MenuText->SetText("Impish glee");

//baseSprite = new CRect(0,0,0,0);//change to CSprite
baseSprite = new CSprite(0,0,original.absSize.x,original.absSize.y,"i_sprites",true,0,0,0);

//baseSprite = new CRect(0,0,0,0);
MenuText = new CText("yabba dapper doo", 20,"Jokerman");
MenuText->SetColor4f(1.f, 1.f, 1.f, 1.f);
(*MenuText) = (*original.MenuText);
(*baseSprite) = (*original.baseSprite);

rcLeftClick=original.rcLeftClick;
rcRightClick = original.rcRightClick;
rcMiddleClick = original.rcMiddleClick;
rcSubmitCode  = original.rcSubmitCode;
rcKeyPress = original.rcKeyPress;
}
/*!
	UIButton::~UIButton

	@brief	destructor that does nothing
______________________________________________________________________________*/
UIButton::~UIButton()
{

}

void UIButton::SetHitSize(float x, float y)
{
	hitSize.x = x;
	hitSize.y = y;

}

void UIButton::SetHitOrigin(float x, float y)
{
	hitOrigin.x = x;
	hitOrigin.y = y;

}
/*!
  UIButton::SetAbsSize
  
  @brief Sets size for a button, considers hit info
***************************************************************************/
bool UIButton::SetAbsSize(float x, float y)
{

	//New hit origin and size in same place relative to button
	hitOrigin.y = x*(hitOrigin.x/absSize.x);
	hitOrigin.y = y*(hitOrigin.y/absSize.y);
	hitSize.y = y*(hitSize.y/absSize.y);
	hitSize.x = x*(hitSize.x/absSize.x);

	absSize.x = x;
	absSize.y = y;
	return true;
}
/*!
  UIButton::SetAbsPos
  
  @brief Sets pos for a button, considers hit info
***************************************************************************/
bool UIButton::SetAbsPos(float x, float y)
{
	//New position
	absPosition.x = x;
	absPosition.y = y;
	
	return true;
}


bool UIButton::isInside(float x, float y)
{
bool retval = false;

std::cout<<"SpriteXY"<<baseSprite->GetWorldX()<<" "<<baseSprite->GetWorldY()<<"::"<<"SpriteWH "<<baseSprite->GetWidth()<<" "<<baseSprite->GetHeight()<<"::"<<"Clicked"<<x<<" "<<y<<"::LC "<<this->GetLC()<<"::"<<nlFOURCODE('Q','U','I','T')<<std::endl;

/*retval = (x>=baseSprite->GetWorldX() && x<=(baseSprite->GetWorldX() + baseSprite->GetWidth())) &&
         (y>=baseSprite->GetWorldY() && y<=(baseSprite->GetWorldY() + baseSprite->GetHeight()));
*/
/*retval = (x>=baseSprite->GetWorldX() && x<=(baseSprite->GetWorldX() + baseSprite->GetWidth())) &&
         (y>=baseSprite->GetWorldY() && y<=(baseSprite->GetWorldY() + baseSprite->GetHeight()));*/


/*retval = (x>=baseSprite->GetWorldX() && x<=(baseSprite->GetWorldX() + baseSprite->GetWidth())) &&
         (y>=baseSprite->GetWorldY() && y<=(baseSprite->GetWorldY() + baseSprite->GetHeight()));
		/*float xdiff = (absSize.x - hitSize.x)/2;
		float ydiff = (absSize.y - hitSize.y)/10.9;//Hackey value derived from observation of main menu buttons
		static float rgb[3] = {.1,.07,.3};
		rgb[2] = rgb[1] +=rgb[0];
		CRect* testRec =  new CRect(absPosition.y + ydiff, absPosition.x + xdiff, hitSize.x, hitSize.y);
		
		testRec->SetVisible(true);
		testRec->SetInteriorColor(rgb[2],rgb[1],rgb[0],1);
		testRec->SetZOrder(baseSprite->GetZOrder() - .1);
		testRec->SetBorderIsVisible(false);
		
		
			 
		retval =  (x>=(absPosition.x + xdiff))&&(x<=(absPosition.x +  xdiff+hitSize.x) );
		retval &= (y>=(absPosition.y+ ydiff ))&&(y<=(absPosition.y + ydiff+hitSize.y ) );*/
/*
		static float rgb[3] = {.1,.07,.3};
		rgb[2] = rgb[1] +=rgb[0];
		CRect* testRec =  new CRect(absPosition.y + hitOrigin.y , absPosition.x + hitOrigin.x, hitSize.x, hitSize.y);
		
		testRec->SetVisible(true);
		testRec->SetInteriorColor(rgb[2],rgb[1],rgb[0],1);
		testRec->SetZOrder(baseSprite->GetZOrder() - .1);
		testRec->SetBorderIsVisible(false);
		
		
*/			 
		retval =  (x>=(absPosition.x + hitOrigin.x))&&(x<=(absPosition.x+hitOrigin.x + hitSize.x) );
		retval &= (y>=(absPosition.y + hitOrigin.y))&&(y<=(absPosition.y + hitOrigin.y + hitSize.y) );

		cout<<"Result:"<<retval<<endl;
		return retval;



}
/*!
	UIButton::Draw

	@brief	Ignores last two arguments, sets sprite's is visible to show
______________________________________________________________________________*/
/*void UIButton::Draw(bool show, float positionx, float positiony)
{
	//All temporary, will draw with sprites 
	positionx;positiony;//unused as of yet
	baseSprite->SetBorderColor(.3f,.07f,.9f,.5f);
	baseSprite->SetInteriorColor(.9f,.4f,.04f,.7f);
	baseSprite->SetVisible(show);
	baseSprite->SetWorldX(absPosition.x);
	baseSprite->SetWorldY(absPosition.y);
	baseSprite->SetWidth(absSize.x);
	baseSprite->SetHeight(absSize.y);
	
	//All temporary, will draw with sprites
}*/