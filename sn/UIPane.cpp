/*!
	@file	UIPane.cpp
	@author	Eric Roberts
	@date	October 23, 2003

	@brief	Defines a base class for menu objects
___________________________________________________________*/
#include "precompiled.h"
#include "UIPane.h"

//#include "cSprite.h"

/*!
  UIPane::UIPane
  
  @brief Default constructor for UIPane. ResponseCodes set to 0
***************************************************************************/
/*UIPane::UIPane()
{
	rcRightClick = rcMiddleClick = rcKeyPress = rcLeftClick =rcSubmitCode = 0;
	baseSprite= new CRect(0,0,0,0);
	MenuText->SetText("Impish glee");
}*/

/*!
  UIPane::UIPane
  
  @brief Default constructor for UIPane. ResponseCodes set to 0
***************************************************************************/
UIPane::UIPane(ResponseCode lc, ResponseCode rc, ResponseCode mc, ResponseCode kb, ResponseCode sc, string spriteCollection):rcLeftClick(lc),
	rcRightClick(rc),
	rcMiddleClick(mc),
	rcKeyPress(kb),
	rcSubmitCode(sc)
{
	//baseSprite= new CRect(0,0,0,0);
	
	MenuText = new CText;
	//absSize.x  = absSize.y= 100;

	baseSprite = new CSprite(0,0,0,0,spriteCollection,false,(int)rc,0,0);

	absSize.x = baseSprite->GetWidth();
	absSize.y = baseSprite->GetHeight();

	//baseSprite = new CSprite(0,0,absSize.x,absSize.y,"chicky",bgSequenceIndex,0,0,0);
	
   //baseSprite = new CRect(0,0,0,0);
	MenuText->SetText("");
	MenuText->SetHeight(absSize.y);
	MenuText->SetWidth(absSize.x);
	MenuText->SetStartLine();
}

