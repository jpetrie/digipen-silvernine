/*!
	@file		CText.cpp
	@author		Scott Smith
	@date		November 12, 2003

	@brief	Implements bitmap font rendering through a CText object
______________________________________________________________________________*/


/*																		includes
______________________________________________________________________________*/
#include "precompiled.h"

#include "CText.h"
//#include "CMemoryMgrS.h"
/*----------------------------------------------------------------------------*/
// ct
CText::CText(std::string text, int point, std::string typeface)
:display_(text), font_(typeface), height_(point), just_(LEFT_JUST), line(0), font(0), line_count(0) 
{
	// build the display list for the specified font
	BuildFont();
	// Set the default font color
	SetColor4f(1.f, 1.f, 1.f, 1.f);
	update = true;
	//tokens = nsl::stsplit_chr(display_, DELIMIT);
}
// dt
CText::~CText() { KillFont(); }	 // clean up OpenGL and our font memory

/*!
	CText::BuildFont()

	@brief	Build a font object and initialize our display list
______________________________________________________________________________*/
void CText::BuildFont(void)
{
	GLenum GLerror;
	HFONT fontid;
	HFONT oldfont;
	// get the device context of our device manager
	HDC dc = *CGraphicsMgr->getDeviceContext();

	// request memory for our font object
	if((font = (GLFONT*)calloc(1, sizeof(GLFONT))) == (GLFONT *)0)
		return;

	// attemp to construct our OpenGL display list
	if((font->base = glGenLists(256)) == 0)
	{
		free(font);
		return;
	}

	// build the font
	fontid = CreateFont(height_, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 
									ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, 
									ANTIALIASED_QUALITY, FF_DONTCARE|DEFAULT_PITCH, font_.c_str());

	// do the Windows GDI business
	oldfont = (HFONT)SelectObject(dc, fontid);

	// check for OpenGL errors before we get too carried away
	while( (GLerror = glGetError()) != GL_NO_ERROR)
		;

	// this is where we build our bitmap font
	if(!wglUseFontBitmaps(dc, 0, 256, font->base))
	{
		return;
	}
	// house cleaning - the Windows way. Yuck.
	SelectObject(dc, oldfont);
	DeleteObject(fontid);

	// load the pixel widths for each character in our character set
	GetCharWidth(dc, 0, 255, font->widths);
	// they all have the same height, though.
	font->height = height_;
	// this is the pixel width of a space character - we will need it for wrapping
	delimeter_width = font->widths[' '];
}

/*----------------------------------------------------------------------------*/

/*!
	CText::KillFont()

	@brief	Delete our display list and free our memory
______________________________________________________________________________*/
void CText::KillFont(void)
{
	// if the font does not exist - don't free the memory
	if(font == (GLFONT*)0)
		return;
	
	// clean up our openGL display list
	glDeleteLists(font->base, 256);
	// free our memory
	free(font);
}

/*----------------------------------------------------------------------------*/

