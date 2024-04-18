/*!
	@file		SNvector.h
	@author	Scott Smith	
	@par		email: ssmith@digipen.edu
	@par		DP Login: ssmith
	@date		July 15, 2003
	@brief	abstracts a vector arithmetic class
_________________________________________________________________________________*/

#ifndef _SNVECTOR_H_
#define _SNVECTOR_H_

#pragma warning(disable: 4786)
#include <cmath>	/* sqrt */
#pragma warning(default: 4786)
const double R2D = 180.0 / 3.1415926535897932384626433832795;

/*!
	@class	Point
	@brief	Represents a 3-dimensional point
__________________________________________________________________________________*/
class Point
{
public:
	Point(double a = 0, double b = 0, double c = 0): x(a), y(b), z(c) { }
	~Point() {}
	
	double x, y, z;
private:
};

/*!
	@class	CVector
	@brief	Represents a 3-dimensional vector.

		A two dimensional vector can be abstracted by neglecting the
		z coordinate.

	Operations:

	-	Add two vectors
	-	Subtract two vectors
	-	Scale a vector by a scalar
	-	Calcultate the Dot Product of two vectors
	-	Calculate the Cross Product of two vectors
	-	Calculate the unit vector of a vector
	-	Calculate the Normal vector of a 2D vector (use cross product for 3D)
	-	Calculate a vector's magnitude
__________________________________________________________________________________*/
class CVector
{
public:

/*******************************************************************
************************* constructors *****************************
********************************************************************/
	
/*!
	CVector::CVector
	Default Constructor
	@param x	The displacement along the x-axis
	@param y	The displacement along the y-axis
	@param z	The displacement along the z-axis
	@brief		Initializes the members of the CVector
____________________________________________________________________*/
	CVector(double x = 0.0, double y = 0.0, double z = 0.0) 
	{	
		v.x = x;
		v.y = y;
		v.z = z;
				
		m = Magnitude();
		u = Normalize();
		if(v.z == 0 && Magnitude())
		{
			n.x = (-v.y) / m;
			n.y = (v.x) / m;
		}
	}
/*!
	CVector::CVector
	Constructor
	@param p1	a Point
	@param p2	another Point
	@brief		Initializes the members of the CVector
____________________________________________________________________*/
	CVector(Point p1, Point p2) 
	{	
		v.x = p2.x - p1.x;
		v.y = p2.y - p1.y;
		v.z = p2.z - p1.z;
				
		m = Magnitude();
		u = Normalize();
		if(v.z == 0 && Magnitude())
		{
			n.x = (-v.y) / m;
			n.y = (v.x) / m;
		}
	}
/*!
	CVector::CVector
	Copy Constructor
	@param w	A CVector to be copied
	@brief		copies 'w' to 'this' CVector
____________________________________________________________________*/
	CVector(const CVector& w)
	{
		v = w.v;
		n = w.n;
		u = w.u;
		m = w.m;
	}
/*******************************************************************
************************* destructor *******************************
********************************************************************/
/*!
	CVector::~CVector
	Destructor
	@brief	no cleanup necessary with this class
______________________________________________________________________*/
	~CVector() {}

/*******************************************************************
*************************** operators ******************************
********************************************************************/
	
/*!
	CVector::operator=
	Assignment operator
	@param w	A CVector to be copied
	@brief		copies 'w' to 'this' CVector
____________________________________________________________________*/
	CVector& operator=(const CVector& w)
	{
		v = w.v;
		n = w.n;
		u = w.u;
		m = w.m;
		return *this;
	}

	CVector operator+(CVector&);		// vector addition
	CVector& operator+=(CVector&);	// vector addition
	CVector operator-(CVector&);		// vector subtraction
	CVector& operator-=(CVector&);	// vector subtraction
	CVector operator*(double);			// scale by k
	CVector& operator*=(double);		// scale by k
	CVector operator/(double);			// scale by 1/k
	CVector& operator/=(double);		// scale by 1/k
	CVector operator^(CVector&);		// cross product
	CVector& operator^=(CVector&);	// cross product
	double operator*(CVector&);			// dot product

/*******************************************************************
*************************** accessors ******************************
********************************************************************/

	CVector Unit(void);
	CVector Normal(void);
	double Magnitude(void);
	char Sign(void) { return (v.z > 0) ? -1 : 1; }

/*!
	CVector::AngleR
	@pararm w		A CVector to be used in an angle calculation
	@return			The angle between 'this' and w in radians
_____________________________________________________________________*/
	double AngleR(CVector& w)
	{ return (Magnitude() && w.Magnitude()) ? 
						std::acos((*this *w) / (Magnitude() * w.Magnitude())): 0; }
/*!
	CVector::AngleD
	@pararm w		A CVector to be used in an angle calculation
	@return			The angle between 'this' and w in degrees
_____________________________________________________________________*/
	double AngleD(CVector& w)
	{ return (Magnitude() && w.Magnitude()) ? 
						std::acos((*this * w) / (Magnitude() * w.Magnitude())) * R2D: 0; }
/*!
	CVector::Sin
	@pararm w		A CVector to be used in an angle calculation
	@return			The sine of the angle between 'this' and w
_____________________________________________________________________*/
	double Sin(CVector& w) 
	{ return (Magnitude() && w.Magnitude()) ? 
						(*this ^ w).Magnitude() / (Magnitude() * w.Magnitude()) : 0; }
/*!
	CVector::Cos
	@pararm w		A CVector to be used in an angle calculation
	@return			The cosine of the angle between 'this' and w
_____________________________________________________________________*/
	double Cos(CVector& w)
	{ return (Magnitude() && w.Magnitude()) ? 
						((*this * w) / (Magnitude() * w.Magnitude())): 0; }
/*!
	CVector::X
	@pararm w		A CVector to be used in an angle calculation
	@return			The cosine of the angle between 'this' and w
_____________________________________________________________________*/
	double X(void)const	{ return v.x;  }
	/*!
	CVector::X
	@pararm w		A CVector to be used in an angle calculation
	@return			The cosine of the angle between 'this' and w
_____________________________________________________________________*/
	double Y(void)const	{ return v.y;  }

	
private:
	/// the actual vector
	Point v;
	/// the normal to the vector, normalized
	Point n;
	/// the normalized expression of the current vector
	Point u;
	/// the magnitude of the vector
	double m;
	// normalizes the current vector
	Point Normalize(void);
};

#endif