/*!
  UIPane::SetAbsSize
  
  @brief Copy constructor for UIPane.  Creates new baseSprite.
***************************************************************************/
bool UIPane::SetAbsSize(float x, float y)
{
	absSize.x = x;
	absSize.y = y;
	return true;
}
/*!
  UIPane::SetRelSize
  
  @brief Copy constructor for UIPane.  Creates new baseSprite.
***************************************************************************/
bool UIPane::SetRelSize(float x, float y)
{
	relSize.x = x;
	relSize.y = y;
	return true;
}
/*!
  UIPane::UIPane
  
  @brief Copy constructor for UIPane.  Creates new baseSprite.
***************************************************************************/
UIPane::UIPane(const UIPane& original)
{
relPosition = original.relPosition;
absPosition = original.absPosition;//Absolute screen position in pixels
relSize= original.relSize;// percentage of normal size for enlarging/shrinking
absSize= original.absSize;//Normal size of pane
isFocused = original.isFocused;//Whether or not input will be directed at this UIPane

//MenuText->SetText("Impish glee");

//baseSprite = new CRect(0,0,0,0);//change to CSprite
baseSprite = new CSprite(0,0,original.absSize.x,original.absSize.y,"chicky",true,0,0,0);
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
  UIPane::~UIPane
  
  @brief destructor for UIPane. Deletes sprite
***************************************************************************/
UIPane::~UIPane()
{
	delete baseSprite;
	delete MenuText;
	MenuText = NULL;
	baseSprite =NULL;
}

/*!
  UIPane::SetFocus
  
  @brief Sets isFocused variable, returns old value
***************************************************************************/
bool UIPane::SetFocus(bool setVal)//Sets focus to setVal, returns previous state
{
	bool temp =isFocused;
	isFocused =setVal;
	return temp;
}

/*!
  UIPane::Select
  
  @brief Sets focus and changes border color (will be sprite index)
***************************************************************************/
bool UIPane::Select(bool state)
{
	SetFocus(state);
	
	if(state)
	state;//baseSprite->SetBorderColor(0,0,0,1);
	else
	state;//baseSprite->SetBorderColor(1,1,1,1);
	return state;
}
/*!
  UIPane::Draw
  
  @brief Sets position and size of baseSprite.  Last two arguments ignored
***************************************************************************/
void UIPane::Draw(bool show, float positionx, float positiony)
{
	//All temporary, will draw with sprites 

	positionx;positiony;//unused as of yet
	//(isFocused)?baseSprite->SetBorderColor(.0f,.0f,.0f,1.f):baseSprite->SetBorderColor(1.f,1.f,1.f,1.f);
	//baseSprite->SetInteriorColor(.9f,.4f,.4f,.7f);
	positiony = baseSprite->GetZOrder();//Save Z order
	baseSprite->SetVisible(show);
	baseSprite->SetWorldX(absPosition.x);
	baseSprite->SetWorldY(absPosition.y);
	//Was uncommented
	baseSprite->SetWidth(absSize.x);
	baseSprite->SetHeight(absSize.y);
	baseSprite->SetZOrder(positiony);//Reset Z order
	//Was uncommented

	//baseSprite->SetFacing(5); //Can use to set one-time animation fake?
	
	MenuText->SetVisible(show);
	
	//MenuText->SetHeight(absSize.y);
	MenuText->SetHeight(40);//why 40? cuz.
	MenuText->SetWidth(absSize.x);
	MenuText->SetLocation(absPosition.x, absPosition.y);
	MenuText->SetZOrder(baseSprite->GetZOrder() - .9f);
	
	MenuText->SetStartLine();
	
}

/*!
  UIPane::SetRelPos
  
  @brief Sets relative position. Returns true if UIPane was already there, false
  if not
***************************************************************************/
bool UIPane::SetRelPos(float x, float y)
{
	bool retval = ((relPosition.x == x) && (relPosition.y==y));

	relPosition.x = x;
	relPosition.y = y;

	return retval;//later for saying whether already there
}

/*!
  UIPane::SetAbsPos
  
  @brief Sets absolute position of center of object, not lower leftFIXME
***************************************************************************/
bool UIPane::SetAbsPos(float x, float y)
{
	bool retval = ((absPosition.x == x) && (absPosition.y==y));

	absPosition.x = x;
	absPosition.y = y;

	return retval;//later for saying whether already there
}
/*!
  UIPane::Respond
  
  @brief Returns ResponseCode depending only on iCode
***************************************************************************/
ResponseCode UIPane::Respond(iCode input, float x, float y, int vKeyCode)
{
	x,y;//Unused in base class
	
	switch(input)
	{
	case LClick:
		{
			return GetLC();
			break;
		}
	case RClick:
		{
			return GetRC();
			break;
		}
	case MClick:
		{
			return GetMC();
			break;
		}
	case KeyPress:
		{
			return GetKP();
			break;
		}
	default:
		{
			return 0;
			break;
		}
	}
}

/*!
  UIPane::isInside
  
  @brief Returns true if point (x,y) lies inside UIPane, false otherwise
***************************************************************************/
bool UIPane::isInside(float x, float y)
{
bool retval = false;

std::cout<<"SpriteXY"<<baseSprite->GetWorldX()<<" "<<baseSprite->GetWorldY()<<"::"<<"SpriteWH "<<baseSprite->GetWidth()<<" "<<baseSprite->GetHeight()<<"::"<<"Clicked"<<x<<" "<<y<<"::LC "<<this->GetLC()<<"::"<<nlFOURCODE('Q','U','I','T')<<std::endl;

retval = (x>=baseSprite->GetWorldX() && x<=(baseSprite->GetWorldX() + baseSprite->GetWidth())) &&
         (y>=baseSprite->GetWorldY() && y<=(baseSprite->GetWorldY() + baseSprite->GetHeight()));

return retval;
}

nsl::point2D<float> UIPane::GetAbsPos()
{
	nsl::point2D<float> point;

	point.x = absPosition.x;
	point.y = absPosition.y;

	
	return(point);
}
