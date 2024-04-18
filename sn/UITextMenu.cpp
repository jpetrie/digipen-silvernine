/*!
	@file	UITextMenu.cpp
	@author	Eric Roberts
	@date	November 14, 2003

	@brief	Defines a button object
___________________________________________________________*/
#include "precompiled.h"
#include "UITextMenu.h"
#include "UIScrollBar.h"
const int PAGE_SIZE = 6;
const float MOVE_PERC = .2f;
/*!
  UITextMenu::Fold
  
  @brief Changes whether or not menu is folded, draws menu
***************************************************************************/
void UITextMenu::Fold(bool state)//changes state of menu to 'state'
{
	isFolded=state;
	
	Draw(true);
}

/*!
  UITextMenu::Draw
  
  @brief Draws either all contained buttons or stub, depending on folded state
***************************************************************************/
void UITextMenu::Draw(bool show, float positionx, float positiony)
{
	
	positionx;positiony;//unused as of yet
	positiony = baseSprite->GetZOrder();//preserve zOrder
//	baseSprite->SetBorderColor(.03f,.7f,.9f,.5f);
//	baseSprite->SetInteriorColor(.6f,.9f,.0f,.7f);
	//baseSprite->SetVisible(false);//temporary
	baseSprite->SetVisible(show);

	baseSprite->SetWorldX(absPosition.x);
	baseSprite->SetWidth(absSize.x);

	baseSprite->SetHeight(absSize.y);
	baseSprite->SetWorldY(absPosition.y);
	baseSprite->SetZOrder(positiony);//preserve zOrder

	vector<UIPane*>::iterator curr;//pcha

	//Don't show buttons not on page
	curr = ButtonList.begin();
	while(curr != ButtonList.end())
	{
		//Go straight to sprite and text, no need to call Draw method
		(*curr)->baseSprite->SetVisible(false);
		(*curr)->MenuText->SetVisible(false);
		curr++;
	}
	//Set size and position of buttons based on page
	curr = ButtonList.begin();//+currentPage*pageSize;
	
	int i = currentPage;
	//Advance to first button
	while(i)
	{
		i--;
		for(int j=0; j<pageSize;j++)
		{
			curr++;
		}
	}

	i=0; //reset for next loop
	float buttonHeight;
	if(ButtonList.size() >= 1)
	buttonHeight = ButtonList[0]->absSize.y;
	else
	buttonHeight = 0;

	while(curr != ButtonList.end() && (i<pageSize))
	{
		//(*curr)->SetAbsSize(absSize.x,buttonHeight); 
		(*curr)->SetAbsPos(absPosition.x, absPosition.y + absSize.y - buttonHeight*(i+1));
		(*curr)->baseSprite->SetZOrder(baseSprite->GetZOrder()-.3f);
		(*curr)->Draw(show);
		curr++;
		i++;
	}
	//
	MenuText->SetVisible(show);
	
	//MenuText->SetHeight(absSize.y);
	MenuText->SetHeight(40);//why 40? cuz.
	MenuText->SetWidth(absSize.x);
	MenuText->SetLocation(absPosition.x, absPosition.y+absSize.y);
	MenuText->SetZOrder(baseSprite->GetZOrder() - .9f);
	
	MenuText->SetStartLine();

	//
	scroll->SetAbsSize(absSize.x*MOVE_PERC,absSize.y); 
	scroll->SetAbsPos(absPosition.x+absSize.x, absPosition.y);
	scroll->Draw(false, (float)currentPage, (float)totalPages);
}

