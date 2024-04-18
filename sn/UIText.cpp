/*!
	@file	UIText.h
	@author	Eric Roberts
	@date	November 14, 2003

	@brief	Defines a button object
___________________________________________________________*/
#include "UIText.h"

//const int PAGE_SIZE = ;
const float MOVE_PERC = .2f;

const long tDelay=160;

/*!
  UIText::Select
  
  @brief Changes color of text depending on 'state'
***************************************************************************/
bool UIText::Select(bool state )
{

	//if(state)
	//	//FullText.SetColor4f(.5f,.5f,.8f,.6f);
	//else
	//	//FullText.SetColor4f(.8f,.5f,.8f,.7f);
	

return state;
}
/*!
  UIText::UIText
  
  @brief Default constructor, initializes //FullText member
***************************************************************************/

UIText::UIText(const char* text, int fontSize):UIPane() //: //FullText("abdbd",25,"Webdings")
{
	textString = text;
	FullText = new CText(textString, fontSize,"Terminal");
	
	
	
	//FullText->SetText(textString.c_str());


	//FullText.SetText("This is the text that I would like to display here.  SCENE I. Rousillon. The COUNT\'s palace.Enter BERTRAM, the COUNTESS of Rousillon,");
	
	//absPosition.x = absPosition.y = 300;
	//absSize.x = absSize.y=200;
	currentLine = 0;

	//baseSprite->SetHeight(abs);
/*
	FullText->SetStartLine(currentLine);
	FullText->SetVisible(true);
	FullText->SetColor4f(.5f,.3f,.4f,1.f);
	FullText->SetHeight(absSize.y);
	FullText->SetWidth(absSize.x);
	FullText->SetLocation(absPosition.x, absPosition.y);*/
/*
	FullText->SetWorldX(400);
    FullText->SetWorldY(100);
    FullText->SetWidth(400);
    FullText->SetHeight(375);
    FullText->SetZOrder(-2000);
    FullText->SetColor4f(0.3f,0.3f,0.3f,1.0f);
*/

//	scroll = new UIScrollBar(this);
	currentPage =0;
	totalPages =1;

	//FullText.SetStartLine(currentLine);
	//FullText.SetVisible(true);
	//FullText.SetColor4f(.5f,.3f,.4f,1.f);
	//FullText.SetHeight(absSize.y);
	//FullText.SetWidth(absSize.x);
	//FullText.SetLocation(absPosition.x, absPosition.y);

}

UIText::~UIText()
{
if(FullText)
	delete FullText;
/*if(scroll)
	delete scroll;*/

}

/*!
  UIText::Respond
  
  @brief Only responds to ScrollUp and ScrollDown, last two arguments are ignored
***************************************************************************/
ResponseCode UIText::Respond(iCode input, float x, float y, int vKeyCode)
{
	x,y;//unused
	static DWORD timer=0;
	if(input == ScrollDown)
	{
		currentLine = (currentLine==0)?	0:(currentLine-1);
	}
	if(input == ScrollUp)
	{
		//No way to find the last line at which we can start FIXEM
	   currentLine++;
	}

	if(input == KeyPress)
	{
		int temp;

		if( ((temp=GetTickCount())-timer)>tDelay)
		{
			if(vKeyCode == VK_BACK)//backspace
			{
				//Weak solution, fixme
				char* c = new char[textString.length()+1];
				strcpy(c, textString.c_str());
				c[strlen(c)-1] = 0;
				textString.clear();
				textString = c;
				delete[] c;
			}
			else
			{
		//AddText("We are the world");
		//Should probably call AddText, but sort of a special case here
				textString+=(char)vKeyCode;
				
			}
		timer=temp;
		}
		
	}
	FullText->SetStartLine(currentLine);
	FullText->SetText(textString.c_str());
	Draw();
	//FullText.SetStartLine(currentLine);

	return 0;

}

void UIText::Draw(bool show, float positionx, float positiony)
{
	//All temporary, will draw with sprites 

	positionx;positiony;//unused as of yet
//	baseSprite->SetBorderColor(.03f,.7f,.9f,.5f);
//	baseSprite->SetInteriorColor(.9f,.4f,.4f,.7f);
	
	positiony = baseSprite->GetZOrder();//preserve zOrder
	

	baseSprite->SetVisible(false);//TextBackground
	baseSprite->SetWorldX(absPosition.x);
	baseSprite->SetWorldY(absPosition.y);
	baseSprite->SetWidth(absSize.x);
	baseSprite->SetHeight(absSize.y);
	
	baseSprite->SetZOrder(positiony);//preserve zOrder

	FullText->SetVisible(show);
	FullText->SetHeight(absSize.y);
	FullText->SetWidth(absSize.x);
	FullText->SetLocation(absPosition.x, absPosition.y);
	FullText->SetZOrder(baseSprite->GetZOrder() - 90.1f);
	FullText->SetStartLine(currentLine);
	

/*	scroll->SetAbsSize(absSize.x*MOVE_PERC,absSize.y); 
	scroll->SetAbsPos(absPosition.x+absSize.x, absPosition.y);
	scroll->Draw(false, currentPage, totalPages);*/
	
	

	//FullText.SetVisible(show);
	//FullText.SetHeight(absSize.y);
	//FullText.SetWidth(absSize.x);
	//FullText.SetLocation(absPosition.x, absPosition.y);
	//FullText.SetZOrder(baseSprite->GetZOrder() - .1f);
	//FullText.SetStartLine();

	MenuText->SetLocation(absPosition.x, absPosition.y+absSize.y);
	
	MenuText->SetVisible(show);
	MenuText->SetHeight(40);
	MenuText->SetWidth(absSize.x);
	
	MenuText->SetZOrder(baseSprite->GetZOrder() - .1f);
	
	MenuText->SetStartLine();
	
	
	//All temporary, will draw with sprites
}

const char* UIText::GetText()
{
	return textString.c_str();
}

void UIText::AddText(const char* newText)
{
	textString+=newText;
	FullText->SetText(textString.c_str());
}

/*!
  UIText::isInside
  
  @brief Returns true if point (x,y) lies inside UIPane, false otherwise
		 tests its scroll bar
***************************************************************************/
bool UIText::isInside(float x, float y)
{
bool retval = false;

std::cout<<"SpriteXY"<<baseSprite->GetWorldX()<<" "<<baseSprite->GetWorldY()<<"::"<<"SpriteWH "<<baseSprite->GetWidth()<<" "<<baseSprite->GetHeight()<<"::"<<"Clicked"<<x<<" "<<y<<"::LC "<<this->GetLC()<<"::"<<nlFOURCODE('Q','U','I','T')<<std::endl;

retval = (x>=baseSprite->GetWorldX() && x<=(baseSprite->GetWorldX() + baseSprite->GetWidth())) &&
         (y>=baseSprite->GetWorldY() && y<=(baseSprite->GetWorldY() + baseSprite->GetHeight()));

//No need to test scroll bar if inside text pane
//retval?NULL:scroll->isInside(x,y);

return retval;
}

void UIText::Clear()
{
	textString.clear();
	FullText->SetText("");
}
