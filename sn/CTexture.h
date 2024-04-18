/*!
	@file	SNtexture.h
	@author	Scott Smith
	@date	June 30, 2003

	@brief	Defines a class for tile map handling
___________________________________________________________*/

#ifndef __SNTEXTURE_H__
#define __SNTEXTURE_H__

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#include <vector>

class CTexture
{
public:
	CTexture(int f = 0);
	virtual ~CTexture();
	CTexture(const CTexture& t);

//#ifdef __MEM_DBG__
//	void * operator new(size_t sz);
//	void * operator new[](size_t sz, int ct);
//	void operator delete(void *p);
//	void operator delete[](void *p);
//#endif
	
	void Bind(int frame); 
	
	void Create(std::vector<GLuint> vtlist);

	bool operator==(CTexture& t);

	void SetFacings(int faces);
	void SetFramesPerFacing(int fpf);

	int GetFacings(void);
	int GetFramesPerFacing(void);


	GLuint operator[](int t);

	size_t Frames(void);
	
	CTexture & operator=(const CTexture &t);

private:
	GLuint current_frame;
	std::vector< GLuint > Texture_List;
	GLuint texture;
	int facings;
	int frames_per_facing;
	void Build_List(void);

};	

#endif
