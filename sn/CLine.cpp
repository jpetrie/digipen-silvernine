#include "precompiled.h"
#include "CLine.h"
//#include "CMemoryMgrS.h"

//#ifdef __MEM_DBG__
//void * CLine::operator new(size_t sz)
	//{
		//sz;
		//return CMemoryMgr->AllocLine();
//	}
	//void CLine::operator delete(void *p)
//	{
	//	CMemoryMgr->FreeLine(p);
	//}
////#endif
static inline int round(float f)
{
	return (int)(f + 0.5f);
}

CLine::CLine (float x0, float y0, float x1, float y1):m_Thickness(1)
{
	SetWorldX(x0);
	SetWorldY(y0);
	SetWidth(x1- x0);
	SetHeight(y1 - y0);
	//SetZOrder(...);
	SetVisible(true);
	SetPinned(false);
}							 
// destructor
CLine::~CLine () { }

void CLine::SetBeginColor (COLORQUAD cq)
{
	mBeginColor = cq;
	mHasGradientColor = true;
}
void CLine::SetBeginColor (float r, float g, float b, float a)
{
	COLORQUAD cq(r,g,b,a);
	mBeginColor = cq;
	mHasGradientColor = true;
}
void CLine::SetEndColor (COLORQUAD cq)
{
	mEndColor = cq;
	mHasGradientColor = true;
}
void CLine::SetEndColor (float r, float g, float b, float a)
{
	COLORQUAD cq(r,g,b,a);
	mEndColor = cq;
	mHasGradientColor = true;
}
void CLine::SetSolidColor (COLORQUAD cq)
{
	mColor = cq;
	mHasGradientColor = false;
}
void CLine::SetSolidColor (float r, float g, float b, float a)
{
	COLORQUAD cq(r,g,b,a);
	mColor = cq;
	mHasGradientColor = false;
}
void CLine::SetThickness(float width) { m_Thickness = width; }

//void SetVisible (bool draw) { mVisible = draw; }
//bool IsVisible(void) { return mVisible; }

void CLine::Draw (void)
{
	if(!IsVisible())
		return;

	
	glDisable(GL_TEXTURE_2D);
	glLineWidth(m_Thickness);

	if(mHasGradientColor)
	{
		glBegin(GL_LINES);
			glColor4f(mBeginColor.red, mBeginColor.green, mBeginColor.blue, mBeginColor.alpha);
			glVertex2f(GetWorldX(), GetWorldY());
			glColor4f(mEndColor.red, mEndColor.green, mEndColor.blue, mEndColor.alpha);
			glVertex2f(GetWorldX() + GetWidth(), GetWorldY() + GetHeight());
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glEnd();
	}
	else
	{
		glBegin(GL_LINES);
			glColor4f(mColor.red, mColor.green, mColor.blue, mColor.alpha);
			glVertex2f(GetWorldX(), GetWorldY());
			glColor4f(mColor.red, mColor.green, mColor.blue, mColor.alpha);
			glVertex2f(GetWorldX() + GetWidth(), GetWorldY() + GetHeight());
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glEnd();
	}
	
	

	glLineWidth(1.0);
	glEnable(GL_TEXTURE_2D);
	
}