/*!
	@file	SNgraphics.cpp
	@author	Scott Smith

	@brief	Implements the methods defined for the OpenGL graphics manager
______________________________________________________________________________*/

#include "precompiled.h"
#include "CGraphicsMgrS.h"
#include "CGraphicsObject.h"
//#include "CMap.h"
//#include "CVector.h"
#include "CText.h"
#include "CLine.h"
#include "CRect.h"
#include "CSprite.h"
//#include "CTile.h"
#include "NSL.h"
#include "CQuadTree.h"
#include "nsl_exception.h"
    #include "CSprite.h"
#if defined (_MSC_VER)
#include "CGameEngine.h"
#endif

#define TILE_HEIGHT 128

double theta = 0.0;
PointFloat pd;

#define TILE_HEIGHT 128
#define TILE_WIDTH 64

#ifdef NSL_VC
#pragma warning(disable: 4505)
#pragma warning(disable: 4706)
#endif

static AUX_RGBImageRec * LoadBMP(char *Filename);

/*!
	CGraphicsMgrS::InitGL
	
	@brief OpenGL initialization function
	
	This function ensures that the textures in load properly, and 
	initializes the OpenGL environment
__________________________________________________________________________*/
bool CGraphicsMgrS::InitGL()										
{
	glEnable(GL_TEXTURE_2D);								// enable 2d texturs
	glEnable(GL_BLEND);										// enable alpha blending
	//glShadeModel(GL_SMOOTH);								// Enable Smooth Shading
	glClearColor(0.75f, 0.75f, 0.75f, 1.f);				//jpetrie light grey background
	
	glClearDepth(1.0f);									
	//glEnable(GL_DEPTH_TEST);								// enable use of depth buffer
	//glDepthFunc(GL_LEQUAL);									// function used for depth calculations
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		// Alpha blending
	//glHint(GL_DONT_CARE, GL_FASTEST);						// for fast processing - high detail not required
	//glEnable(GL_CULL_FACE);									// enable automatic face culling
	//glCullFace(GL_BACK);									// culling mode - don't draw back faces
	glPointSize(1.0);										// point size default to 1x1 pixel
	glLineWidth(1.0);										// lines default to 1 pixel wide
	
	return true;											// Initialization Went OK
}