/*!
	CText::Draw()

	@brief	Draw the text to screen 
______________________________________________________________________________*/
void CText::Draw(void)
{
	if(IsVisible() == false)
		return;
	GLenum GLerror;
	
	while( (GLerror = glGetError()) != GL_NO_ERROR)
		;
	glDisable(GL_TEXTURE_2D);
	// check for valid font and text
	if(font == (GLFONT*)0 || display_.c_str() == (char*)0)
		return;
	
	// set the appopriate color
	glColor4f(color_.red, color_.green, color_.blue, color_.alpha);
	
	int width = 0;
	
//	lines.clear();
	//std::string curr_line;
	//// add up all of the character widths
	//for(unsigned int i = 0; i < tokens.size(); ++i)
	//{
	//	// find the pixel width of the current word
	//	for(unsigned int j = 0; j < tokens[i].length(); ++j)
	//	{
	//		if(tokens[i].length() >= (GetWidth() / CGraphicsMgr->gcam()))
	//		{
	//			
	//			std::string cur;
	//			nsl::stringlist words;
	//			unsigned int l = 0;
	//			for(; l < tokens[i].length(); ++l)
	//			{
	//				cur += tokens[i][l];
	//				if(cur.length() == GetWidth() / CGraphicsMgr->gcam())
	//				{
	//					words.push_back(cur);
	//					cur.clear();
	//				}
	//			}
	//			words.push_back(cur);
	//			
	//			std::vector<std::string>::iterator it = tokens.begin();
	//			for(unsigned int k = 0; k <= i; ++k)
	//				++it;
	//			tokens.insert(it, words.begin(), words.end());
	//			for(unsigned int k = 0; k <= i; ++k)
	//				++it;
	//			tokens.erase(it);
	//		}
	//		else
	//			width += font->widths[tokens[i][j]];
	//	}
	//	// add the width of a space between each word
	//	width += delimeter_width;

	//	// if the pixel width of the line with the new word is still less than
	//	// our pane width, add the word to the list.
	//	std::string split;
	//	if(width < (GetWidth() / CGraphicsMgr->gcam()))
	//	{
	//		//bool newline = false;
	//		//
	//		//int sidx = 0, eidx = 0;
	//		//char breakup[256];
	//		//strcpy(breakup, tokens[i].c_str());
	//		//for(int bn = 0; bn < tokens[i].length(); ++bn)
	//		//{
	//		//	newline = false;
	//		//	eidx = bn;
	//		//	if(tokens[i][bn] == '\n')
	//		//	{
	//		//		newline = true;
	//		//		char * newword = new char[(eidx - sidx) + 1];
	//		//		std::string t = (breakup + sidx);
	//		//		strncpy(newword, t.c_str(), (eidx - sidx) + 1);
	//		//		newword[(eidx - sidx)] = '\0';
	//		//		curr_line += " " + std::string(newword);
	//		//		lines.push_back(curr_line);
	//		//		lines.push_back("");
	//		//		curr_line = "";
	//		//		//tokens[i] = std::string(newword);
	//		//	}
	//		//		//std::string first, second;
	//		//		//newline = true;
	//		//		//char buf[1024], *out;
	//		//		//strcpy(buf, tokens[i].c_str());
	//		//		////out = strtok(buf, "\n");
	//		//		//first = strtok(buf, "\n");

	//		//		//curr_line += " ";
	//		//		//curr_line += out;
	//		//		//tokens[i] = "";
	//		//		////while(out != '\0')
	//		//		////{
	//		//		//	tokens[i] = strtok(NULL, "\n");
	//		//		//	tokens[i] += ' ';
	//		//		////	tokens[i] += out;
	//		//		////	tokens[i] += '\n';
	//		//		////}
	//		//		//if(i != tokens.size() - 1)
	//		//		//{
	//		//		//	tokens[i + 1] = tokens[i] + tokens[i + 1];
	//		//		//}
	//		//		//// add the line to the line list
	//		//		//lines.push_back(curr_line);
	//		//		//// clear the current line string
	//		//		//curr_line = "";
	//		//		//// line width is 0
	//		//		//width = 0;
	//		//		////if(i > 1)
	//		//		////	i--;
	//		//		//break;
	//		//	
	//		//	
	//		//	
	//		//}
	//		//if(!newline)
	//		//{
	//		//	char *newword = new char[(eidx - sidx) + 2];
	//		//	std::string t = (breakup + sidx);
	//		//	strncpy(newword, t.c_str(), (eidx - sidx) + 1);
	//		//	newword[(eidx - sidx) + 1] = '\0';
	//		//	
	//		//	/*if(i > tokens.size() - 1)
	//		//	{
	//		//		tokens[i + 1] = tokens[i] + std::string(newword);
	//		//	}*/
	//		//	//tokens[i] = std::string(newword);
	//		//	
	//		//	curr_line += " " + std::string(newword);
	//		//	delete [] newword;
	//		//}
	//		curr_line += " " + tokens[i];
	//	}
	//	// otherwise, add the line to the list of lines and start a new line.
	//	else
	//	{
	//		// add the line to the line list
	//		lines.push_back(curr_line);
	//		// clear the current line string
	//		curr_line = "";
	//		// go back to the previous word
	//		//if(i > 1)//jpetrie  Fixed infinite loop.
	//		//  --i;
	//		// line width is 0
	//		width = 0;
	//	}
 // }
	// add the last line to the list of lines.
//	lines.push_back(curr_line);
	if(update)
	{
		lines.clear();
		std::string curr_line = "";
		std::string::iterator it = display_.begin();
		for(int idx = 0; idx < display_.size(); ++idx)
		{
			if(display_[idx] == '\n')
			{
				width = 0;
				lines.push_back(curr_line);
				curr_line = "";
				continue;
			}
			if(display_[idx] == '\t')
			{
				curr_line += "    ";
				continue;
			}
			width += delimeter_width;
			if(width >= GetWidth() / CGraphicsMgr->gcam())
			{
				width = 0;
				lines.push_back(curr_line);
				curr_line = "" + display_[idx];
			}
			curr_line += display_[idx];
		}
		lines.push_back(curr_line);
		update = false;
	}
	
	// we are using our text display list now
	glPushAttrib(GL_LIST_BIT);
	glListBase(font->base);
	// use the list
	int pos = 0;
	float total_height = 0.f;
	line_count = (int)lines.size();
	for(unsigned int i = line; i < lines.size(); ++i)
	{
		
		// justify the text
		// our location in device units
		int line_width = 0;
		for(unsigned int j = 0; j < lines[i].length(); ++j)
			line_width += font->widths[lines[i][j]];
		total_height = (GetWorldY() + GetHeight() - 1.5f * (float)height_) - ( (float)pos * (float)height_ * CGraphicsMgr->gcam());
		if(total_height < (GetWorldY() + height_ * CGraphicsMgr->gcam()))
			break;

		glRasterPos2f(GetWorldX() + delimeter_width, total_height);
		if(just_ == RIGHT_JUST)
		{
			glBitmap(0, 0, 0, 0, (GLfloat)-line_width, 0, NULL);
		}
		else if(just_ == CENTER_JUST)
		{
			glBitmap(0, 0, 0, 0, (GLfloat)-line_width / 2, 0, NULL);
		}
		glCallLists((GLsizei)lines[i].length(), GL_UNSIGNED_BYTE, lines[i].c_str());
		glCallLists(1, GL_UNSIGNED_BYTE, " ");
		++pos;
		 
	}
	// restore whatever display list may have been in use
	glPopAttrib();
	// reset the color to white
	glColor4f(1.f, 1.f, 1.f, 1.f);
	if( (GLerror = glGetError()) != GL_NO_ERROR)
		std::cout << "TEXT ERROR!!!!!!" << std::endl;
	glEnable(GL_TEXTURE_2D);
}

