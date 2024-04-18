
#include "precompiled.h"
#include "CTexture.h"

/*#include "CMemoryMgrS.h"

#ifdef __MEM_DBG__
void * CTexture::operator new(size_t sz)
	{
		sz;
		return CMemoryMgr->AllocTexture();
	}
	void CTexture::operator delete(void *p)
	{
		CMemoryMgr->FreeTexture(p);
	}
#endif
	*/
CTexture::CTexture(int f):current_frame(f) { }
CTexture::~CTexture() 
{
	Texture_List.clear();
}
CTexture::CTexture(const CTexture& t)
{
	current_frame = t.current_frame;
	Texture_List = t.Texture_List;
	texture = t.texture;
	facings = t.facings;
	frames_per_facing = t.frames_per_facing;
}

void CTexture::Bind(int frame)
{
	if(Texture_List[frame] == current_frame)
		return;
		
	glBindTexture(GL_TEXTURE_2D, Texture_List[frame]);
	current_frame = frame;
}

void CTexture::Create(std::vector<GLuint> vtlist)
{
	Texture_List = vtlist;
}

bool CTexture::operator==(CTexture& t)
{
	if(Texture_List == t.Texture_List)
		return true;
	else
		return false;
}

void CTexture::SetFacings(int faces) { facings = faces; }
void CTexture::SetFramesPerFacing(int fpf) { frames_per_facing = fpf; }

int CTexture::GetFacings(void) { return facings; }
int CTexture::GetFramesPerFacing(void) { return frames_per_facing; }


GLuint CTexture::operator[](int t) { return Texture_List[t]; }

size_t CTexture::Frames(void) { return Texture_List.size(); }

CTexture & CTexture::operator=(const CTexture &t)
{
	current_frame = t.current_frame;
	Texture_List = t.Texture_List;
	texture = t.texture;
	facings = t.facings;
	frames_per_facing = t.frames_per_facing;
	return *this;
}