/*!
	@file		CTag_proj.h
	@author	Scott Smith
	@date		November 17, 2003

	@brief	projectile tag
______________________________________________________________________________*/

#ifndef _C_TAG_PGRP_H_
#define _C_TAG_PGRP_H_

#include "NSL.h"
#include "CTag.h"

// tag id
const CTag::ID  kTag_pgrp = nlFOURCODE('p','g','r','p');

// tag id strings
const std::string  kTag_pgrp_TypeStr = "pgrp";
const std::string  kTag_pgrp_KindStr = "projectile groups";

const int kProjectileGroupType_Fan = 1;			///< projectiles fan out
const int kProjectileGroupType_Seek = 2;		///< projectiles seek a target
const int kProjectileGroupType_Random = 4;	///< projectiles shoot randomly
/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTag_pgrp : public CTag
{
  // friends
  friend class CTagFactory_pgrp;
  
  public:
    // ct and dt
		CTag_pgrp(void) : CTag(kTag_pgrp), mType(0), mSpread(0.0), mCount(0)			
		{ }
    ~CTag_pgrp(void) {	}
  
    // size accessor
    virtual size_t Size(void)
    { 
			int t = sizeof(*this) - sizeof(CTag); 
			return t;
		}
	
		std::vector<std::string>	mTags;
		int												mType;
		double										mSpread;
		unsigned int							mCount;
};


#endif 