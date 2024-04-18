/*!
	@file	BMops.cpp
	@author	Scott Smith
_________________________________________________________*/
#include <windows.h>
#include "BMops.h"            
#include <math.H>
#include <fstream>

using namespace std;

inline static int clamped_value(int value, int colors)
{
	if(value > colors)
		return colors;
	else if(value < 0)
		return 0;
	return value;
}


// This returns the 'current time' (undefined zero point) in seconds,
// as a double. This is very convenient for a lot of things.
// It's not a super quick routine, but it calculates the time to
// very high accuracy. Much more than GetTickCount().
double CS_GetTime()
{
	LARGE_INTEGER	iFrequency, iTime;
	BOOL FreqResult = QueryPerformanceFrequency(&iFrequency);
	BOOL CounterResult = QueryPerformanceCounter(&iTime);
	if ((FreqResult == TRUE) && (CounterResult == TRUE))
	{
		double Time = (double)iTime.QuadPart / (double)iFrequency.QuadPart;
		return Time;
	}
	// This better not happen...
	assert(0);
	return 0.0;
}


void DisplayLastError(const char  * pmessage)
{
  MessageBox(NULL, pmessage, "ERROR", MB_OK);
}
      

//These functions are done for you
uint8*  Bitmap::GetSurfaceBits() { return mSurfaceBits; }
/////////////////////////////////////////////////////////////////
//	Function:		isValidBitmap
//	Description: Returns true if bitmap data is allocated.	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////
bool	Bitmap::HasBitmap() { return mBitmapDC != 0;}

/////////////////////////////////////////////////////////////////
//	Function:		isValidBitmap
//	Description:	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////
bool Bitmap::isValidBitmap()
{
	return mBitmapNew != NULL && 
         mBitmapDC != NULL && 
         mBitmapMonochrome != NULL;
}
/////////////////////////////////////////////////////////////////
//	Function:		DrawAt
//	Description:	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////
void Bitmap::DrawAt(HDC hdc,int startX, int startY)  
{
	BITMAP bm;
	POINT ptSize, ptOrg;

  if (!isValidBitmap())
		return;
	SetMapMode (mBitmapDC, GetMapMode(hdc));

	GetObject (mBitmapNew, sizeof (BITMAP), (LPVOID) &bm);

	ptSize.x = bm.bmWidth;
	ptSize.y = bm.bmHeight;
	DPtoLP(hdc, &ptSize, 1);

	ptOrg.x = 0;
	ptOrg.y = 0;
	DPtoLP(mBitmapDC, &ptOrg, 1);

	BitBlt(hdc, startX,startY, ptSize.x, ptSize.y,
		mBitmapDC, ptOrg.x, ptOrg.y, SRCCOPY);
}