/*!
  UITextMenu::Respond
  
  @brief Like base class's Respond except for folding and unfolding when clicked
***************************************************************************/
ResponseCode UITextMenu::Respond(iCode input, float x, float y, int vKeyCode)
{	
	//if(!isFolded)
	//{
	if(input == ScrollDown)
	{
		currentPage = (currentPage+1 >= totalPages)?currentPage:currentPage+1;
		
	}

	if(input == ScrollUp)
	{
	
		currentPage = (currentPage==0)?	0:(currentPage-1);
	}

	if(input == LClick)
	{
		int index=(int)ButtonList.size();

		while(--index>-1)
		{
			if(ButtonList[index]->isInside(x,y) && ButtonList[index]->baseSprite->IsVisible())
			{
				//Fold();
				//HACK!
				if(ButtonList[index]->baseSprite->GetCurrentFrame())
				{	
					ButtonList[index]->baseSprite->SetInitFrame(0);
				}
				else
				{
					ButtonList[index]->baseSprite->SetInitFrame(1);
				}
				Draw(true);
				return ButtonList[index]->Respond(input);
			}
		}
	}
		//Fold();

	//}
	/*else
	{
		Fold(false);
	}*/
	return 0;

}

/*!
  UITextMenu::Add
  
  @brief Adds button to bottom of UITextMenu
***************************************************************************/
void UITextMenu::AddButton(UIPane* button)//insert into vector, re-set extent
{
	//Set relative position based on how many are in the list, then add button
//	int lastButton;
	/*if((lastButton = (int)ButtonList.size()) == 0)
	{//First button added
		button->relPosition.x = 0;
		button->relPosition.y = -1*foldedSize.y;
	}
	else
	{
		lastButton-=1;
		button->relPosition.x = ButtonList[lastButton]->relPosition.x;
		button->relPosition.y = ButtonList[lastButton]->relPosition.y-ButtonList[lastButton]->absSize.y;
	}*/
	//Don't care about relative positions anymore

/*Figure out how many pages*/
	ButtonList.push_back(button);
	//integer division
	pageSize =(int)( absSize.y/button->absSize.y);
	totalPages=(int)ButtonList.size() / pageSize + 1;
	
	//integer division

	//SetExtent();
}

/*!
  UITextMenu::UITextMenu
  
  @brief Default constructor that sets folded size of menu
***************************************************************************/
UITextMenu::UITextMenu(char* spriteCollection, float foldedX, float foldedY):
UIMenu(spriteCollection),/*sprite initialization*/ 
pageSize(PAGE_SIZE),
currentPage(0)/**/
{
	foldedSize.x = absSize.x = foldedX;
	foldedSize.y = absSize.y = foldedY;
	scroll = new UIScrollBar(this);
}
/*!
  UITextMenu::UITextMenu
  
  @brief Default constructor that sets folded size of menu
***************************************************************************/
UITextMenu::~UITextMenu()
{
	
	if(scroll)
		delete scroll;
}
/*!
  UITextMenu::isInside
  
  @brief returns true if point(x,y) is contained within UITextMenu.  Takes into account
  folded state
***************************************************************************/
bool UITextMenu::isInside(float x, float y)
{
bool retval = false;

std::cout<<"TextMenuSpecial SpriteXY"<<baseSprite->GetWorldX()<<" "<<baseSprite->GetWorldY()<<"::"<<"SpriteWH "<<baseSprite->GetWidth()<<" "<<baseSprite->GetHeight()<<"::"<<"Clicked"<<x<<" "<<y<<"::LC "<<this->GetLC()<<"::"<<nlFOURCODE('Q','U','I','T')<<std::endl;
nsl::point2D<float> topLeft;
nsl::point2D<float> bottomRight;

topLeft = ScreenToWorld((int)absPosition.x, (int)absPosition.y);
bottomRight = ScreenToWorld((int)(absPosition.x+foldedSize.x), (int)(absPosition.y+foldedSize.y));

/*if(isFolded)
//retval = (x>=topLeft.x && x<=bottomRight.x) && (y<=topLeft.y && y>=bottomRight.y);
retval = (x>=absPosition.x && x<=absPosition.x+foldedSize.x) && (y>=absPosition.y && y<=absPosition.y+foldedSize.y);
else*/

retval = (x>=baseSprite->GetWorldX() && x<=(baseSprite->GetWorldX() + baseSprite->GetWidth())) &&
         (y>=baseSprite->GetWorldY() && y<=(baseSprite->GetWorldY() + baseSprite->GetHeight()));
cout<<":::"<<retval<<endl;
//No need to test scroll bar if inside text pane
if(!retval)
{
scroll->isInside(x,y);
Draw(true);
}

return retval;
}