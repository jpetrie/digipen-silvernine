#include "precompiled.h"
#include "CRect.h"
//#include "CMemoryMgrS.h"
/*
#ifdef __MEM_DBG__
void * CRect::operator new(size_t sz)
	{
		sz;
		return CMemoryMgr->AllocRect();
	}
	void CRect::operator delete(void *p)
	{
		CMemoryMgr->FreeRect(p);
	}
#endif*/
CRect::CRect(float bottom, float left, float width, float height)
	:mVisibleBorder(true), mBorderWidth(1.f)
{
	SetWorldX(width < 0.f ? left + width : left);
	SetWorldY(height < 0.f ? bottom + height : bottom);
	SetWidth(width < 0.f ? -width : width);
	SetHeight(height < 0.f ? -height : height);
	SetVisible(true);
	SetPinned(false);
	l1 = new CLine(left, bottom, left, bottom + GetHeight());
	l2 = new CLine(left, bottom + GetHeight(), left + GetWidth(), bottom + GetHeight());
	l3 = new CLine(left + GetWidth(), bottom + GetHeight(), left + GetWidth(), bottom);
	l4 = new CLine(left + GetWidth(), bottom, left, bottom);

}
CRect::~CRect() 
{
	delete l1;
	delete l2;
	delete l3;
	delete l4;
}

// border
void CRect::SetBorderColorTL (COLORQUAD cq)
{
	BorderColorTL = cq;
	mHasGradientBorder = true;
}
void CRect::SetBorderColorTL (float r, float g, float b, float a)
{
	COLORQUAD cq(r,g,b,a);
	BorderColorTL = cq;
	mHasGradientBorder = true;
}
void CRect::SetBorderColorTR (COLORQUAD cq)
{
	BorderColorTR = cq;
	mHasGradientBorder = true;
}
void CRect::SetBorderColorTR (float r, float g, float b, float a)
{
	COLORQUAD cq(r,g,b,a);
	BorderColorTR = cq;
	mHasGradientBorder = true;
}
void CRect::SetBorderColorBL (COLORQUAD cq)
{
	BorderColorBL = cq;
	mHasGradientBorder = true;
}
void CRect::SetBorderColorBL (float r, float g, float b, float a)
{
	COLORQUAD cq(r,g,b,a);
	BorderColorBL = cq;
	mHasGradientBorder = true;
}
void CRect::SetBorderColorBR (COLORQUAD cq)
{
	BorderColorBR = cq;
	mHasGradientBorder = true;
}
void CRect::SetBorderColorBR (float r, float g, float b, float a)
{
	COLORQUAD cq(r,g,b,a);
	BorderColorBR = cq;
	mHasGradientBorder = true;
}

// quad vertices
void CRect::SetInteriorColorTL (COLORQUAD cq)
{
	InteriorColorTL = cq;
	mHasGradientInterior = true;
}
void CRect::SetInteriorColorTL (float r, float g, float b, float a)
{
	COLORQUAD cq(r,g,b,a);
	InteriorColorTL = cq;
	mHasGradientInterior = true;
}
void CRect::SetInteriorColorTR (COLORQUAD cq)
{
	InteriorColorTR = cq;
	mHasGradientInterior = true;
}
void CRect::SetInteriorColorTR (float r, float g, float b, float a)
{
	COLORQUAD cq(r,g,b,a);
	InteriorColorTR = cq;
	mHasGradientInterior = true;
}
void CRect::SetInteriorColorBL (COLORQUAD cq)
{
	InteriorColorBL = cq;
	mHasGradientInterior = true;
}
void CRect::SetInteriorColorBL (float r, float g, float b, float a)
{
	COLORQUAD cq(r,g,b,a);
	InteriorColorBL = cq;
	mHasGradientInterior = true;
}
void CRect::SetInteriorColorBR (COLORQUAD cq)
{
	InteriorColorBR = cq;
	mHasGradientInterior = true;
}
void CRect::SetInteriorColorBR (float r, float g, float b, float a)
{
	COLORQUAD cq(r,g,b,a);
	InteriorColorBR = cq;
	mHasGradientInterior = true;
}

// solid colors
void CRect::SetInteriorColor (COLORQUAD cq)
{
	InteriorColor = cq;
	mHasGradientInterior = false;
}
void CRect::SetInteriorColor (float r, float g, float b, float a)
{
	COLORQUAD cq(r,g,b,a);
	InteriorColor = cq;
	mHasGradientInterior = false;
}

