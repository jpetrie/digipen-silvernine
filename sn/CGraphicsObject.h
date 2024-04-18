/*!
	@file	SNgraphgen.h
	@author	Scott Smith

	@brief	contains commonly used constructs and functions
_____________________________________________________________________________*/

#ifndef __SNGRAPHGEN_H__
#define	__SNGRAPHGEN_H__

//#include <algorithm>
#include "CGraphicsMgrS.h"
//#include "MemDebug.h"

struct COLORQUAD
{
	COLORQUAD( float r = 0.0f,  float g = 0.0f,  float b = 0.0f,  float a = 1.0f)
		: red(r), green(g), blue(b), alpha(a) { }

	COLORQUAD (const COLORQUAD &cq)
	{
		red = cq.red;
		green = cq.green;
		blue = cq.blue;
		alpha = cq.alpha;
	}
	float red;
	float green;
	float blue;
	float alpha;
};

/*!
	@class	CGraphicsObject

	@brief	A generic object from which all drawable objects derive from
______________________________________________________________________________*/
class CGraphicsObject
{
public:
/*******************************************************************************
**********************	Constructor	********************************************
*******************************************************************************/
	/*!
		CGraphicsObject::CGraphicsObject
		@brief	Constructor
	__________________________________________________________________________*/
	CGraphicsObject() 
	{
		CGraphicsMgr->AddToList(this);
	}

/*******************************************************************************
**********************	Destructor	********************************************
*******************************************************************************/
	/*!
		CGraphicsObject::~CGraphicsObject
		@brief	Destructor
	__________________________________________________________________________*/
	virtual ~CGraphicsObject() 
	{
		CGraphicsMgr->RemoveFromList(this);
	}

/*******************************************************************************
**********************	Utility 	********************************************
*******************************************************************************/
	/*!
		CGraphicsObject::Draw
		@brief	Renders objects to the screen
	__________________________________________________________________________*/
	virtual void Draw()= 0;

/*******************************************************************************
**********************	Mutator		********************************************
*******************************************************************************/
	/*!
		CGraphicsObject::SetWorldX
		@param	x	The x position of the object's base, in world coordinates
		@brief	Sets the object's x position
	__________________________________________________________________________*/
	void SetWorldX(float x) { m_X = x; }
	/*!
		CGraphicsObject::SetWorldY
		@param	y	The y position of the object's base, in world coordinates
		@brief	Sets the object's y position
	__________________________________________________________________________*/
	void SetWorldY(float y) { m_Y = y; m_ZOrder = y; }
	/*!
		CGraphicsObject::SetWidth
		@param	width	The width of the object, world coordinates
		@brief	Sets the object's width
	__________________________________________________________________________*/
	void SetWidth(float width) { m_Width = width; }
	/*!
		CGraphicsObject::SetHeight
		@param	height	The height of the object, world coorinates
		@brief	Sets the object's height
	__________________________________________________________________________*/
	void SetHeight(float height) { m_Height = height; }
	/*!
		CGraphicsObject::SetZOrder
		@param	ZOrder	This parameter determines the order in which it is drawn
		@brief	Sets the object's drawing order
	__________________________________________________________________________*/
	void SetZOrder(float ZOrder) { m_ZOrder = ZOrder; }
	/*!
		CGraphicsObject::SetPinned
		@param	isPinned	Determines if the object is locked to the window
		@brief	Sets whether the object scrolls with the map
	__________________________________________________________________________*/
	void SetPinned(bool isPinned) { m_isPinned = isPinned; }
	/*!
		CGraphicsObject::SetVisible
		@param	isVisible	This determines if the object will be drawn
		@brief	Sets the visibility status of the object
	__________________________________________________________________________*/
	virtual void SetVisible(bool isVisible) { m_isVisible = isVisible; }

/*******************************************************************************
**********************	Accessor	********************************************
*******************************************************************************/	
	/*!
		CGraphicsObject::GetWorldX
		@brief	Provides the world x coordinate
		@return	The x base position in world coordinates
	__________________________________________________________________________*/
	float GetWorldX(void)	{ return m_X; }
	/*!
		CGraphicsObject::GetWorldY
		@brief	Provides the world y coordinate
		@return	The y base position in world coordinates
	__________________________________________________________________________*/
	float GetWorldY(void)	{ return m_Y; }
	/*!
		CGraphicsObject::GetWidth
		@brief	Provides the width/run of the object
		@return The width/run of the object
	__________________________________________________________________________*/
	float GetWidth(void)	{ return m_Width; }
	/*!
		CGraphicsObject::GetHeight
		@brief	Provides the height/rise of the object
		@return The height/rise of the object
	__________________________________________________________________________*/
	float GetHeight(void)	{ return m_Height; }
	/*!
		CGraphicsObject::GetZOrder
		@brief	Provides the Z-order of the object
		@return The Z-order of the object
	__________________________________________________________________________*/
	float GetZOrder(void)	{ return m_ZOrder; }
	/*!
		CGraphicsObject::IsPinned
		@brief	Provides whether the object is pinned to the window
		@return The object's pinned status
	__________________________________________________________________________*/
	bool IsPinned(void)		{ return m_isPinned; }
	/*!
		CGraphicsObject::IsVisible
		@brief	Provides the visibility status of the object
		@return The visibility status of the object
	__________________________________________________________________________*/
	bool IsVisible(void)	{ return m_isVisible; }

	bool operator==(CGraphicsObject &gObj)	{ return (m_ZOrder == gObj.m_ZOrder/* && m_X == gObj.m_X*/);	}
	bool operator<(CGraphicsObject &gObj)		{ return (m_ZOrder <	gObj.m_ZOrder/* && m_X <	gObj.m_X*/);	}
	bool operator>(CGraphicsObject &gObj)		{ return (m_ZOrder >	gObj.m_ZOrder/* && m_X >	gObj.m_X*/);	}
	bool operator<=(CGraphicsObject &gObj)	{ return (m_ZOrder <= gObj.m_ZOrder/* && m_X <= gObj.m_X*/);	}
	bool operator>=(CGraphicsObject &gObj)	{ return (m_ZOrder >= gObj.m_ZOrder/* && m_X >= gObj.m_X*/);	}
	bool operator!=(CGraphicsObject &gObj)	{ return (m_ZOrder != gObj.m_ZOrder/* && m_X != gObj.m_X*/);	}

protected:
	float m_X, m_Y;			// base position in world coords
	float m_Height;			// height of sprite/rect/text pane, or rise for line
	float m_Width;			// width of sprite/rect/text pane, or run for line
	float m_ZOrder;			// drawing order
	bool	m_isPinned;		// keeps pinned objects from scrolling with the window
	bool	m_isVisible;	// is the object drawn?

};

bool GraphicObjectSort( void *, void * );
bool SpriteSort( void * s1, void *s2 );


#endif

