/*!
	@file	SNtext.h
	@author	Scott Smith
	@date	November 14, 2003

	@brief	Defines a class for line drawing
______________________________________________________________________________*/

#ifndef	__CTEXT_H__
#define	__CTEXT_H__

/*																																	includes
______________________________________________________________________________*/

#include "precompiled.h"

#include "CGraphicsObject.h"						// CGraphicsObject


/*																																	constants
______________________________________________________________________________*/
const int CENTER_JUST	= 0;				///< Centered
const int LEFT_JUST		= 1;				///< Left justified
const int RIGHT_JUST	= -1;				///< Right justified
const char DELIMIT[]	= " ";			///< delimiting characters

/*----------------------------------------------------------------------------*/

/*!
	@struct GLFONT
	@brief	Contains font information
______________________________________________________________________________*/
struct GLFONT 
{
	unsigned int base;	///<	base of the display list
	int widths[256];		///<	array of character widths
	int height;					///<	character height (point)
};

/*----------------------------------------------------------------------------*/

/*!
	@struct CText
	@brief	Allows display of character strings in OpenGL using TrueType fonts.
______________________________________________________________________________*/
class CText: public CGraphicsObject
{
public:
	// ct
	CText(std::string text = "", int point = 16, std::string typeface = "Times New Roman");
	// dt
	~CText();
	CText(const CText &t)
	{
		display_ = t.display_;
		font_ = t.font_;
		height_ = t.height_;
		color_ = t.color_;
		just_ = t.just_;
		delimeter_width = t.delimeter_width;
		line = t.line;
		tokens = t.tokens;
		lines = t.lines;
		line_count = t.line_count;
		if(t.font)
		{
			if((font = (GLFONT*)calloc(1, sizeof(GLFONT))) == (GLFONT *)0)
				return;
			memcpy(font, t.font, sizeof(GLFONT));
		}
	}

//#ifdef __MEM_DBG__
//	void * operator new(size_t sz);
//	void operator delete(void *p);
//#endif

	// change the display text
	void SetText(const char* ftm,...); 
	// change the font color
	void SetColor4f(float r, float g, float b, float a);
	// set the raster position
	void SetLocation(float x, float y);
	// set the justification
	void SetJustification(const int justify = LEFT_JUST) { just_ = justify; }
	void SetStartLine(int start = 0) { line = start; }
	
	// put it on the screen
	virtual void Draw(void);
	CText & operator=(const CText &t)
	{
		display_ = t.display_;
		font_ = t.font_;
		height_ = t.height_;
		color_ = t.color_;
		just_ = t.just_;
		delimeter_width = t.delimeter_width;
		line = t.line;
		tokens = t.tokens;
		lines = t.lines;
		line_count = t.line_count;
		if(t.font)
		{
			if((font = (GLFONT*)calloc(1, sizeof(GLFONT))) == (GLFONT *)0)
				nlTHROW("copying invalid CText object");
			memcpy(font, t.font, sizeof(GLFONT));
		}
		return *this;
	}

private:
	std::string display_;			// the display text
	std::string font_;				// the name of the font
	int height_;					// the height of a character (point)
	COLORQUAD color_;				// color of the font
	GLFONT *font;					// font info
	int just_;						// justification specification
	int delimeter_width;			// width of a space char (for wrapping)
	int line;						// used for line wrapping
	nsl::stringlist tokens;			// used for line wrapping
	nsl::stringlist lines;			// used for line wrapping
	bool update;
	// set up the display list
	void BuildFont(void);
	// free the memory
	void KillFont(void);
	int line_count;

};

#endif	/* __CTEXT_H__  */

