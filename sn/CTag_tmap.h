/*! =========================================================================
      
      @file    CTag_cphy.h
      @author  jpetrie
      @brief   'tmap' Tile Maps
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAG_TMAP_H_
#define _C_TAG_TMAP_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "NSL.h"

#include "CTag.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// tag id
const CTag::ID  kTag_tmap = nlFOURCODE('t','m','a','p');

// tag id strings
const std::string  kTag_tmap_TypeStr = "tmap";
const std::string  kTag_tmap_KindStr = "tile maps";


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTag_tmap : public CTag
/*! @brief tmap Tile Map tag.
*/
{
  // stereotypes
  nlCONTRACT_NOCOPY(CTag_tmap);

  // friends
  friend class CTagFactory_tmap;
  
  public:
    // structs
    struct StTile
    {
      std::string    name;            // For ease of use.
      unsigned char  sequenceNormal;  // When the tile is normal.
      unsigned char  sequenceBurnt;   // When the tile is burnt.
      unsigned int   terrainType;     // Terrain type.
      unsigned long  flags;           // Tile flags.
    };
    
    struct StUnit
    {
      std::string  name;      // (unit) Unit tag.
      float        x;         // World X.
      float        y;         // World Y.
      char         is_proxy;  // If true, unit is a proxy (name should be empty).
      char         team;      // Index of owning team.
    };
    
    struct StGroup
    {
      std::string         name;   // For ease of use.
      std::vector< int >  units;  // Unit indices.
    };
    
    struct StMarker
    {
      std::string  name;
      float        x;
      float        y;
    };
  
    // ct and dt
     CTag_tmap(void) : CTag(kTag_tmap) { mapWidth = mapHeight = tileCnt = unitCnt = groupCnt = 0; teamCnt = waypointCnt = 0; }
    ~CTag_tmap(void)                   { }
    
    // data members
    unsigned short                 mapWidth;      // In tiles.
    unsigned short                 mapHeight;     // In tiles.
    std::string                    collection;    // (sprc) Used for tile graphics.
    std::string                    pregameText;   // (text) Pregame story text.
    std::string                    postgameText;  // (text) Postgame story text.
    std::string                    startScript;   // (scri) Level begin control script.
    std::string                    stopScript;    // (scri) Level end control script.
    unsigned short                 tileCnt;       // Tile count.
    std::vector< StTile >          tileData;      // Tile data.
    std::vector< unsigned short >  tileLayout;    // Indices into tile data, defines tile map layout.
    
    unsigned char                  teamCnt;   // Maximum team count.
    unsigned short                 unitCnt;   // Unit count.
    std::vector< StUnit >          units;     // Unit instances.
    unsigned short                 groupCnt;  // Group count.
    std::vector< StGroup >         groups;    // Group instances.
    
    unsigned char                  waypointCnt;
    std::vector< StMarker >        waypoints;
};


#endif  /* _C_TAG_CPHY_H_ */
