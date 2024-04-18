/*!
	@file	UIStateButton.h
	@author	Eric Roberts
	@date	November 14, 2003

	@brief	Defines a button object
___________________________________________________________*/
#include "UIPane.h"

#ifndef __UISTATEBUTTON_H_
#define __UISTATEBUTTON_H_
class UIStateButton: public UIPane
{
public:
	UIStateButton(ResponseCode SC=0, UIPane* parent = NULL);
	virtual ~UIStateButton();

	bool isSelected(){return isSelected;}
	bool isSelectable(){return isSelectable;}

	bool Select(bool state=true);
	bool MakeSelectable(bool state=true);

	
	
protected:
	bool pisSelected;
	bool pisSelectable;
	
	
	
	//Change state and animation			
	long SelectedSeqIndex;
	long NonSelectedSeqIndex;
	long UnSelectableSeqIndex;
};
#endif