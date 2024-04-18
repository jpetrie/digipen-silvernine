/*! =========================================================================
      
      @file    nsl_tools_math.cpp
      @brief   Math tools implementation.
      
    ========================================================================= */
    
#include "nsl_tools_math.h"

int nsl::randint(int min,int max)
{
  return ((rand() % ((max - min) + 1)) + min);
}

float nsl::randfloat(float min,float max)
{
  // This works by generating integer random values between 100 * min and
  // 100 * max, then dividing the result by 100, into a float. This gives
  // us two digits of floating point precision, which is enough.
  
  // This will never give you EXACTLY the max, but you will get imperceptably (as a float) close.
  
  unsigned long imax,imin;
  imax = scast< int >(max * 100 + 1);
  imin = scast< int >(min * 100);
  
unsigned long  ir = rand() % ((imax - imin) + 1);

  return ((float)imin / 100.f + ((float)ir / 100.0f));
}



bool nsl::pt_in_ellipse(float ellipseLocX,float ellipseLocY,float axisX, float axisY,float pointLocX,float PointLocY)
{
	//CVector d(pointLocX - ellipseLocX, PointLocY - ellipseLocY, 0.0);
	//CVector e(axisX * d.Unit().X(), axisY * d.Unit().Y());
	
	float dx = pointLocX - ellipseLocX;
	float dy = PointLocY - ellipseLocY;
	float dm = std::sqrt(dx * dx + dy * dy);
	
	float ex = axisX * (dx / dm);// d.Unit().X();
	float ey = axisY * (dy / dm);//d.Unit().Y();
	float em = std::sqrt(ex * ex + ey * ey);
	
	if(dm <= em)
		return true;

	return false;
}



/*!
	NLIsEllipseInEllipse()
	
	@brief	Tests if two ellipses intersect.
______________________________________________________________________________*/
bool nsl::ellipse_in_ellipse(float x1, float y1, float axisX1, float axisY1,float x2, float y2, float axisX2, float axisY2)
{
	for(double angle = 0.0; angle < 2.0*3.14159; angle += 3.14159/4.0)
	{
		if(nsl::pt_in_ellipse(x1, y1, axisX1, axisY1, x2 + (axisX2 * (float)std::cos(angle)), y2 + (axisY2 * (float)std::sin(angle))))
			return true;
	}
	return false;
}
