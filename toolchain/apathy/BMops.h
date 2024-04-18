#ifndef NBITMAP_H
#define NBITMAP_H

//#include "csdefs.h"
#include <stdio.h>
#include <assert.h>


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;

#ifdef	_DEBUG
	// Use the normal assert macro in debug builds.
	#define rassert(exp)	assert(exp)
#else
	// Define a custom assert macro in release builds.
	#define rassert(exp) \
				do { \
					if (!(exp)) { \
						__asm { int 3 } \
					} \
				} while (0)
#endif

#ifndef	__cplusplus
typedef unsigned char bool;
#define	true	1
#define	false	0
#endif

// This is a tremendously useful macro that calculates how many
// elements are in an array. The calculations are done at compile
// time, so it is very efficient.
#define	NUMELEMENTS(x)	(sizeof(x) / sizeof(x[0]))

//#ifdef	WIN32
// Windows true-colour bitmaps are in BGR format instead
// of RGB. These defines help to avoid depending on the
// order, and make the intent of code clearer.
#define	BLUE_BITMAP_OFFSET	0
#define	GREEN_BITMAP_OFFSET	1
#define	RED_BITMAP_OFFSET	2
#define	ALPHA_BITMAP_OFFSET	3
//#else
//#error	Unknown platform. Please specify!
//#endif

#define   DITHER_HALFTONE_RANDOM 0 
#define   DITHER_HALFTONE_ORDERED 1 
#define   DITHER_HALFTONE_DIFFUSE 2 

struct DIBData
{
	BITMAPINFOHEADER InfoHeader;
	RGBQUAD ColorTable[256];
};

// All data in this struct should be treated as private. DON'T MESS
// WITH IT!!!! Use the bitmap functions below for EVERYTHING!
class Bitmap
{  
	DIBData   mInfo;
	
    int   mChannels; /* 1 for 8bpp, 3 for 24bpp etc */
    int		mBytesPerLine; /* Number of bytes per line, always positive. */
    int		mStride;   /* */
    uint8	*mLineZeroPointer; 
    uint8	*mSurfaceBits;

	  // Various Win32 specific items.
	  HDC		  mBitmapDC;
	  HBITMAP mBitmapNew;
    HBITMAP mBitmapMonochrome;


public:

    // Methods to get and set the size of the bitmap. SetSize() will free
    // previously allocated bitmaps if there are any.
    bool	  SetSize( int width, int height, int channels);	// Returns true for success.
    int	    GetWidth();
    int	    GetHeight();
    int	    GetChannels();
    int	    GetStride() ;
    uint8*  GetSurfaceBits();
    // Returns true if bitmap data is allocated.
    bool	  HasBitmap() ;
    // You should call the Init() function before using the bitmap.
    void		InitBitmap();
    // Frees the bitmap data. Be sure to call when finished with the bitmap.
    void		FreeBitmap();
    
    // Asserts if the color table cannot be set, for instance if the bitmap
    // is not a paletted bitmap or if there is no bitmap.
    void SetPalette(int StartColor, int NumColors, RGBQUAD* pColors);
    // Returns true if getting the palette succeeds. Asserts if used illegally.
    bool GetPalette( int StartColor, int NumColors, RGBQUAD* pColors);
    
    
    // Methods to get access to the bitmap data. Some types of
    // Win32 bitmaps allow you to treat them either as an HDC,
    // an HBITMAP or as an array of bytes. While not portable,
    // the HDC and HBITMAP options are too useful to ignore.
    HDC			  GetDC( void );    
    uint8*		GetLinePtr( int y);    
    
    
    // Various methods to draw the bitmap to an HDC.
    void      DrawAt(HDC hdc,
                     int startX, 
                     int startY)  ;
    void			DrawAll(HDC DestDC);
    bool      LoadBMPFile(const char* FileName);
    bool      SaveBMPFile(const char* FileName );
    bool      isValidBitmap();
    
    /////////////////////////////////////////////////////////////////
    //	Function:		Scale
    //	Description:	Scales the source bitmap map to the given 
    //                width (right -left) and height (bottom - top) 
    //                in the dest bitmap
    //	Parameters:		
    //      left,top,right,bottom - relative location - just used to 
    //                              get final size for bitmap
    //      pSourceBM - reference of source bitmap to scale
    //                  NOTE: THIS BITMAP SHOULD NOT BE MODIFIED
    //                        (unless scaling self)
    //      pFiltered - true if scaling should be done with bi-lateral
    //                  filtering.
    //                  false - otherwise
    //	Return: 1 - for success
    //          0 - for failure
    ////////////////////////////////////////////////////////////////
    int       Scale(int left,
                    int top, 
                    int right, 
                    int bottom, 
                    Bitmap & pSourceBM,
                    bool bFiltered);

    int	Bitmap::Convert24_32(Bitmap& srcBmp, unsigned char r,
                                             unsigned char g,
                                             unsigned char b);
	
  /////////////////////////////////////////////////////////////////
  // Function:	Flip 
  // Description:	This function makes the dest bitmap the same size
  //              and colour depth as the source bmp, then flips 
  //              the source image vertically and/or horizontally 
  //              and stores the result in dest bmp
  //              NOTE: you must allow for the case where 
  //                    *this == pSrcBmp 
  //                    ie. we're overwritting the source bmp
  // Parameters:   srcBmp - source bitmap reference
  //               bVert - true if you should flip image vertically
  //               bHoriz - true if you should flip image horizontally
  // Return: 1 on success
  //         0 otherwise		 
  ////////////////////////////////////////////////////////////////
  int Flip(Bitmap & srcBmp,
                   bool bVert, 
                   bool bHorz);

  /////////////////////////////////////////////////////////////////
  // Function:	Invert
  // Description:	This function makes the dest ("this") bitmap 
  //                the same size and colour depth as the source 
  //                bmp, then inverts the colours of each channel 
  //                of the source bitmap and writes the result to 
  //                the dest bmp.
  //                NOTE: you must allow for the case where 
  //                    *this == pSrcBmp 
  //                    ie. we're overwritting the source bmp
  // Parameters:   pSrcBmp - source bitmap reference
  // Return: 1 on success
  //         0 otherwise		 
  ////////////////////////////////////////////////////////////////
  int Invert(Bitmap & srcBmp); 



  /////////////////////////////////////////////////////////////////
  // Function:	Brighten 
  // Description:	This function makes the dest "this" bitmap the same size
  //              and colour depth as the source bmp, then 
  //              brightens each channel of the source image by 
  //              "amount" and stores the result in dest bmp
  //              NOTE: you must allow for the case where 
  //                    pDestBmp == pSrcBmp 
  //                    ie. we're overwritting the source bmp
  // Parameters:   srcBmp - source bitmap reference
  ///              amount - number to add/subtract from each pixel
  //                        colour channel (remember to clamp on 
  //                        255 and 0)
  // Return: 1 on success
  //         0 otherwise		 
  ////////////////////////////////////////////////////////////////
  int Brighten(Bitmap & srcBmp, 
                          int amount);



};

#endif