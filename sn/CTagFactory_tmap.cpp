/*! =========================================================================
      
      @file    CTagFactory_tmap.cpp
      @author  jpetrie
      @brief   'tmap' tag factory.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory_tmap.h"


/*                                                             static members
----------------------------------------------------------------------------- */

CTagFactory_tmap  CTagFactory_tmap::smRegistrar;


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
void CTagFactory_tmap::DoUnarchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Unarchives a tag from a stream of bytes.

    @param tag    Pointer to the tag to unarchive into.
    @param bytes  The bytestream containing the tag data.
*/
{
CTag_tmap* tTag = dcast< CTag_tmap* >(tag);

  if(0 != tTag)
  {
    // Pull the tag data from the stream.
    bytes >> tTag->mapWidth >> tTag->mapHeight
          >> tTag->collection >> tTag->pregameText >> tTag->postgameText
          >> tTag->startScript >> tTag->stopScript;
          
    
    // Now do the tile chunk.
    bytes >> tTag->tileCnt;
    for(unsigned int i = 0; i < tTag->tileCnt; ++i)
    {
    CTag_tmap::StTile  tTile;
    
      bytes >> tTile.name
            >> tTile.sequenceNormal >> tTile.sequenceBurnt
            >> tTile.terrainType >> tTile.flags;

      tTag->tileData.push_back(tTile);
    }
    
    // Now do the tile layout chunk.
    for(int i = 0; i < (tTag->mapWidth * tTag->mapHeight); ++i)
    {
    unsigned short  tTile;
    
      bytes >> tTile;
      tTag->tileLayout.push_back(tTile);
    }
    
    // Now do the unit chunk.
    bytes >> tTag->teamCnt;
    bytes >> tTag->unitCnt;
    for(int i = 0; i < tTag->unitCnt; ++i)
    {
    CTag_tmap::StUnit  tUnit;
    
      bytes >> tUnit.name >> tUnit.x >> tUnit.y >> tUnit.is_proxy >> tUnit.team;
      tTag->units.push_back(tUnit);
    }
    
    // Now, the group chunk.
    bytes >> tTag->groupCnt;
    for(int i = 0; i < tTag->groupCnt; ++i)
    {
    CTag_tmap::StGroup  tGroup;
    unsigned long       tGroupSize;
    
      bytes >> tGroup.name;
      bytes >> tGroupSize;
      for(unsigned int j = 0; j < tGroupSize; ++j)
      {
      int  tUnitIdx;

        bytes >> tUnitIdx;
        tGroup.units.push_back(tUnitIdx);
      }
      tTag->groups.push_back(tGroup);
    }
    
    // Now, the waypoint chunk.
    bytes >> tTag->waypointCnt;
    for(int i = 0; i < tTag->waypointCnt; ++i)
    {
    CTag_tmap::StMarker  wayp;
    
      bytes >> wayp.name >> wayp.x >> wayp.y;
      tTag->waypoints.push_back(wayp);
    }
  }
}


/*  _________________________________________________________________________ */
void CTagFactory_tmap::DoArchive(CTag *tag,nsl::bstream &bytes)
/*! @brief Archives a tag to a stream of bytes.

    @param tag    Pointer to the tag to archive from.
    @param bytes  The bytestream to contain the tag data.
*/
{

CTag_tmap* tTag = dcast< CTag_tmap* >(tag);

  if(0 != tTag)
  {
    // Push the tag data into the stream.
    bytes << tTag->mapWidth << tTag->mapHeight
          << tTag->collection << tTag->pregameText << tTag->postgameText
          << tTag->startScript << tTag->stopScript;

    // Now do the tile chunk.
    bytes << tTag->tileCnt;
    for(int i = 0; i < tTag->tileCnt; ++i)
    {
    CTag_tmap::StTile  tTile;

      tTile = tTag->tileData[i];
      bytes << tTile.name
            << tTile.sequenceNormal << tTile.sequenceBurnt
            << tTile.terrainType << tTile.flags;
    }

    // Now do the tile layout chunk.
    for(int i = 0; i < (tTag->mapWidth * tTag->mapHeight); ++i)
      bytes << tTag->tileLayout[i];

    // Now do the unit chunk.
    bytes << tTag->teamCnt;
    bytes << tTag->unitCnt;
    for(int i = 0; i < tTag->unitCnt; ++i)
      bytes << tTag->units[i].name << tTag->units[i].x << tTag->units[i].y << tTag->units[i].is_proxy << tTag->units[i].team;
  
    // Now, the group chunk.
    bytes << tTag->groupCnt;
    for(int i = 0; i < tTag->groupCnt; ++i)
    {
      bytes << tTag->groups[i].name;
      bytes << (int)tTag->groups[i].units.size();
      for(unsigned int j = 0; j < tTag->groups[i].units.size(); ++j)
        bytes << tTag->groups[i].units[j];
    }
    
    // Now, the waypoint chunk.
    bytes << tTag->waypointCnt;
    for(int i = 0; i < tTag->waypointCnt; ++i)
    {
      bytes << tTag->waypoints[i].name;
      bytes << tTag->waypoints[i].x;
      bytes << tTag->waypoints[i].y;
    }
  }
}

