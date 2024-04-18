/*!
	@file		CTagFactory_pgrp.cpp
	@author	Scott Smith
	@date		December 1, 2003

	@brief	projectile group tag
______________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CTagFactory_pgrp.h"

/*                                                             static members
----------------------------------------------------------------------------- */

CTagFactory_pgrp  CTagFactory_pgrp::smRegistrar;


/*! @@brief Unarchives a tag from a stream of bytes.

    @@param tag    Pointer to the tag to unarchive into.
    @@param bytes  The bytestream containing the tag data.
______________________________________________________________________________*/
void CTagFactory_pgrp::DoUnarchive(CTag *tag, nsl::bstream &bytes)
{
CTag_pgrp* tTag = dcast< CTag_pgrp* >(tag);
  
  if(0 != tTag)
  {
		bytes >> tTag->mCount;
		
		for(unsigned int i = 0; i < tTag->mCount; ++i)
		{
			std::string s;
			bytes >> s;
			tTag->mTags.push_back(s);
    }
		
		bytes >> tTag->mType >> tTag->mSpread; 
	}

}

/*! @@brief Archives a tag to a stream of bytes.

    @@param tag    Pointer to the tag to archive from.
    @@param bytes  The bytestream to contain the tag data.
______________________________________________________________________________*/
void CTagFactory_pgrp::DoArchive(CTag *tag, nsl::bstream &bytes)
{
	CTag_pgrp* tTag = dcast< CTag_pgrp* >(tag);
  
  if(0 != tTag)
  {
		bytes << tTag->mCount;
		for(unsigned int i = 0; i < tTag->mTags.size(); ++i)
			bytes << tTag->mTags[i];
		bytes << tTag->mType << tTag->mSpread;
  }
}
