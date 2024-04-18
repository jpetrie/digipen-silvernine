/*! =========================================================================
      
      @file    nsl_tools_math.h
      @brief   Math tools interface.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _NSL_TOOLS_MATH_H_
#define _NSL_TOOLS_MATH_H_


/*                                                                   includes
----------------------------------------------------------------------------- */
                
#include "nsl_common.h"

namespace nsl
{


/*                                                                   structs
----------------------------------------------------------------------------- */

template< typename T_ >
struct point2D
//! Represents a two-dimensional point.
{
  T_  x;
  T_  y;
};


/*                                                                 prototypes
----------------------------------------------------------------------------- */

// clamping
template< typename T_ > void clampval(T_ &val,T_ low,T_ hi);

// intersection test
template< typename T_ > bool pt_in_rect(T_ x,T_ y,T_ l,T_ t,T_ r,T_ b);

bool pt_in_ellipse(float ellipseLocX,float ellipseLocY,float axisX, float axisY,float pointLocX,float PointLocY);
bool ellipse_in_ellipse(float x1, float y1, float axisX1, float axisY1,float x2, float y2, float axisX2, float axisY2);


// random
int   randint(int min,int max);
float randfloat(float min,float max);


/*                                                                  functions
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
template< typename T_ >
void clampval(T_ &val,T_ low,T_ hi)
/*! @brief 
*/
{
  if(val >= hi)
    val = hi;
  if(val <= low)
    val = low;
}


/*  _________________________________________________________________________ */
template< typename T_ >
bool pt_in_rect(T_ x,T_ y,T_ l,T_ t,T_ r,T_ b)
/*! @brief Determines if a given point is within a given rectangle.

    If the point is on the edge of the rectangle, it is considered within the
    rectangle. pt_in_rect() interprets its coordinates as belonging to a
    Cartesian coordinate system.

    @param x  X coordinate of the point to test.
    @param y  Y coordinate of the point to test.
    @param l  Left coordinate of the rectangle.
    @param t  Top coordinate of the rectangle.
    @param r  Right coordinate of the rectangle.
    @param b  Bottom coordinate of the rectangle.
    
*/
{
T_ &lx = (l < r ? l : r);
T_ &hx = (l < r ? r : l);
T_ &ly = (b < t ? b : t);
T_ &hy = (b < t ? t : b);

  return (x >= lx && x <= hx && y >= ly && y <= hy);
}


}       /* namespace nsl */
#endif  /* _NSL_TOOLS_MATH_H_ */
