/*!
	@file	UITextMenu.cpp
	@author	Eric Roberts
	@date	November 14, 2003

	@brief	Defines a button object
___________________________________________________________*/
#include "precompiled.h"
#include "UIScrollBar.h"
const float TOP_PERC =.8f;
const float MOVE_PERC = .2f;
/*!
  UIScrollBar::UIScrollBar
  
  @brief Scrollbar constructor
  @param parent That which the scollbar controls
***************************************************************************/	
	UIScrollBar::UIScrollBar(UIPane* Parent):parent(Parent)
	{
		//position and size bar
		baseSprite->SetWorldY(parent->baseSprite->GetWorldY());
		baseSprite->SetWorldX(parent->baseSprite->GetWorldX()+parent->baseSprite->GetWidth());
		//baseSprite->SetWidth((parent->baseSprite->GetWidth())*MOVE_PERC);
		baseSprite->SetHeight((parent->baseSprite->GetHeight()));
		baseSprite->SetZOrder((parent->baseSprite->GetZOrder()));
		baseSprite->SetVisible(false);
		//create indicator in default size and position
		indicator =new CSprite(baseSprite->GetWorldX(),baseSprite->GetWorldY()+baseSprite->GetHeight()*MOVE_PERC,baseSprite->GetWidth(),(baseSprite->GetHeight())*.6f,"barparts",0,0,0,0);//one chicken
		up_arrow  = new CSprite(0,0,0,0,"barparts",false,1,0,0);
		down_arrow  = new CSprite(0,0,0,0,"barparts",false,0,0,0);
		
		//The dimensions are all the same
		spriteDimension = up_arrow->GetHeight();
				
	}

/*!
  UIScrollBar::~IScrollBar
  
  @brief Scrollbar destructor
***************************************************************************/
	UIScrollBar::~UIScrollBar()
	{
		if(indicator)
			delete indicator;
		if(up_arrow)
			delete up_arrow;
		if(down_arrow)
			delete down_arrow;
	}
/*!
  UIScrollBar::Respond
  
  @brief Scrollbar constructor
  @param parent That which the scollbar controls
***************************************************************************/
	ResponseCode UIScrollBar::Respond(iCode input, float x, float y, int vKeyCode)
	{
	parent->Respond(input);
	return 0;//Never returns a value
	}
/*!
  UIScrollBar::Respond
  
  @brief Scrollbar constructor
  @param parent That which the scollbar controls
***************************************************************************/
	void UIScrollBar::Draw(bool show, float positionx, float positiony)
	{

	//HACK?
	const int current = (int)positionx;
	const int total = (int)positiony;
	//HACK?
	
	//Set base sprite
	float zOrder = baseSprite->GetZOrder();//preserve zOrder
	
	baseSprite->SetVisible(show);
	baseSprite->SetWorldX(absPosition.x);
	baseSprite->SetWorldY(absPosition.y);
	//baseSprite->SetWidth(absSize.x);
	baseSprite->SetHeight(absSize.y);

	baseSprite->SetZOrder(zOrder);//preserve zOrder

	
//Set indicator sprite

	//height of indicator
	float indHeight = (absSize.y*TOP_PERC)/total;
/*
	indicator->SetVisible(show);
	indicator->SetWorldX(absPosition.x);
	
	indicator->SetWorldY(absPosition.y+absSize.y-indHeight*current-indHeight);
	indicator->SetWidth(absSize.x);
	
	indicator->SetZOrder(baseSprite->GetZOrder()-.9f);
	indicator->SetHeight(indHeight);
*/	//Arrows
	//x position
	up_arrow->SetWorldX(absPosition.x);
	down_arrow->SetWorldX(absPosition.x);
	//y position
	up_arrow->SetWorldY(absPosition.y+absSize.y-spriteDimension);//top of bar
	down_arrow->SetWorldY(absPosition.y);//bottom of bar
	//show
	up_arrow->SetZOrder(baseSprite->GetZOrder()-.001f);
	down_arrow->SetZOrder(baseSprite->GetZOrder()-.001f);
	up_arrow->SetVisible(show);
	down_arrow->SetVisible(show);

	
	//In case there is any garbage
	MenuText->SetVisible(false);

	}

/*!
  UIScrollBar::isInside()
  
  @brief Returns true if point (x,y) lies inside, calls Respond method on itself
  @param x x position to test
  @param y y position to test
  
***************************************************************************/
bool UIScrollBar::isInside(float x, float y)
{
bool retval = false;

std::cout<<"SpriteXY"<<baseSprite->GetWorldX()<<" "<<baseSprite->GetWorldY()<<"::"<<"SpriteWH "<<baseSprite->GetWidth()<<" "<<baseSprite->GetHeight()<<"::"<<"Clicked"<<x<<" "<<y<<"::LC "<<this->GetLC()<<"::"<<nlFOURCODE('Q','U','I','T')<<std::endl;

		/*(x>=baseSprite->GetWorldX() && x<=(baseSprite->GetWorldX() + baseSprite->GetWidth())) &&
         (y>=baseSprite->GetWorldY() && y<=(baseSprite->GetWorldY() + baseSprite->GetHeight()));*/

//Top 20%
	if  ((x>=up_arrow->GetWorldX()  && x<=(up_arrow->GetWorldX() + spriteDimension))
		&& (y>=up_arrow->GetWorldY() && y<=(up_arrow->GetWorldY() + spriteDimension)))
	{
		//Scroll up
		Respond(ScrollUp);
		return false;
	}


//Bottom 20%
	if  ((x>=down_arrow->GetWorldX()  && x<=(down_arrow->GetWorldX() + spriteDimension))
		&& (y>=down_arrow->GetWorldY() && y<=(down_arrow->GetWorldY() + spriteDimension)))
	{
		//Scroll up
		Respond(ScrollDown);
		return false;
	}
//return retval;
return false;//never need to return anything
}