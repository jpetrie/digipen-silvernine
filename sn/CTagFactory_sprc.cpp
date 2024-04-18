/*!
	@file	CTagFactory_sprc.cpp
	@author	Scott Smith
	@date	October 16, 2003

	@brief	Provides a means of creating Sprite Collection tags
______________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */
#include <stdio.h>
#include "precompiled.h"
#include "CTagFactory_sprc.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#define COLOR_DEPTH	4
/*                                                             static members
----------------------------------------------------------------------------- */

CTagFactory_sprc  CTagFactory_sprc::smRegistrar;



/*! @brief Unarchives a tag from a stream of bytes.

    @param tag    Pointer to the tag to unarchive into.
    @param bytes  The bytestream containing the tag data.
______________________________________________________________________________*/
void CTagFactory_sprc::DoUnarchive(CTag *tag, nsl::bstream &bytes)
{
CTag_sprc* tTag = scast< CTag_sprc* >(tag);
unsigned long ByteCount = 0;  
  
  if(0 != tTag)
  {
	bytes >> tTag->SequenceCount;		// number of sequences to follow
	// stream each structure
	for(int seq = 0; seq < tTag->SequenceCount; ++seq)
	{
		CTag_sprc::DataMembers data;
		bytes	>> data.facings >> data.frames_per_facing \
				>> data.frameWidth >> data.frameHeight;
		ByteCount += (data.facings * data.frames_per_facing * 
					data.frameWidth * data.frameHeight * 4);			// fixme
		tTag->Sequence.push_back(data);
	}
	// read the raw image data for all of the tags
	if(ByteCount > 0)
	{
		tTag->ImageData = new unsigned char[ByteCount];
		memcpy(tTag->ImageData, bytes.raw_get(), ByteCount);
	}

	LoadGLTextures(tTag);
  }
}

/*! @brief Archives a tag to a stream of bytes.

    @param tag    Pointer to the tag to archive from.
    @param bytes  The bytestream to contain the tag data.
______________________________________________________________________________*/
void CTagFactory_sprc::DoArchive(CTag *tag, nsl::bstream &bytes)
{
CTag_sprc* tTag = scast< CTag_sprc* >(tag);
unsigned long ByteCount = 0;
  
  if(0 != tTag)
  {
	bytes << tTag->SequenceCount;		// number of sequences to follow
	// stream each structure

    /*FILE *fp = fopen("work", "wb");
    char b1[] = "sprc";
    short n = htons(12);
    char b2[] = "attack icons";
    fwrite(b1,sizeof(char), strlen(b1), fp);
    fwrite(&n, sizeof(short), 1, fp);
    fwrite(b2, sizeof(char), strlen(b2), fp);
    int i1 = htonl((tTag->SequenceCount));
    fwrite(&i1, sizeof(int), 1, fp);
	*/
    for(unsigned int seq = 0; seq < tTag->Sequence.size(); ++seq)
	{
    /*long l1 = (htonl(tTag->Sequence[seq].facings)),
        l2 = (htonl(tTag->Sequence[seq].frames_per_facing)),
        l3 = (htonl(tTag->Sequence[seq].frameWidth)),
        l4 = (htonl(tTag->Sequence[seq].frameHeight));
        fwrite(&l1, sizeof(long), 1, fp);
        fwrite(&l2, sizeof(long), 1, fp);
        fwrite(&l3, sizeof(long), 1, fp);
        fwrite(&l4, sizeof(long), 1, fp);
      */
		bytes	<< tTag->Sequence[seq].facings << tTag->Sequence[seq].frames_per_facing \
				<< tTag->Sequence[seq].frameWidth << tTag->Sequence[seq].frameHeight;
        ByteCount += (tTag->Sequence[seq].facings * tTag->Sequence[seq].frames_per_facing *
					tTag->Sequence[seq].frameWidth * tTag->Sequence[seq].frameHeight * 4);		 // fixme

	}
	// write the raw image data for all of the tags
	if(ByteCount > 0)
	{
    	bytes.raw_put((nsl::byte_t*)tTag->ImageData, ByteCount);
        //fwrite(tTag->ImageData, ByteCount, 1, fp);
        //fclose(fp);

    }
  }
}
/*!
	CTagFactory_sprc::LoadGLTextures()
	
	@brief Loads the textures from file into CTexture objects
_________________________________________________________________________*/
int CTagFactory_sprc::LoadGLTextures(CTag_sprc* sTag)						// Load Bitmaps And Convert To Textures
{
 	if(sTag->SequenceCount == 0)
		return false;
	std::vector< GLuint > vTex;
	GLuint texture = 0;
	unsigned char *atPointer = sTag->ImageData;
	for(int i = 0; i < sTag->SequenceCount; ++i)
	{
		for(int t = 0; t < (sTag->Sequence[i].frames_per_facing * sTag->Sequence[i].facings); ++t)
		{
			
			glGenTextures(1, &texture);					// Create The Texture

			glBindTexture(GL_TEXTURE_2D, texture);
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sTag->Sequence[i].frameWidth, sTag->Sequence[i].frameHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, atPointer);
			
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); 
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 

			vTex.push_back(texture);
			
			atPointer += (sTag->Sequence[i].frameHeight * sTag->Sequence[i].frameWidth * COLOR_DEPTH);   
			
		}
		
		// create an instance of a texture object (this is a texture set)
 		CTexture ctexture;
		ctexture.Create(vTex);
		ctexture.SetFacings(sTag->Sequence[i].facings);
		ctexture.SetFramesPerFacing(sTag->Sequence[i].frames_per_facing);
		// add it to the master texture list
		sTag->TextureCollection.push_back(ctexture);
		vTex.clear();

	
	}
	return true;										// Return The Status
}
