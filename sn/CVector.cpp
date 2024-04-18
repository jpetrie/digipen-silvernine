/*!
	@file		SNvector.cpp
	@author	Scott Smith	
	@par		email: ssmith@digipen.edu
	@par		DP Login: ssmith
	@date		July 15, 2003
	@brief	implementation for a vector arithmetic class
_________________________________________________________________________________*/

#include "precompiled.h"
#include "CVector.h"

/*******************************************************************
*************************** operators ******************************
********************************************************************/
/*!
	CVector::operator+
	@param w	A reference to a vector to be added
	@return		A CVector
	@brief		Adds two CVectors together
___________________________________________________________________*/
CVector CVector::operator+(CVector& w)
{
	CVector p;
	p.v.x = v.x + w.v.x;
	p.v.y = v.y + w.v.y;
	p.v.z = v.z + w.v.z;
	p.m = p.Magnitude();
	p.u = p.Unit().v;
	p.n = p.Normal().v;
	return p;
}
/*!
	CVector::operator+=
	@param w	A reference to a vector to be added
	@return		A CVector
	@brief		Adds two CVectors together
___________________________________________________________________*/
CVector& CVector::operator+=(CVector& w)
{
	v.x = v.x + w.v.x;
	v.y = v.y + w.v.y;
	v.z = v.z + w.v.z;
	m = Magnitude();
	u = Unit().v;
	n = Normal().v;
	return *this;
}
/*!
	CVector::operator-
	@param w	A reference to a vector to be subtracted
	@return		A CVector
	@brief		subtracts two CVectors
___________________________________________________________________*/
CVector CVector::operator-(CVector& w)
{
	CVector p;
	p.v.x = v.x - w.v.x;
	p.v.y = v.y - w.v.y;
	p.v.z = v.z - w.v.z;
	p.m = p.Magnitude();
	p.u = p.Unit().v;
	p.n = p.Normal().v;
	return p;
}
/*!
	CVector::operator-=
	@param w	A reference to a vector to be subtracted
	@return		A CVector
	@brief		subtracts two CVectors
___________________________________________________________________*/
CVector& CVector::operator-=(CVector& w)
{
	v.x = v.x - w.v.x;
	v.y = v.y - w.v.y;
	v.z = v.z - w.v.z;
	m = Magnitude();
	u = Unit().v;
	n = Normal().v;
	return *this;
}
/*!
	CVector::perator^
	@param w	A reference to a vector to 'crossed'
	@return		A CVector normal to 'this' and t
	@brief		performs the cross product of two vectors
___________________________________________________________________*/
CVector CVector::operator^(CVector& w)
{
	CVector t;
	t.v.x = (v.y * w.v.z) - (v.z * w.v.y);
	t.v.y = (v.z * w.v.x) - (w.v.z * v.x);
	t.v.z = (v.x * w.v.y) - (w.v.x * v.y);
	t.m = t.Magnitude();
	t.u = t.Unit().v;
	t.n = t.Normal().v;
	return t;
}
/*!
	CVector::operator^=
	@param w	A reference to a vector to 'crossed'
	@return		A CVector normal to 'this' and t
	@brief		performs the cross product of two vectors
___________________________________________________________________*/
CVector& CVector::operator^=(CVector& w)
{
	CVector t;
	t.v.x = (v.y * w.v.z) - (v.z * w.v.y);
	t.v.y = (v.z * w.v.x) - (w.v.z * v.x);
	t.v.z = (v.x * w.v.y) - (w.v.x * v.y);
	v = t.v;
	m = Magnitude();
	u = Unit().v;
	n = Normal().v;
	return *this;
}
/*!
	CVector::operator*
	@param k	A scalar to scale 'this' vector
	@return		a scaled vector with the same direction
	@brief		Scales a vector by 'k'
___________________________________________________________________*/
CVector CVector::operator*(double k)
{
	CVector p;
	p.v.x = v.x * k;
	p.v.y = v.y * k;
	p.v.z = v.z * k;
	p.m = p.Magnitude();
	p.u = p.Unit().v;
	p.n = p.Normal().v;
	return p;
}
/*!
	CVector::operator*=
	@param k	A scalar to scale 'this' vector
	@return		a scaled vector with the same direction
	@brief		Scales a vector by 'k'
___________________________________________________________________*/
CVector& CVector::operator*=(double k)
{
	v.x = v.x * k;
	v.y = v.y * k;
	v.z = v.z * k;
	m = Magnitude();
	u = Unit().v;
	n = Normal().v;
	return *this;
}
/*!
	CVector::operator/
	@param k	A scalar to scale 'this' vector
	@return		a scaled vector with the same direction
	@brief		Scales a vector by '1/k'
___________________________________________________________________*/
CVector CVector::operator/(double k)
{
	CVector p;
	p.v.x = v.x / k;
	p.v.y = v.y / k;
	p.v.z = v.z / k;
	p.m = p.Magnitude();
	p.u = p.Unit().v;
	p.n = p.Normal().v;
	return p;
}
/*!
	CVector::operator/=
	@param k	A scalar to scale 'this' vector
	@return		a scaled vector with the same direction
	@brief		Scales a vector by '1/k'
___________________________________________________________________*/
CVector& CVector::operator/=(double k)
{
	v.x = v.x / k;
	v.y = v.y / k;
	v.z = v.z / k;
	m = Magnitude();
	u = Unit().v;
	n = Normal().v;
	return *this;
}
/*!
	CVector::operator*
	@param w	A reference to a vector to be 'dotted'
	@return		the dot product of 'this' and t
	@brief		Performs the dot product of 'this' and t
___________________________________________________________________*/
double CVector::operator*(CVector& w)
{
	return ((v.x * w.v.x) + (v.y * w.v.y) + (v.z * w.v.z));
}


/*******************************************************************
*************************** accessors ******************************
********************************************************************/

/*!
	CVector::Unit
	@return		a CVector expressing 'this' as a unit vector
	@brief		normalizes 'this' (magnitude of 1) 
___________________________________________________________________*/
CVector CVector::Unit(void)
{
	CVector w;
	w.u.x = w.v.x = v.x / m;
	w.u.y = w.v.y = v.y / m;
	w.u.z = w.v.z = v.z / m;
	w.m = 1;
	w.n = w.Normal().v;
	return w;
}
/*!
	CVector::Normal
	@return		a CVector expressing a vector orthogonal to 'this'
	@brief		calculates a vector orthogonal(normal) to 'this'
___________________________________________________________________*/
CVector CVector::Normal(void)
{
	CVector n;
	if(v.z == 0)
	{
		n.u.x = n.v.x = (-v.y) / m;
		n.u.y = n.v.y = (v.x) / m;
		n.u.z = n.v.z = 0;
		n.n.x = v.x / m;
		n.n.y = v.y / m;
		n.m = n.Magnitude();
	}
	return n;
}
/*!
	CVector::Magnitude
	@return		the magnitude(length) of 'this' vector
	@brief		Calculates the magnitude of 'this' vector using 
						the distance(pythagorean) formula
___________________________________________________________________*/
double CVector::Magnitude(void)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

/*!
	CVector::Normalize
	@return		a Point scaled by the inverse of the vector's magnitude
	@brief		Provides easy internal calculation of a normalization
___________________________________________________________________*/
Point CVector::Normalize(void)
{
	Point p;
	if(m)
	{
		p.x = v.x / m;
		p.y = v.y / m;
		p.z = v.z / m;
	}
	return p;
}