void CRect::SetBorderColor (COLORQUAD cq)
{
	BorderColor = cq;
	mHasGradientBorder = false;
}
void CRect::SetBorderColor (float r, float g, float b, float a)
{
	COLORQUAD cq(r,g,b,a);
	BorderColor = cq;
	mHasGradientBorder = false;
}
void CRect::SetBorderWidth(float width) { mBorderWidth = width; }
void CRect::SetBorderIsVisible(bool draw) 
{ 
	mVisibleBorder = draw; 
	l1->SetVisible(draw);
	l1->SetVisible(draw);
	l1->SetVisible(draw);
	l1->SetVisible(draw);
}

bool CRect::BorderIsVisible(bool) { return mVisibleBorder; }

void CRect::Draw (void)
{
	if(IsVisible())
	{
		glDisable(GL_TEXTURE_2D);
		float left = GetWorldX(), bottom = GetWorldY();
		float w = GetWidth();
		float h = GetHeight();

		if(w <= 0.f)
		{
			if(mHasGradientInterior)
			{
				std::swap<COLORQUAD>(InteriorColorTL, InteriorColorTR);
				std::swap<COLORQUAD>(InteriorColorBL, InteriorColorBR);
			}
			w = -w;
			left -= w;
		}
		if(h <= 0.f)
		{
			if(mHasGradientInterior)
			{
				std::swap<COLORQUAD>(InteriorColorTL, InteriorColorBL);
				std::swap<COLORQUAD>(InteriorColorTR, InteriorColorBR);
			}
			h = -h;
			bottom -= h;
		}
		
		if(mHasGradientInterior)
		{
			glBegin(GL_QUADS);
				glColor4f(InteriorColorBL.red, InteriorColorBL.green, InteriorColorBL.blue, InteriorColorBL.alpha);
				glVertex3f(left, bottom, 0.0);
				glColor4f(InteriorColorBR.red, InteriorColorBR.green, InteriorColorBR.blue, InteriorColorBR.alpha);
				glVertex3f(left + w, bottom, 0.0);
				glColor4f(InteriorColorTR.red, InteriorColorTR.green, InteriorColorTR.blue, InteriorColorTR.alpha);
				glVertex3f(left + w, bottom + h, 0.0);
				glColor4f(InteriorColorTL.red, InteriorColorTL.green, InteriorColorTL.blue, InteriorColorTL.alpha);
				glVertex3f(left, bottom + h, 0.0);
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glEnd();
		}
		else
		{
			glBegin(GL_QUADS);
				glColor4f(InteriorColor.red, InteriorColor.green, InteriorColor.blue, InteriorColor.alpha);
				glVertex3f(left, bottom, 0.0);
				glVertex3f(left + w, bottom, 0.0);
				glVertex3f(left + w, bottom + h, 0.0);
				glVertex3f(left, bottom + h, 0.0);
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glEnd();
		}

		if(mVisibleBorder)
		{
			l1->SetVisible(true);
			l2->SetVisible(true);
			l3->SetVisible(true);
			l4->SetVisible(true);

			l1->SetWorldX(left);
			l1->SetWorldY(bottom);
			
			l2->SetWorldX(left);
			l2->SetWorldY(bottom + h);
			
			l3->SetWorldX(left + w);
			l3->SetWorldY(bottom + h);

			l4->SetWorldX(left + w);
			l4->SetWorldY(bottom);

			l1->SetThickness(mBorderWidth);
			l2->SetThickness(mBorderWidth);
			l3->SetThickness(mBorderWidth);
			l4->SetThickness(mBorderWidth);

			if(mHasGradientBorder)
			{
				
				l1->SetBeginColor(BorderColorBL);
				l1->SetEndColor(BorderColorTL);
				l2->SetBeginColor(BorderColorTL);
				l2->SetEndColor(BorderColorTR);
				
				l3->SetBeginColor(BorderColorTR);
				l3->SetEndColor(BorderColorBR);

				l4->SetBeginColor(BorderColorBR);
				l4->SetEndColor(BorderColorBL);
			}
			else
			{
				l1->SetSolidColor(BorderColor);
				l2->SetSolidColor(BorderColor);
				l3->SetSolidColor(BorderColor);
				l4->SetSolidColor(BorderColor);
			}

			
		}
		
		
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		l1->SetVisible(false);
		l2->SetVisible(false);
		l3->SetVisible(false);
		l4->SetVisible(false);

	}
}
