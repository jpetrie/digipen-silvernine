
#include "precompiled.h"
#include "CSprite.h"
//#include "CMemoryMgrS.h"

CSprite::CSprite():frame_delay(0), frame_delay_counter(0) { }
CSprite::CSprite(float x0, float y0, 
				float width, float height, 
				std::string sprc_tag, 
				bool anim,
				int sequence,
				int facing,
				int init_frame)
:isAnimated(anim), Sequence(sequence), frame(init_frame), current_facing(facing),
frame_delay(10), frame_delay_counter(0) 
{
	SetWorldX(x0);
	SetWorldY(y0);
	//SetWidth(width);
	//SetHeight(height);
	SetVisible(true);
	SetZOrder(y0);
	CTag_sprc *sTag = rcast<CTag_sprc*>(CTagMgr->Unarchive(kTag_sprc,sprc_tag));
	SetWidth((float)sTag->Sequence[sequence].frameWidth);
	SetHeight((float)sTag->Sequence[sequence].frameHeight);
	Textures = sTag->GetTextureSet();
	base_frame = current_facing * GetFramesPerFace();
	max_frame = base_frame + (GetFramesPerFace() - 1);
	frame += (unsigned char)base_frame;
}
CSprite::CSprite(float x0, float y0, 
				float width, float height, 
				CTag_sprc *sTag, 
				bool anim,
				int sequence,
				int facing,
				int init_frame)
:isAnimated(anim), Sequence(sequence), frame(init_frame), current_facing(facing),
frame_delay(10), frame_delay_counter(0) 
{
	SetWorldX(x0);
	SetWorldY(y0);
	//SetWidth(width);
	//SetHeight(height);
	SetVisible(true);
	SetZOrder(y0);
	SetWidth((float)sTag->Sequence[sequence].frameWidth);
	SetHeight((float)sTag->Sequence[sequence].frameHeight);
	Textures = sTag->GetTextureSet();
	base_frame = current_facing * GetFramesPerFace();
	max_frame = base_frame + (GetFramesPerFace() - 1);
	frame += (unsigned char)base_frame;
}

//#ifdef __MEM_DBG__
//	void * operator new(size_t sz);
//	void operator delete(void *p);
//#/endif

// copy constructor
CSprite::CSprite(CSprite& t)
{
	
	Textures = t.Textures;
	isAnimated = t.isAnimated;
	SetWorldX(t.GetWorldX());
	SetWorldY(t.GetWorldY());
	SetWidth(t.GetWidth());
	SetHeight(t.GetHeight());
	frame = t.frame;
	Sequence = t.Sequence;
	frame_delay = t.frame_delay;
	frame_delay_counter = t.frame_delay_counter;
	SetVisible(t.IsVisible());
	current_facing = t.current_facing;
	base_frame = t.base_frame;
	max_frame = t.max_frame;
}

// destructor
CSprite::~CSprite() { }

// assignment operator
CSprite& CSprite::operator=(CSprite& t)
{
	Textures = t.Textures;
	isAnimated = t.isAnimated;
	SetWorldX(t.GetWorldX());
	SetWorldY(t.GetWorldY());
	SetWidth(t.GetWidth());
	SetHeight(t.GetHeight());
	frame = t.frame;
	Sequence = t.Sequence;
	frame_delay = t.frame_delay;
	frame_delay_counter = t.frame_delay_counter;
	SetVisible(t.IsVisible());
	current_facing = t.current_facing;
	base_frame = t.base_frame;
	max_frame = t.max_frame;
	return *this;
	
}

// mutators
void CSprite::SetAnim(bool anim)				{ isAnimated = anim; }
void CSprite::SetInitFrame(unsigned char f)		{ frame = f; }
void CSprite::SetSequence(int sequence, unsigned char init_frame)	
{ 
	Sequence = sequence;	
	frame = init_frame; 
	base_frame = current_facing * GetFramesPerFace();
	max_frame = base_frame + (GetFramesPerFace() - 1);
}
void CSprite::SetFrameDelay(int ticks){ frame_delay = ticks; }
void CSprite::SetFacing(int facing)																
{ 
	current_facing = facing; 
	base_frame = current_facing * GetFramesPerFace();
	max_frame = base_frame + (GetFramesPerFace() - 1);
	frame += (unsigned char)base_frame;
}

// accessors
int CSprite::GetSequenceCount(void)		{ return (int)Textures.size(); }
int CSprite::GetSequence(void)					{ return Sequence; }
int CSprite::GetFaceCount(void)				{ return Textures[Sequence].GetFacings(); }
int CSprite::GetFramesPerFace(void)		{ return Textures[Sequence].GetFramesPerFacing(); }
int CSprite::GetIsAnimated(void)				{ return isAnimated; }
int CSprite::GetCurrentFrame(void)			{ return frame; }
int CSprite::GetFrameDelay(void)				{ return frame_delay; }
int CSprite::GetFacing(void)						{ return current_facing; }
void CSprite::Draw(void)
{

	if(!IsVisible())
		return;

	GLenum GLerror;
	while( (GLerror = glGetError()) != GL_NO_ERROR)
		;

	if(isAnimated)
	{
		if( frame > max_frame )
			frame = (unsigned char)base_frame;
		Textures[Sequence].Bind(frame);
				
		if(frame_delay_counter > frame_delay)
		{
			++frame;
			frame_delay_counter = 0;
		}
		++frame_delay_counter;
	}
	else 
		Textures[Sequence].Bind(frame);

	// actual plot coordinates
	float drawX = GetWorldX();
	float drawY = GetWorldY();
	//drawY = (float)y / 128;	// offset vertically for tiling
	//drawX = (float)x / 128;

	glBegin(GL_QUADS);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( drawX, drawY, 0.0f);				// bottom-left
		glTexCoord2f(1.0f, 0.0f); glVertex3f( drawX + GetWidth() , drawY, 0.0f);			// bottom-right
		glTexCoord2f(1.0f, 1.0f); glVertex3f( drawX + GetWidth(),  drawY + GetHeight(), 0.0f);				// top-right
		glTexCoord2f(0.0f, 1.0f); glVertex3f( drawX,  drawY + GetHeight(), 0.0f);					// top-left
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnd();


}

#ifdef __MEM_DBG__
void * CSprite::operator new(size_t sz)
{
	sz;
	return CMemoryMgr->AllocSprite();
}
void CSprite::operator delete(void *p)
{
	CMemoryMgr->FreeSprite(p);
}
#endif
