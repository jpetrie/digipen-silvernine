/*!
	@file	SNLine.h
	@author	Scott Smith
	@date	September 11, 2003

	@brief	Defines a class for line drawing
___________________________________________________________*/



#ifndef __CLINE_H__
#define __CLINE_H__

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library

#include "CGraphicsObject.h"

class CLine : public CGraphicsObject
{
public:
	// default constructors
	CLine (float x0, float y0, float x1, float y1);
	
	// destructor
	virtual	~CLine ();

	void SetBeginColor (COLORQUAD cq);
	void SetBeginColor (float r, float g, float b, float a);
	void SetEndColor (COLORQUAD cq);
	void SetEndColor (float r, float g, float b, float a);
	void SetSolidColor (COLORQUAD cq);
	void SetSolidColor (float r, float g, float b, float a);
	void SetThickness(float width);
		
	virtual void Draw (void);
private:
	//float x0, y0, x1, y1;
	COLORQUAD mBeginColor;
	COLORQUAD mEndColor;
	COLORQUAD mColor;
	bool  mHasGradientColor;
	//bool  mVisible;
	GLfloat m_Thickness;

	
};

#endif