/////////////////////////////////////////////////////////////////
//	Function:		DrawAll
//	Description:	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////
void Bitmap::DrawAll(HDC hdc) 
{
	DrawAt( hdc,0,0);
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//CS230 - this is where your work begins

/////////////////////////////////////////////////////////////////
//	Function:		InitBitmap
//	Description:	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////
void Bitmap::InitBitmap()
{
	memset(this, 0, sizeof(Bitmap));
}

/////////////////////////////////////////////////////////////////
//	Function:		SetSize
//	Description:	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////
bool Bitmap::SetSize(int Width, int Height, int Channels)
{
	FreeBitmap();
	memset(&mInfo.InfoHeader, 0, sizeof(mInfo.InfoHeader));
	
	HDC tempDC = CreateDC("Display", NULL, NULL, NULL);
	
	rassert(Width > 0);
	rassert(Height > 0);
	//rassert(Channels > 0);

	if(!Channels)
		Channels = 1;

    mInfo.InfoHeader.biBitCount = Channels * 8;
	mInfo.InfoHeader.biHeight = Height;
	mInfo.InfoHeader.biWidth = Width;
	mInfo.InfoHeader.biPlanes = 1;
	mInfo.InfoHeader.biCompression = BI_RGB;
	mInfo.InfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	mInfo.InfoHeader.biSizeImage = 0;
	mInfo.InfoHeader.biClrImportant = 0;
	mInfo.InfoHeader.biClrUsed = 0;
	mInfo.ColorTable->rgbBlue = 0;
	mInfo.ColorTable->rgbGreen = 0;
	mInfo.ColorTable->rgbRed = 0;
	mInfo.InfoHeader.biXPelsPerMeter = 0;
	mInfo.InfoHeader.biYPelsPerMeter = 0;


        
	/*
    mInfo.InfoHeader.biHeight = Height;
	mInfo.InfoHeader.biWidth = Width;
	
	mInfo.InfoHeader.biBitCount = Channels * 8;
	mInfo.InfoHeader.biPlanes = 1;
	mInfo.InfoHeader.biSize = sizeof(BITMAPINFOHEADER);
    */
    
	mChannels = Channels;
	
	mStride = (Width * Channels + 3) & ~3;
	
	mBytesPerLine = abs(GetStride());
	
	mBitmapDC = CreateCompatibleDC(tempDC);
	
	if(0 == mBitmapDC)
	{
		DeleteObject(mBitmapNew);
		return false;
	}
	
	// allocate mSurfaceBits
	mBitmapNew = CreateDIBSection(mBitmapDC, (BITMAPINFO *)&(mInfo), \
								DIB_RGB_COLORS, (void**)&mSurfaceBits, NULL, NULL); 
	
	// set palette info if it's there
	SetDIBColorTable(mBitmapDC, 0, mInfo.InfoHeader.biClrUsed, mInfo.ColorTable);
	
	// select object to bm to be displayed
	mBitmapMonochrome = (HBITMAP) SelectObject(mBitmapDC, mBitmapNew);
	
	DeleteDC(tempDC);
	return true;
	
}


/////////////////////////////////////////////////////////////////
//	Function:		GetLinePtr
//	Description:	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////
unsigned char* Bitmap::GetLinePtr(int y) 
{
	return (isValidBitmap()) ? mSurfaceBits + y * mStride : 0;
}

/////////////////////////////////////////////////////////////////
//	Function:		GetWidth
//	Description:	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////
int Bitmap::GetWidth() 
{
  return (mInfo.InfoHeader.biWidth);
}
/////////////////////////////////////////////////////////////////
//	Function:		GetHeight
//	Description:	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////
int Bitmap::GetHeight() 
{
  return (mInfo.InfoHeader.biHeight);
}
    /////////////////////////////////////////////////////////////////
//	Function:		GetChannels
//	Description:	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////
int Bitmap::GetChannels() 
{
	mChannels = (mInfo.InfoHeader.biBitCount / 8);
	if(!mChannels)
		mChannels = 1;

	return mChannels;
}
    /////////////////////////////////////////////////////////////////
//	Function:		GetStride
//	Description:	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////
int Bitmap::GetStride() 
{
	return (GetWidth() * GetChannels() + 3) & ~3;
}
/////////////////////////////////////////////////////////////////
//	Function:		FreeBitmap
//	Description:	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////
void Bitmap::FreeBitmap() 
{ 
	SelectObject(mBitmapDC, mBitmapMonochrome);
	DeleteDC(mBitmapDC);
	DeleteObject(mBitmapNew);
}

/////////////////////////////////////////////////////////////////
//	Function:		LoadBMPFile
//	Description:	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////
bool Bitmap::LoadBMPFile(const char* FileName)
{
  if(!FileName)
	  return false;
  InitBitmap();
  BITMAPFILEHEADER bmfh;
    
  /// @brief pointer to the bitmap file
    ifstream	fp;

	fp.open(FileName, ios::binary);
	
	if(fp == NULL)
	{
		MessageBox(NULL, "File not found.", "Error!", MB_ICONERROR);
		return (false);
	}
	
	/// read file info into bmfh structure
	fp.read(reinterpret_cast<char *>(&bmfh), sizeof(BITMAPFILEHEADER));

	/// confirm correct bitmap file format
	if(bmfh.bfType != 0x4D42)
	{
		MessageBox(NULL, "Incorrect file format.", "Error!", MB_ICONERROR);
		return (false);
	}
	
	/// read file info into bmih structure
	fp.read(reinterpret_cast<char *>(&(mInfo.InfoHeader)), sizeof(BITMAPINFOHEADER));
	
	if((mInfo.InfoHeader.biBitCount) <= 8)
	{	
		if(mInfo.InfoHeader.biClrUsed)
			fp.read(reinterpret_cast<char *>(&mInfo.ColorTable), mInfo.InfoHeader.biClrUsed * sizeof(RGBQUAD));
		else if(0 == mInfo.InfoHeader.biClrUsed)
			fp.read(reinterpret_cast<char *>(&mInfo.ColorTable), (1 << mInfo.InfoHeader.biBitCount) * sizeof(RGBQUAD));
	}
	else
	{
		fp.seekg(bmfh.bfOffBits,ios_base::beg);
	}
	// fill in fields with info from file
	mChannels = (mInfo.InfoHeader.biBitCount / 8);
	if(!mChannels)
		mChannels = 1;

	mStride = ((GetWidth() * GetChannels()) + 3) & ~3;
	mLineZeroPointer = ((uint8*)&bmfh + (GetStride() * (GetHeight() - 1)) + (GetChannels() * GetWidth()));
	mBytesPerLine = abs(GetStride());
	SetSize(GetWidth(), GetHeight(), GetChannels());

	if(mInfo.InfoHeader.biCompression == BI_RLE8)
	{
		
	}
	else
		fp.read(reinterpret_cast<char *>(mSurfaceBits), mBytesPerLine * GetHeight());
	
	fp.close();
	//SaveBMPFile("output.bmp");
	this;
   return true; 
}

////////////////////////////////////////////////////////////////
//	Function:		SaveBMPFile
//	Description:	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////
bool Bitmap::SaveBMPFile(const char* FileName)
{
	if(!HasBitmap())
	  return false;
	if(!isValidBitmap())
	  return false;
	
	

	BITMAPFILEHEADER bmfh = {0};
	bmfh.bfType = 0x4D42;
	
	if((mInfo.InfoHeader.biBitCount) <= 8)
	{
		if(mInfo.InfoHeader.biClrUsed)
			bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) 
							+ mInfo.InfoHeader.biClrUsed * sizeof(RGBQUAD);
		else if(0 == mInfo.InfoHeader.biClrUsed)
			bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) 
							+ (1 << mInfo.InfoHeader.biBitCount) * sizeof(RGBQUAD);
	}
	else
		bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	/// @brief pointer to the bitmap file
    ofstream	fp;

	fp.open(FileName, ios::binary);
	
	
	if(fp == NULL)
	{
		MessageBox(NULL, "File could not be created", "Error!", MB_ICONERROR);
		return (false);
	}
	
	/// read file info into bmfh structure
	fp.write(reinterpret_cast<char *>(&bmfh), sizeof(BITMAPFILEHEADER));

	/// confirm correct bitmap file format
	if(bmfh.bfType != 0x4D42)
	{
		MessageBox(NULL, "Incorrect file format.", "Error!", MB_ICONERROR);
		return (false);
	}
	
	/// read file info into bmih structure
	fp.write(reinterpret_cast<char *>(&(mInfo.InfoHeader)), sizeof(BITMAPINFOHEADER));

	GetDIBColorTable(mBitmapDC, 0, mInfo.InfoHeader.biClrUsed, mInfo.ColorTable);
	
	if((mInfo.InfoHeader.biBitCount) <= 8)
	{	
		if(mInfo.InfoHeader.biClrUsed)
			fp.write(reinterpret_cast<char *>(mInfo.ColorTable), mInfo.InfoHeader.biClrUsed * sizeof(RGBQUAD));
		else if(0 == mInfo.InfoHeader.biClrUsed)
			fp.write(reinterpret_cast<char *>(mInfo.ColorTable), (1 << mInfo.InfoHeader.biBitCount) * sizeof(RGBQUAD));
		
	
	}
	
	fp.write(reinterpret_cast<char *>(mSurfaceBits), mBytesPerLine * GetHeight());
	fp.close();
	
	return true;
}
/*!
    BitMap::Convert24_32()
    @param  srcBmp  Bitmap to be scaled
______________________________________________________________________________*/
int	Bitmap::Convert24_32(Bitmap& srcBmp, unsigned char r,
                                         unsigned char g,
                                         unsigned char b)
{
	if(!(GetWidth() && GetHeight() && srcBmp.GetChannels()))
	{
		return 0;
	}

	unsigned char *tbuf;
	tbuf = new unsigned char[mBytesPerLine * GetHeight()];
	
	// create a copy of the existing surface bits
	memcpy(tbuf, mSurfaceBits, mBytesPerLine * GetHeight());

	// allocate space for a 32 bit bitmap
	SetSize(GetWidth(), GetHeight(), 4);

	unsigned char *SrcL;
	unsigned char *DstL;
	int channelAmount = 3;

	double SrcY = 0;
	double SrcX = 0;
	int Height = GetHeight();
	int Width = GetWidth();
	int DstX, DstY;
	int ErrorAccumulatorX	= 0;
	//int ErrorAccumulatorY	= (Height / 2) - Height;
	int channelOffsetDest	= 0;
	int channelOffsetSource = 0;

	for (DstY = 0; DstY < Height; ++DstY)
	{
		SrcY = (DstY * Height + (Height >> 1)) / Height;
		
		SrcL = tbuf + (int)SrcY * srcBmp.GetStride();
		DstL   = GetLinePtr(DstY);

		SrcX = 0;
		ErrorAccumulatorX = Width / 2 - Width;

		for (DstX = 0; DstX < Width; ++DstX)
		{
			while (ErrorAccumulatorX >= 0)
			{
				++SrcX;
				ErrorAccumulatorX -= Width;
			}

			if(SrcX >= Width)
				SrcX = Width - 1;
			else if(SrcX < 0)
				SrcX = 0;
							
			assert(SrcX >= 0 && SrcX < Width);
		
			ErrorAccumulatorX += Width;
			channelOffsetDest = DstX * (4);
			channelOffsetSource = SrcX * channelAmount;
			
			for (int channel = 0; channel < channelAmount; ++channel)
				DstL[channelOffsetDest + channel] = SrcL[channelOffsetSource + channel];
			
			if( DstL[channelOffsetDest] ==  r &&
				DstL[channelOffsetDest + 1] == g &&
                DstL[channelOffsetDest + 2] == b)
			{
				DstL[channelOffsetDest + 3] = 0x00;
			}
			else
			{
				DstL[channelOffsetDest + 3] = 0xFF;
			}

					
		} // end for DestX
	} // end for DestY

    //return 1;


	delete[] tbuf;
	return 0;
}

