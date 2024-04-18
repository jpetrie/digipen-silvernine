/*!
	@file		SNsprite.h
	@author	Scott Smith
	@date		July 8, 2003

	@brief	Defines a CSprite class as part of the SN graphics library
_______________________________________________________________________*/

#ifndef __SNSPRITE_H__
#define __SNSPRITE_H__

#include <string>
#include "CTexture.h"
#include "CGraphicsObject.h"

#include "CTagMgrS.h"

#include "CTag_sprc.h"
//#include "MemDebug.h"


class CSprite: public CGraphicsObject
{
public:
	
	// constructors
	CSprite();
	CSprite(float x0, float y0, 
			float width, float height, 
			std::string sprc_tag, 
			bool anim = false,
			int sequence = 0,
			int facing = 0,
			int init_frame = 0);
	CSprite(float x0, float y0, 
			float width, float height, 
			CTag_sprc *sTag, 
			bool anim =false,
			int sequence = 0,
			int facing = 0,
			int init_frame = 0);

//#ifdef __MEM_DBG__
//	void * operator new(size_t sz);
//	void operator delete(void *p);
//#/endif

	// copy constructor
	CSprite(CSprite& t);

	// destructor
	virtual ~CSprite();

	// assignment operator
	CSprite& operator=(CSprite& t);

	virtual void Draw(void);

	// mutators
	void SetAnim(bool anim);
	void SetInitFrame(unsigned char f);
	void SetSequence(int sequence, unsigned char init_frame);
	void SetFrameDelay(int ticks);
	void SetFacing(int facing);

	// accessors
	int GetSequenceCount(void);
	int GetSequence(void);
	int GetFaceCount(void);
	int GetFramesPerFace(void);
	int GetIsAnimated(void);
	int GetCurrentFrame(void);
	int GetFrameDelay(void);
	int GetFacing(void);

private:
// texture set which the sprite draws from
	std::vector< CTexture > Textures;
// determines whether the sprite is animated
	bool isAnimated;
	int Sequence;
// the current frame being used for display
	int frame;
// number of game loops delayed before updating an animation
	int frame_delay;
// keeps track of how many game loops have occured since the last frame swap
	int frame_delay_counter;
// the facing in the current sequence
	int current_facing;
//
	int base_frame;
//
	int max_frame;

};

#endif
