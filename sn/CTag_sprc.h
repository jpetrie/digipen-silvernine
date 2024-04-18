/*!
	@file	CTag_sprc.h
	@author	Scott Smith
	@date	October 16, 2003

	@brief	Sprite Collection Tag
______________________________________________________________________________*/

#ifndef _C_TAG_SPRC_H_
#define _C_TAG_SPRC_H_

#include <vector>
#include "NSL.h"
#include "CTag.h"
#include "CTexture.h"

// tag id
const CTag::ID  kTag_sprc = nlFOURCODE('s','p','r','c');

// tag id strings
const std::string  kTag_sprc_TypeStr = "sprc";
const std::string  kTag_sprc_KindStr = "sprite collections";


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTag_sprc : public CTag
{
  // friends
  friend class CTagFactory_sprc;
  
  public:
    // ct and dt
     CTag_sprc(void) : CTag(kTag_sprc), ImageData(0), SequenceCount(0) { }
    ~CTag_sprc(void)                   
	{
		if(ImageData)
			delete[] ImageData;
		TextureCollection.clear();
		Sequence.clear();
	}
  
    // size accessor
    virtual size_t Size(void)
    { int t = sizeof(*this) - sizeof(CTag); 
    return t; }
	
	std::vector< CTexture > GetTextureSet(void)const { return TextureCollection; }

    // data members
    struct DataMembers
	{
        DataMembers(): frames_per_facing(0), facings(0), frameWidth(0), frameHeight(0)
        {}
        
		long frames_per_facing;	///< number of frames in the collection
		long facings;			///< number of facings available (frames/frames per facing)
		long frameWidth;		///< width of each image (constant for a sequence)
		long frameHeight;		///< height of each image (constant for a sequence
	};

	std::vector< DataMembers > Sequence;			///< holds all of the sequences, ordered
	std::vector< CTexture > TextureCollection;		///< Master collection of textures in the sprite collection
	int SequenceCount;								///< number of sequences in the collection
	unsigned char *ImageData;		///< raw image data, allocated once all sequences have been loaded
};


#endif  