////////////////////////////////////////////////////////////////
//	Function:		SetPalette
//	Description:	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////
void Bitmap::SetPalette(int StartColor, int NumColors, RGBQUAD* pColors)
{
  SetDIBColorTable(mBitmapDC, StartColor, NumColors, pColors);
}

////////////////////////////////////////////////////////////////
//	Function:		GetPalette
//	Description:	
//	Parameters:		
//	Return:			 
////////////////////////////////////////////////////////////////    
bool Bitmap::GetPalette( int StartColor, int NumColors, RGBQUAD* pColors)
{
	rassert(isValidBitmap());  
	rassert(1 == mChannels);
	GetDIBColorTable(mBitmapDC, StartColor, NumColors, pColors);
	return true; /* or false */
}
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
int       Bitmap::Scale(int left,
                int top, 
                int right, 
                int bottom, 
                Bitmap & pSourceBM,
                bool bFiltered)
{
    if(right && bottom && pSourceBM.GetChannels())
	{
		SetSize(right - left, bottom - top, pSourceBM.GetChannels());
	}
	else
	{
		return 0;
	}
	
	int channelAmount = GetChannels();

	unsigned char *SrcL;
	unsigned char *DstL;
	
	int SrcHeight = pSourceBM.GetHeight();
	int SrcWidth  = pSourceBM.GetWidth();
	int DstHeight   = GetHeight();
	int DstWidth    = GetWidth();
	
	double SrcX = 0;
	double SrcY = 0;
	int DstX	= 0;
	int DstY	= 0;
	int channel = 0;
	
	if(bFiltered)
	{
		double BWeight	= 0;
		double TWeight	= 0;
		double RWeight	= 0;
		double LWeight	= 0;
		double BLWeight	= 0;
		double BRWeight	= 0;
		double TLWeight	= 0;
		double TRWeight	= 0;
		
		int LPixel	= 0;
		int leftp	= 0;
		int left1p	= 0;
		int LAdd	= 0;
		int x		= 0;
		int TLine	= 0;
		

		for(DstY = 0; DstY < GetHeight(); ++DstY)
		{
			SrcY = (DstY + 0.5) * SrcHeight / ((double)DstHeight);
			SrcY -= 0.5;
			
			TLine = (int)SrcY;
			if(TLine >= SrcHeight)
				TLine = SrcHeight - 1;
					
			if(TLine < 0)
				TLine = 0;
			
			BWeight = SrcY - TLine;
			TWeight = 1.0 - BWeight;

			SrcL	 = pSourceBM.GetLinePtr((int)SrcY);
			DstL	 = GetLinePtr(DstY);

			for(DstX = 0; DstX < DstWidth; ++DstX)
			{
				SrcX = (DstX + 0.5) * SrcWidth / ((double)DstWidth);
				SrcX -= 0.5;
				
				LPixel = (int)SrcX;
				if(LPixel >= SrcWidth)
					LPixel = SrcWidth - 1;
				
				if(LPixel < 0)
					LPixel = 0;
				
				RWeight = SrcX - LPixel;
				LWeight = 1.0 - RWeight;

				TLWeight = TWeight * LWeight;
				BLWeight = BWeight * LWeight;
				BRWeight = BWeight * RWeight;
				TRWeight = TWeight * RWeight;

				for (channel = 0; channel < channelAmount; ++channel)
				{
					SrcL	= pSourceBM.GetLinePtr(TLine);
					x = DstX * channelAmount + channel;
					leftp = LPixel * channelAmount + channel;
					LAdd = LPixel + 1;
					left1p = LAdd * channelAmount + channel;
					
					if(LAdd >= SrcWidth)
						left1p = leftp;
					
					DstL[x] = (unsigned char) (SrcL[leftp] * TLWeight + SrcL[left1p] * TRWeight);

					if(TLine < (SrcHeight - 1))
						SrcL = pSourceBM.GetLinePtr(TLine + 1);
					
					DstL[x] += (unsigned char)(SrcL[leftp] * BLWeight + SrcL[left1p] * BRWeight);
				} // end for channel
			} // end for DestX
		} // end for DestY
	} // end if bFiltered
	else // if not filtered
	{
		SrcY = 0;
		SrcX = 0;
		int ErrorAccumulatorX	= 0;
		//int ErrorAccumulatorY	= (SrcHeight / 2) - DstHeight;
		int channelOffsetDest	= 0;
		int channelOffsetSource = 0;

		for (DstY = 0; DstY < DstHeight; ++DstY)
		{
			SrcY = (DstY * SrcHeight + 	(SrcHeight >> 1)) / DstHeight;
			
			SrcL = pSourceBM.GetLinePtr(SrcY);
			DstL   = GetLinePtr(DstY);

			SrcX = 0;
			ErrorAccumulatorX = SrcWidth / 2 - DstWidth;

			for (DstX = 0; DstX < DstWidth; ++DstX)
			{
				while (ErrorAccumulatorX >= 0)
				{
					++SrcX;
					ErrorAccumulatorX -= DstWidth;
				}

				if(SrcX >= SrcWidth)
					SrcX = SrcWidth - 1;
				else if(SrcX < 0)
					SrcX = 0;
								
				assert(SrcX >= 0 && SrcX < SrcWidth);
			
				ErrorAccumulatorX += SrcWidth;
				channelOffsetDest = DstX * channelAmount;
				channelOffsetSource = SrcX * channelAmount;
				
				for (channel = 0; channel < channelAmount; ++channel)
					DstL[channelOffsetDest + channel] = SrcL[channelOffsetSource + channel];
						
			} // end for DestX
		} // end for DestY

		
	} // end else
	
    return 1;


}

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
int Bitmap::Flip(Bitmap & srcBmp, 
                 bool bVert, 
                 bool bHorz)
{
	if(!(GetWidth() && GetHeight() && srcBmp.GetChannels()))
	{
		return 0;
	}
	
	unsigned char *pDestLine;
	unsigned char *pSourceLine;
	int Height = srcBmp.GetHeight();
	int Width = srcBmp.GetWidth();
	int numChannels = srcBmp.GetChannels();
	int tempVal = 0;
	
	
	if(bVert)
	{
		unsigned char *ybuf;
		ybuf = new unsigned char[mBytesPerLine];
		for(int y = 0; y < Height/2; ++y)
		{
			memcpy((unsigned char *)ybuf, (unsigned char *)srcBmp.GetLinePtr(y), mBytesPerLine);
			memcpy((unsigned char *)GetLinePtr(y), (unsigned char *)srcBmp.GetLinePtr(Height - y - 1), mBytesPerLine);
			memcpy((unsigned char *)GetLinePtr(Height - y - 1), (unsigned char *)ybuf, mBytesPerLine);
		}
		delete[] ybuf;
	}

	if(bHorz)
	{
		for(int y = 0; y < Height; ++y)
		{
			pDestLine = GetLinePtr(y);
			pSourceLine = srcBmp.GetLinePtr(y);
			
			for (int x = 0; x < Width/2; ++x) 
			{	
			
				if (numChannels > 1)
				{
					switch( GetChannels())
					{
						case 4:   //do nothing here - this is alpha	
						case 3:
							tempVal = pSourceLine [ x * numChannels + 2];
  							pDestLine [ x * numChannels + 2 ] = pSourceLine[(Width - x - 1) * numChannels + 2];
							pDestLine [ (Width - x - 1) * numChannels + 2 ] = tempVal;
							
						case 2:
							tempVal = pSourceLine [ x * numChannels + 1];
  							pDestLine [ x * numChannels + 1 ] = pSourceLine[(Width - x - 1) * numChannels + 1];
							pDestLine [ (Width - x - 1) * numChannels + 1 ] = tempVal;
							
						case 1:
							tempVal = pSourceLine [ x * numChannels + 0];
  							pDestLine [ x * numChannels + 0 ] = pSourceLine[(Width - x - 1) * numChannels + 0];
							pDestLine [ (Width - x - 1) * numChannels + 0 ] = tempVal; 
							
						default:
							break;
					}
				}
				else
					return 0;
			}	
		  
		}

	}
    return 1;
}

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
int Bitmap::Invert(Bitmap & srcBmp)
{
    if(!(GetWidth() && GetHeight() && srcBmp.GetChannels()))
	{
		return 0;
	}

	unsigned char *SrcL;
	unsigned char *DstL;
	int channelAmount = GetChannels();

	double SrcY = 0;
	double SrcX = 0;
	int Height = GetHeight();
	int Width = GetWidth();
	int DstX, DstY;
	int ErrorAccumulatorX	= 0;
	//int ErrorAccumulatorY	= (Height / 2) - Height;
	int channelOffsetDest	= 0;
	int channelOffsetSource = 0;

	for (DstY = 0; DstY < Height; ++DstY)
	{
		SrcY = (DstY * Height + (Height >> 1)) / Height;
		
		SrcL = srcBmp.GetLinePtr(SrcY);
		DstL   = GetLinePtr(DstY);

		SrcX = 0;
		ErrorAccumulatorX = Width / 2 - Width;

		for (DstX = 0; DstX < Width; ++DstX)
		{
			while (ErrorAccumulatorX >= 0)
			{
				++SrcX;
				ErrorAccumulatorX -= Width;
			}

			if(SrcX >= Width)
				SrcX = Width - 1;
			else if(SrcX < 0)
				SrcX = 0;
							
			assert(SrcX >= 0 && SrcX < Width);
		
			ErrorAccumulatorX += Width;
			channelOffsetDest = DstX * channelAmount;
			channelOffsetSource = SrcX * channelAmount;
			
			for (int channel = 0; channel < channelAmount; ++channel)
				DstL[channelOffsetDest + channel] = ~SrcL[channelOffsetSource + channel];
					
		} // end for DestX
	} // end for DestY

    return 1;
}



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
int Bitmap::Brighten(Bitmap & srcBmp, 
                  int amount)
{
    if(!(GetWidth() && GetHeight() && srcBmp.GetChannels()))
	{
		return 0;
	}

	unsigned char *pDestLine;
	unsigned char *pSourceLine;

	int Height = srcBmp.GetHeight();
	int Width = srcBmp.GetWidth();
	int numChannels = srcBmp.GetChannels();
	int tempVal = 0;

	for(int y = 0; y < Height; ++y)
	{
		pDestLine = GetLinePtr(y);
		pSourceLine = srcBmp.GetLinePtr(y);
		
		for (int x = 0; x < Width; ++x) 
		{	
		
			if (numChannels > 1)
			{
				switch( GetChannels())
				{
					case 4:   //do nothing here - this is alpha	
					case 3:
						tempVal = pSourceLine [ x * numChannels + 2] + amount;  // invert for RED
  						//make sure value is in range  
						if ( tempVal  > 255)
							tempVal = 255;   // clamp high
						else if( tempVal < 0)
							tempVal = 0;     // clamp low
						pDestLine [ x * numChannels + 2 ] = tempVal;
						
					case 2:
						tempVal = pSourceLine [ x * numChannels + 1] + amount;  // invert for RED
  						//make sure value is in range  
						if ( tempVal  > 255)
							tempVal = 255;   // clamp high
						else if( tempVal < 0)
							tempVal = 0;     // clamp low
						pDestLine [ x * numChannels + 1 ] = tempVal;
						
					case 1:
						tempVal = pSourceLine [ x * numChannels + 0] + amount;  // invert for RED
  						//make sure value is in range  
						if ( tempVal  > 255)
							tempVal = 255;   // clamp high
						else if( tempVal < 0)
							tempVal = 0;     // clamp low
						pDestLine [ x * numChannels + 0 ] = tempVal;
						
					default:
						break;
				}
			}
			else // numChannels == 1      paletted
			{
				int colors = srcBmp.mInfo.InfoHeader.biClrUsed;
				for (int i = 0; i < colors; ++i)
				{
					mInfo.ColorTable[ i ].rgbBlue = 
						clamped_value (srcBmp.mInfo.ColorTable[i].rgbBlue + amount, colors);
					mInfo.ColorTable[ i ].rgbGreen = 
						clamped_value (srcBmp.mInfo.ColorTable[i].rgbGreen + amount, colors);
					mInfo.ColorTable[ i ]. rgbRed = 
						clamped_value (srcBmp.mInfo.ColorTable[i].rgbRed + amount, colors);
				}

			}
		}
	}


    return 1;
}

