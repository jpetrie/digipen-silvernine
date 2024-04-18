/*!
	@file		CTagFactory_proj.cpp
	@author	Scott Smith
	@date		November 17, 2003

	@brief	projectile tag
______________________________________________________________________________*/

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"
#include "CTagFactory_proj.h"

/*                                                             static members
----------------------------------------------------------------------------- */

CTagFactory_proj  CTagFactory_proj::smRegistrar;


/*! @brief Unarchives a tag from a stream of bytes.

    @param tag    Pointer to the tag to unarchive into.
    @param bytes  The bytestream containing the tag data.
______________________________________________________________________________*/
void CTagFactory_proj::DoUnarchive(CTag *tag, nsl::bstream &bytes)
{
CTag_proj* tTag = dcast< CTag_proj* >(tag);
  
  if(0 != tTag)
  {
		bytes >> tTag->obje_tag >> tTag->sprc_tag 
					>> tTag->in_flight_seq_idx 
					>> tTag->at_rest_seq_idx 
					>> tTag->det_seq_idx 
					>> tTag->det_flags 
					>> tTag->dam_flags 
					>> tTag->damage_type 
					>> tTag->damage_min
					>> tTag->damage_max
					>> tTag->damage_radius_min
					>> tTag->damage_radius_max
					>> tTag->damage_radius_fill_rate;
	}

}

/*! @brief Archives a tag to a stream of bytes.

    @param tag    Pointer to the tag to archive from.
    @param bytes  The bytestream to contain the tag data.
______________________________________________________________________________*/
void CTagFactory_proj::DoArchive(CTag *tag, nsl::bstream &bytes)
{
	CTag_proj* tTag = dcast< CTag_proj* >(tag);
  
  if(0 != tTag)
  {
		bytes << tTag->obje_tag << tTag->sprc_tag 
					<< tTag->in_flight_seq_idx 
					<< tTag->at_rest_seq_idx 
					<< tTag->det_seq_idx 
					<< tTag->det_flags 
					<< tTag->dam_flags 
					<< tTag->damage_type 
					<< tTag->damage_min
					<< tTag->damage_max
					<< tTag->damage_radius_min
					<< tTag->damage_radius_max
					<< tTag->damage_radius_fill_rate;
  }
}