/*----------------------------------------------------------------------------*/

/*!
	CText::SetColor4f()

	@brief	Applies a color to the font
______________________________________________________________________________*/
void CText::SetColor4f(float red, float green, float blue, float alpha)
{
	color_.red = red;
	color_.green = green;
	color_.blue = blue;
	color_.alpha = alpha;
}


/*----------------------------------------------------------------------------*/

/*!
	CText::SetLocation()

	@brief	Specifies the raster position in world coordinates
______________________________________________________________________________*/
void CText::SetLocation(float x, float y)
{
	SetWorldX(x);
	SetWorldY(y);
}

/*----------------------------------------------------------------------------*/

void CText::SetText(const char *fmt, ...)					
{
	char		text[65535];												// Holds Our String
	va_list		ap;															// Pointer To List Of Arguments

	if (fmt == NULL)													// If There's No Text
		return;																		// Do Nothing

	va_start(ap, fmt);												// Parses The String For Variables
	    vsprintf(text, fmt, ap);							// And Converts Symbols To Actual Numbers
	va_end(ap);																// Results Are Stored In Text

	display_ = text;													// Copy 'text' to our 'display_' string
	tokens = nsl::stsplit_chr(display_, DELIMIT);		// tokenize - for wrapping
	update = true;
	
}




#ifdef __MEM_DBG__
void * CText::operator new(size_t sz)
	{
		sz;
		return CMemoryMgr->AllocText();
	}
	void CText::operator delete(void *p)
	{
		CMemoryMgr->FreeText(p);
	}
#endif