/*!
	CGraphicsMgrS::ProcessGraphics()
	
	@brief Processes the graphical objects in the game, and displays them
	
_________________________________________________________________________*/
int CGraphicsMgrS::ProcessGraphics(GLvoid)									
{
	if(Tree == 0)
	{	
		SwapBuffers(hDC);
		return true;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity();										// Reset The Current Modelview Matrix
	
	// set the camera location - no zoom
	glTranslatef(gX ,gY, 0);						
	
	glFlush();

	int XRes = Tree->GetXStep();
	int YRes = Tree->GetYStep();
	int x, y;
	QNode* where;
	
	// tracks the frame rate - 
	new_ticks_ = GetTickCount();
	ticks_ += (new_ticks_ - old_ticks_);
	double fps = 1.0 / (/*(double)*/(new_ticks_ - old_ticks_)/1000.0);
	old_ticks_ = new_ticks_;
	++frames_;
	//double fps = (double)frames_ / ((double)(GetTickCount() - ticks_)/1000.0);
	//std::cout << Tree->GetXStep() << ", " << Tree->GetYStep() << std::endl;
	//std::cout << "fps: " << fps << std::endl;
	char buf[10];
	nsl::point2D<float> pt = ScreenToWorld(10,Height() / 8);
	std::sprintf(buf, "%d", (int)fps);
	std::string s = buf;
	CText t(s.c_str());
	t.SetWidth(100);
	t.SetHeight(100);
	t.SetLocation(pt.x,pt.y);
	t.SetVisible(true);

	unsigned int i = 0;
	for(x = (int)(-gX - 150); x < (int)(-gX + WindowWidth * gCam + 150); x += 128)
		for(y = (int)(-gY - 150); y < (int)(-gY + WindowHeight * gCam + 150); y += 128)
		{
			where = Tree->TestPoint(x, y);
	

			// draw the map tiles
			//std::sort(where->Objects.begin(), where->Objects.end(), GraphicObjectSort);
			for(i = 0; i < where->Objects.size(); ++i)
			{
				scast<CGraphicsObject*>(where->Objects[i])->Draw();
				//std::cout << "Total: " << MapList.size() << "	Local:" << where->MapTiles.size() << std::endl;
			}
		}
	i = 0;
	std::vector< CRect * > rects;
	std::vector< CArmy* > Teams = CGame->RequestState()->teams;
	for(i = 0; i < Teams.size(); ++i)
		for(int j = 0; j < Teams[i]->GetSizeofActive(); ++j)
			rects.push_back(new CRect(0, 0, 0, 0));

	CRect *viewport = new CRect(0,0,0,0);
	if(minimap)
	{
		//// draw minimap
		nsl::point2D<float> mm = ScreenToWorld(Width() - (.25 * Width()) - 10, .25 * Height() + 10);
		minimap->SetWorldX(mm.x);
		minimap->SetWorldY(mm.y);
		minimap->SetWidth(.25 * gCam * Width());
		minimap->SetHeight(.25 * gCam * Height());
		minimap->SetZOrder(-140000);
		
		nsl::point2D<float> or, ext;
		or.x = mm.x + (-gX)/CGame->RequestState()->map->WorldWidth() * minimap->GetWidth();
		or.y = mm.y + (-gY)/CGame->RequestState()->map->WorldHeight() * minimap->GetHeight();
		ext.x = mm.x + (-gX + Width())/CGame->RequestState()->map->WorldWidth() * minimap->GetWidth();
		ext.y = mm.y + (-gY + Height())/CGame->RequestState()->map->WorldHeight() * minimap->GetHeight();
		viewport->SetWorldX(or.x);
		viewport->SetWorldY(or.y);
		viewport->SetWidth(gCam * (ext.x - or.x));
		viewport->SetHeight(gCam * (ext.y - or.y));
		viewport->SetInteriorColor(1, 1, 0, .3);
		viewport->SetZOrder(-160000);
		//viewport->Draw();

		nsl::point2D<float> upt;
		std::vector< CArmy* > Teams = CGame->RequestState()->teams;
		int uct = 0;
		for(i = 0; i < Teams.size(); ++i)
			for(int j = 0; j < Teams[i]->GetSizeofAvailable(); ++j)
			{
				upt.x = mm.x + (((Teams[i]->GetActiveUnit(j))->X())/CGame->RequestState()->map->WorldWidth()) * minimap->GetWidth();
				upt.y = mm.y + (((Teams[i]->GetActiveUnit(j))->Y())/CGame->RequestState()->map->WorldHeight()) * minimap->GetHeight();
				rects[uct]->SetWorldX(upt.x);
				rects[uct]->SetWorldY(upt.y);
				rects[uct]->SetWidth(5);
				rects[uct]->SetHeight(5);
				rects[uct]->SetInteriorColor(1, 1, 1, 1);
				rects[uct]->SetZOrder(-175000);
				//rects[uct]->Draw();
				uct++;
			}

	}
	
	// draw the other sprites/lines/rectangles/text/...
	try
	{
		std::sort(DrawList.begin(), DrawList.end(), GraphicObjectSort);
		
		for(i = 0; i < DrawList.size(); ++i)
			DrawList[i]->Draw();
		//std::cout << DrawList.size() << std::endl;
	}
	catch(...)
	{
		//CMemTracker::WhereAlloc(DrawList[i]);
		std::cout << DrawList[i] << std::endl;
		std::cout << &t << std::endl;
		RemoveFromList(DrawList[i]);
	//	nlTHROW("Caugth rogue graphics object!");
	}

	//while( (old_ticks_ + 25) > GetTickCount() ) // regulate the frame rate
	//	;

	for(i = 0; i < rects.size(); ++i)
		delete rects[i];
	delete viewport;
	SwapBuffers(hDC);
	glFlush();
	return true;										
}


/*!
	CGraphicsMgrS::ReSizeGLScene()
	
	@brief Adjusts the viewport to the size of the window on resizing,
			it also resets the orthographics projection mode. 
	
_________________________________________________________________________*/
GLvoid CGraphicsMgrS::ReSizeGLScene(GLsizei width, GLsizei height)	
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}
	WindowWidth = width;
	WindowHeight = height;
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// setup Orthographic mode
	glOrtho(0.0f, (float)width * gCam, 0.f, (float)height * gCam, -20.f,20.f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}



/*!
	LoadBMP()
	
	@brief A utility function for loading bitmaps
	
_________________________________________________________________________*/
static AUX_RGBImageRec * LoadBMP(char *Filename)
{
	std::FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File = std::fopen(Filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return 0;//auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}

/*!
	CGraphicsMgrS::KillGLWindow()
	
	@brief Performs cleanup for the closing of the window 
	
_________________________________________________________________________*/
GLvoid CGraphicsMgrS::KillGLWindow(GLvoid)								
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(true);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}

	
}

