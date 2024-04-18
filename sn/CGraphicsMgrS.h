/*!
	@file	SNgraphics.h
	@author	Scott Smith
	@date	June 30, 2003

	@brief	Defines a class for the graphics manager
___________________________________________________________*/


#ifndef __SNGRAPHICS_H__
#define	__SNGRAPHICS_H__

#include "precompiled.h"

#include "CConfigMgrS.h"

#include "CTag_sprc.h"
#include "CTagFactory.h"

#include "CTexture.h"


class CQuadTree;
struct QNode;
//using std::string;  jpetrie removed  (namespace pollution)

const int COLOR_DEPTH	= 4;

class CSprite;
class PointFloat
{
public:
  PointFloat(float ix = 0,float iy = 0,float iz = 0) : x(ix),y(iy),z(iz) { };
  float x;
  float y;
  float z;
};

nsl::point2D< float >  ScreenToWorld(int x, int y);

class CGraphicsMgrS: public nsl::singleton< CGraphicsMgrS >
{
	friend class CGraphicsObject;

public:
	CGraphicsMgrS(LRESULT (CALLBACK *pWndProc)(HWND, UINT, WPARAM, LPARAM) = 0)
		:fp(pWndProc), scrollrate(64.0), zoomrate(.05f), fullscreen(CConfigMgr->GetValueAsBool("gfx_fullscreen" )), gCam(1.0f),
		gX(0.0f), gY(0.0f), WindowWidth(CConfigMgr->GetValueAsInt("gfx_resx")), WindowHeight(CConfigMgr->GetValueAsInt("gfx_resy")),
		ColorDepth(32), mxThresh(60), myThresh(60), new_ticks_(0), ticks_(0), frames_(0),
		old_ticks_(GetTickCount()), Tree(0), CurrTexture(0), minimap(0)
	{
		if(pWndProc)
			Init();
	}
	

	~CGraphicsMgrS() 
	{
		
	}

	bool Init(void)
	{
		if(CreateGLWindow("Silver Nine", WindowWidth, WindowHeight, ColorDepth, fullscreen))
			return true;
		return false;
	}
	GLvoid KillGLWindow(GLvoid);

	int ProcessGraphics(GLvoid);	
	GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
	void SortTree(void);
	void SortList(void);
	void LoadTextureFiles(void);
  	
	// zoom in on the scene	
	void SetZoom(float z)//jpetrie added to set zoom correctly at the beginning of the level.
	{
	  gCam = z;
	  ReSizeGLScene(WindowWidth,WindowHeight);	
	}
	
	
	void ZoomIn(void)		
	{	
		gCam -= zoomrate; 
		
		if(gCam < 1.5)
			gCam = 1.5;
		ReSizeGLScene(WindowWidth, WindowHeight);	
	}	
	
	// zoom out of the scene
	void ZoomOut(void)		
	{ 
		gCam += zoomrate; 
		if(gCam > 2.5)
			gCam = 2.5;
		ReSizeGLScene(WindowWidth, WindowHeight);
		
	}	
	void ScrollRight(void)	
	{ 
		gX -= scrollrate; 
		
	}
	
	void Reset(void) { gX = 0; gY = 0; SetZoom(1.0f); }
	void ScrollLeft(void)	
	{ 
		gX += scrollrate; 
		if(gX > 0)
			gX = 0;
	}
	void ScrollUp(void)		{ gY -= scrollrate; }
	void ScrollDown(void)	
	{ 
		gY += scrollrate;
		if(gY > 0)
			gY = 0;
	}
	bool isFullscreen(void) { return fullscreen;	}
	void SetFullScreen(bool full) { fullscreen = full; }
	int Width(void)			{ return WindowWidth;	}
	int Height(void)		{ return WindowHeight;	}
	const int xThresh(void)		{ return mxThresh; }
	const int yThresh(void)		{ return myThresh; }
	size_t GetItemCount(void) { return DrawList.size(); } 
	const float gx(void) { return (const float)gX; }
	const float gy(void) { return (const float)gY; }
	const float gcam(void) { return (const float)gCam; }
	HDC *getDeviceContext(void)	{ return &hDC; }
	bool isTree(void) { return (Tree ? true : false); }
	void BuildQuadTree(int minx, int miny, int maxx, int maxy);
	void KillQuadTree(void);
	void PopulateFull(void);		// does a point check on every graphical object
	void PopulatePartial(QNode *);	// does a point check within a particular node
	void AddMapTile(CSprite *tile);
	
	void UnloadMap(void)
	{
		MapList.clear();
	}
	GLuint GetCurrentTexture(void) { return CurrTexture; }
	void SetCurrentTexture(GLuint texture = 0) { CurrTexture = texture; }

	CSprite *minimap;
private:
	// windows event handler callback
	LRESULT (CALLBACK *fp)(HWND, UINT, WPARAM, LPARAM);
	// drawable objects in scope
	std::vector<CGraphicsObject*> DrawList;
	std::vector<CGraphicsObject*> MapList;
	CQuadTree	*Tree;
	GLuint CurrTexture;
	// camera variables
	float scrollrate;
	float zoomrate;
	float gCam;
	float gX, gY;
	const int mxThresh;
	const int myThresh;
	// window variables
	int WindowWidth; 
	int WindowHeight;
	bool fullscreen;
	BYTE ColorDepth;
	
	// device state variables
	HDC			hDC;			// device context
	HGLRC		hRC;			// rendering context
	HWND		hWnd;			// window handle
	HINSTANCE	hInstance;		// Holds The Instance Of The Application

	// frame rate variables
	DWORD new_ticks_;
	DWORD old_ticks_;
	DWORD ticks_;
	DWORD frames_;

	// private functions
	bool InitGL();
	bool CreateGLWindow(char* title, int width, int height, BYTE bits, bool fullscreenflag);
	CGraphicsMgrS & operator=(const CGraphicsMgrS &g);
	void AddToList(CGraphicsObject*);
	void RemoveFromList(CGraphicsObject*);
	
};

#define CGraphicsMgr (CGraphicsMgrS::instance())


#endif