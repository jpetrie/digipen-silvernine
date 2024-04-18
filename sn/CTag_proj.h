/*!
	@file		CTag_proj.h
	@author	Scott Smith
	@date		November 17, 2003

	@brief	projectile tag
______________________________________________________________________________*/

#ifndef _C_TAG_PROJ_H_
#define _C_TAG_PROJ_H_

#include "NSL.h"
#include "CTag.h"

// tag id
const CTag::ID  kTag_proj = nlFOURCODE('p','r','o','j');

// tag id strings
const std::string  kTag_proj_TypeStr = "proj";
const std::string  kTag_proj_KindStr = "projectiles";

#define	DAMAGE_TYPES	5
#define KINETIC				0
#define EXPLOSIVE			1
#define	BURN					2
#define	ELECTRICAL		3
#define	SYNC					4


const int kPromotesOnDetonation	= 1;
const int kDetonatesOnCollision =	2;
const int kDetonatesAtRest			=	4;

const int kDetonatesExplosives	= 1;
const int kIgnoresShielding			=	2;
const int kIgnoresOwner					= 4;

/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTag_proj : public CTag
{
  // friends
  friend class CTagFactory_proj;
  
  public:
    // ct and dt
		CTag_proj(void) : CTag(kTag_proj),
			in_flight_seq_idx(0), at_rest_seq_idx(0), det_seq_idx(0),
			det_flags(0), dam_flags(0), damage_type(0), damage_min(0),
			damage_max(0), damage_radius_min(0), damage_radius_max(0),
			damage_radius_fill_rate(0)
		{ }
    ~CTag_proj(void) {	}
  
    // size accessor
    virtual size_t Size(void)
    { 
			int t = sizeof(*this) - sizeof(CTag); 
			return t;
		}
	
		std::string		obje_tag;
		std::string		sprc_tag;
		int						in_flight_seq_idx;
		int						at_rest_seq_idx;
		int						det_seq_idx;
		int						det_flags;
		int						dam_flags;
		int						damage_type;
		float					damage_min;
		float					damage_max;
		float					damage_radius_min;
		float					damage_radius_max;
		float					damage_radius_fill_rate;	// percentage per frame

};


#endif 