/*!
	CGraphicsMgrS::CreateGLWindow()
	
	@brief Creates the OpenGL window, and sets up all necessary variables
	
_________________________________________________________________________*/
bool CGraphicsMgrS::CreateGLWindow(char* title, int width, int height, BYTE bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) fp;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;											// Return false
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=false;		// Windowed Mode Selected.  Fullscreen = false
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return false;									// Return false
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		//ShowCursor(false);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return false
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return false
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return false
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return false
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return false
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return false
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return false
	}

	return true;									// Success
}

/*!
	CGraphicsMgrS::LoadTextureFiles()
	
	@brief Loads the strings which represent the texture files into a list,
	which is added to a master list for later use
_________________________________________________________________________*/

/*!
	ScreenToWorld()
	
	@brief converts window coordinates to world coordinates
_________________________________________________________________________*/
nsl::point2D< float > ScreenToWorld(int x, int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( (GLint)winX, (GLint)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

nsl::point2D< float > tResult = { (float)posX, (float)posY };
	return tResult;//PointFloat((float)posX, (float)posY, (float)posZ);
}

void CGraphicsMgrS::AddToList(CGraphicsObject* gObj)
{
	//if(gObj && gObj->IsVisible())
	//{
		std::vector < CGraphicsObject * >::iterator it;
		it = std::find(DrawList.begin(), DrawList.end(), gObj);
		if(it != DrawList.end())
			return;
		DrawList.push_back(gObj);
    //}

}
void CGraphicsMgrS::RemoveFromList(CGraphicsObject * gObj)
{
	std::vector < CGraphicsObject * >::iterator it;
	it = std::find(DrawList.begin(), DrawList.end(), gObj);
	if(it != DrawList.end())
		DrawList.erase(it);
}
void CGraphicsMgrS::SortList(void)
{
   std::sort(DrawList.begin(), DrawList.end(), GraphicObjectSort);
}
/*!
	GraphicObjectSort()
	@param	o1	An object for comparison
	@param	o2	Another object for comparison
	@return	true if o1 is greater than o2, false otherwise

	@brief	Compares two objects, to be used by the STL sort function
______________________________________________________________________________*/
bool GraphicObjectSort( void * o1, void *o2 )
{
	return (*(scast<CGraphicsObject*>(o1)) > *(scast<CGraphicsObject*>(o2)));
}
/*!
	SpriteSort()
	@param	s1	A sprite for comparison
	@param	s2	Another sprite for comparison
	@return	true if s1 is greater than s2, false otherwise

	@brief	Compares two objects, to be used by the STL sort function
______________________________________________________________________________*/
bool SpriteSort( void * s1, void *s2 )
{
	if(scast<CSprite*>(s1)->GetSequence() != scast<CSprite*>(s2)->GetSequence())
		return false;
	if(scast<CSprite*>(s1)->GetFacing() != scast<CSprite*>(s2)->GetFacing())
		return false;
	if(scast<CSprite*>(s1)->GetCurrentFrame() != scast<CSprite*>(s2)->GetCurrentFrame())
		return false;
	return true;
}

void CGraphicsMgrS::BuildQuadTree(int minx, int miny, int maxx, int maxy)
{
	KillQuadTree();

	int dim = (maxx - minx) > (maxy - miny) ? (maxx - minx) : (maxy - miny);
	int depth = (int)(std::log((double)dim/(double)WindowWidth)/std::log(2.0));
	if(depth < 2)
		depth = 2;

	Tree = new CQuadTree(minx, maxx, miny, maxy, depth + 4);
	Tree->BuildTree();
	
}
void CGraphicsMgrS::KillQuadTree(void)
{
	if(Tree)
	{
		delete Tree;
		DrawList.clear();
		Tree = 0;
	}
	
}
void CGraphicsMgrS::AddMapTile(CSprite *tile)
{
	reinterpret_cast<CGraphicsObject *>(tile)->SetVisible(true);
	if(isTree())
	{
		Tree->AddObject((Tree->TestPoint(scast<int>(reinterpret_cast<CGraphicsObject *>(tile)->GetWorldX()), scast<int>(reinterpret_cast<CGraphicsObject *>(tile)->GetWorldY()))), reinterpret_cast<CGraphicsObject *>(tile));	
	}
	//else
	//{	
	//	MapList.push_back((CGraphicsObject*)tile);
	//}
	RemoveFromList((CGraphicsObject*)tile); // remove it from the master draw list
}
void CGraphicsMgrS::SortTree(void) { Tree->SortTree( SpriteSort ); }


