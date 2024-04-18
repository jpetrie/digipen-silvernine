/*!
	@file	SNrect.h
	@author	Scott Smith
	@date	September 12, 2003

	@brief	Defines a class for rectangle drawing
___________________________________________________________*/


#ifndef __SNRECT_H__
#define __SNRECT_H__

//#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#include <algorithm>
#include "CGraphicsObject.h"
#include "CLine.h"

class CRect: public CGraphicsObject
{

public:
	CRect(float bottom, float left, float width, float height);
	virtual ~CRect();

	// border
	void SetBorderColorTL (COLORQUAD cq);
	void SetBorderColorTL (float r, float g, float b, float a);
	void SetBorderColorTR (COLORQUAD cq);
	void SetBorderColorTR (float r, float g, float b, float a);
	void SetBorderColorBL (COLORQUAD cq);
	void SetBorderColorBL (float r, float g, float b, float a);
	void SetBorderColorBR (COLORQUAD cq);
	void SetBorderColorBR (float r, float g, float b, float a);

	// quad vertices
	void SetInteriorColorTL (COLORQUAD cq);
	void SetInteriorColorTL (float r, float g, float b, float a);
	void SetInteriorColorTR (COLORQUAD cq);
	void SetInteriorColorTR (float r, float g, float b, float a);
	void SetInteriorColorBL (COLORQUAD cq);
	void SetInteriorColorBL (float r, float g, float b, float a);
	void SetInteriorColorBR (COLORQUAD cq);
	void SetInteriorColorBR (float r, float g, float b, float a);
	
	// solid colors
	void SetInteriorColor (COLORQUAD cq);
	void SetInteriorColor (float r, float g, float b, float a);

	void SetBorderColor (COLORQUAD cq);
	void SetBorderColor (float r, float g, float b, float a);
	void SetBorderWidth(float width);

#ifdef __MEM_DBG__
	void * operator new(size_t sz);
	void operator delete(void *p);
#endif

	void SetBorderIsVisible(bool draw);
	bool BorderIsVisible(bool);
	//void SetVisible(bool isVisible);
	
	virtual void Draw (void);

private:
	COLORQUAD BorderColorTL;
	COLORQUAD BorderColorTR;
	COLORQUAD BorderColorBL;
	COLORQUAD BorderColorBR;
	COLORQUAD BorderColor;
	COLORQUAD InteriorColorTL;
	COLORQUAD InteriorColorTR;
	COLORQUAD InteriorColorBL;
	COLORQUAD InteriorColorBR;
	COLORQUAD InteriorColor;
	CLine * l1, *l2, *l3, *l4;
	bool mHasGradientInterior;
	bool mHasGradientBorder;
	bool mVisibleBorder;
	float mBorderWidth;

};

#endif
