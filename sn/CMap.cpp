/*! =========================================================================

      @file    CMap.cpp
      @brief   Implementation of in-game map class.

    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"


#include "CTagMgrS.h"
#include "CTag_tmap.h"

#include "CEvent_LevelEnd.h"

#include "CMap.h"
#include "CArmy.h"

#include "CTagFactory_sprc.h"
/*                                                         internal constants
----------------------------------------------------------------------------- */

namespace
{
  const int  ikStuffDoneFlagCount = 256;  // Should be more than enough.  
};


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
bool CMap::StTile::AStarEquiv(const CMap::StTile &t) const
/*! @brief Determine if two tiles are the same.

    @param t  The tile to compare the invoking tile against.
    
    @return
    True if the invoking tile and t share the same X and Y coordinates in
    tile space.
*/
{
  return (x == t.x && y == t.y);
}


/*  _________________________________________________________________________ */
int CMap::StTile::AStarCost(const CUnit &unit) const
/*! @brief Determine the movement cost to cross a tile.

    AStarCost() returns the movement cost for the specified unit to cross the
    tile, taking into account the unit's object's terrain penalities and other
    relevant factors.

    @param unit  The unit crossing the tile.
    
    @return
    The cost to cross the tile.
*/
{
  return (1);
}


/*  _________________________________________________________________________ */
int CMap::StTile::AStarDist(const CUnit &/*unit*/,const StTile &t) const
/*! @brief Determine the heuristic distance to a tile.

    AStarDist() returns the (heuristic) distance between the invoking tile
    and the tile t, using the properties and status of the specified unit to
    weight the result.

    @param unit  The unit crossing the tilespace.
    @param t     The goal tile.
    
    @return
    The distance between the invoking tile and the tile t.
*/
{
  return (scast< int >((sqrt((gx - t.gx) * (gx - t.gx) + (gy - t.gy) * (gy - t.gy)))));
}


/*  _________________________________________________________________________ */
CMap::CMap(const std::string &tag,std::vector< CArmy* > *armies,TLoadCallback progress)
/*! @brief Default constructor.

    If the tag parameter is allowed to default (to the empty string), the
    map will be initialized to sane (but probably useless) values.

    @param tag       The name of the tag to load data from.
    @param armies    The preloaded army data.
    @param progress  The progress callback.
*/
: mWidth(0),mHeight(0),
  mStuffDoneFlags(ikStuffDoneFlagCount,0.0f),
  mWinningTeam(-1)
{
  if(tag.length() > 0)
    LoadFromTag(tag,armies,progress);
}


/*  _________________________________________________________________________ */
CMap::~CMap(void)
/*! @brief Destructor.
*/
{
  nDestroy();
}



/*  _________________________________________________________________________ */
void CMap::LoadFromTag(const std::string &tag,std::vector< CArmy* > *armies,TLoadCallback progress)
/*! @brief Reinitializes an object from the specified tag.

    It is safe to call this function repeatedly.

    @param tag       The name of the tag to load data from.
    @param armies    The preloaded army data.
    @param progress  The progress callback.
*/
{
CTag_tmap *tTag = scast< CTag_tmap* >(CTagMgr->Unarchive(kTag_tmap,tag));
float      tX   = kMapTile_EvenRowAdjust;
float      tY   = kMapTile_FirstRowAdjust;
float      tPercent;

/*
*
*	- Mini map creation code - 
*
*/
CTag_sprc *minimap = scast<CTag_sprc*>(CTagMgr->Create(kTag_sprc));
CTag_sprc::DataMembers d;
d.facings = 1;
d.frameHeight = tTag->mapHeight;
d.frameWidth = tTag->mapWidth;
d.frames_per_facing = 1;
minimap->Sequence.push_back(d);
minimap->SequenceCount = 1;

minimap->ImageData = new unsigned char[d.frameHeight * d.frameWidth * 4];
unsigned char *at = minimap->ImageData;
//sf.LoadGLTextures(minimap); //make this call after all map data is loaded

  if(0 != tTag)
  {
  std::vector< int > idxs(tTag->teamCnt);
  
    nDestroy();

    // We'll want to cache the sprite collection.
    progress("Loading tileset...");
    CTagMgr->Cache(kTag_sprc,tTag->collection);
    
    mControlScript = tTag->stopScript;
    
    // Basic properties.
    mWidth = tTag->mapWidth;
    mHeight = tTag->mapHeight;
    
    // The tiles.
    for(unsigned int i = 0; i < mHeight; ++i)
    {
      tPercent = 100.0f * ((float)i / (float)mHeight);
      progress(nsl::stformat("Loading tiles (%d%%)...",scast< int >(tPercent)));
      
      for(unsigned int j = 0; j < mWidth; ++j)
      {
      nsl::point2D< float >  tGraphPt;
      StTile                *tTile = new StTile;
      unsigned short         tTileIdx = tTag->tileLayout[i * mWidth + j];
        
        // Set up the tile's coordinates.
        // The "graph point" is the tile's location in a pseudo-connectivity graph
        // that represents the map (to account for the wider-than-they-are-tall tiles).
        tTile->x = j;
        tTile->y = i;
        tGraphPt = TileToWorld(j,i);
        tTile->gx = tGraphPt.x / 2.0f;
        tTile->gy = tGraphPt.y;
        
        // Set the rest of the tile.
        tTile->terrain = scast< ETerrainType >(tTag->tileData[tTileIdx].terrainType);
        tTile->is_burnable = true;
        
		*at =		(unsigned char)(kTerrainColors[tTile->terrain].red * 255);
		*(at + 1) = (unsigned char)(kTerrainColors[tTile->terrain].green * 255);
		*(at + 2) = (unsigned char)(kTerrainColors[tTile->terrain].blue * 255);
		*(at + 3) = (unsigned char)(.75 * 255);
		at += 4;

        tTile->sprite = new CSprite(tX,tY,kMapTile_RawWidth,kMapTile_RawHeight,
                        tTag->collection,
                        true,
                        tTag->tileData[tTileIdx].sequenceNormal,
                        0);
        tTile->sprite->SetFacing( rand() % (tTile->sprite->GetFaceCount()));
        
        // The weird Z order is needed to keep the tiles from overlapping each other.
        tTile->sprite->SetZOrder(-(tY + 1));
		    CGraphicsMgr->AddMapTile(tTile->sprite);
				
        // Store it and move on.
        mTiles.push_back(tTile);
        tX += kMapTile_Width;
      }
      
      // Move to the next row.
      tY += kMapTile_NextRowAdjust;
      if(i % 2)
        tX = kMapTile_EvenRowAdjust;
      else
        tX = kMapTile_OddRowAdjust;
    }
	//CTagMgr->ArchiveTo(kTag_sprc, "temp.sprc", minimap);
	CTagFactory_sprc::LoadGLTextures(minimap);
	// make sprite here !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	CGraphicsMgr->minimap = new CSprite(100, 100, d.frameWidth, d.frameHeight, minimap);
	CGraphicsMgr->minimap->SetWidth(CGraphicsMgr->minimap->GetWidth() * 5);
	CGraphicsMgr->minimap->SetHeight(CGraphicsMgr->minimap->GetHeight() * 2.5);

	CGraphicsMgr->minimap->SetZOrder(-50000);
	CTagMgr->Release(minimap);
    // Force tile sprites to be draw in the background.
		//CGraphicsMgr->SortList();
		
		progress("Loading units...");
		
		// Armies passed to this function are NOT
		// owned by the map, and will not be released
		// when it is. They are the first armies in the
		// map's list.
		mUnownedArmies = (unsigned int)armies->size();
		for(unsigned int i = 0; i < mUnownedArmies; ++i)
		{
		  mArmyList.push_back(armies->at(i));
		  idxs[i] = 0;
		}
		
		// All the other armies are owned by the map.
		for(unsigned int i = mUnownedArmies; i < tTag->teamCnt; ++i)
		{
		  mArmyList.push_back(new CArmy);
		  idxs[i] = 0;
		}
		// Read units.
		int sztemp = tTag->unitCnt;
		for(unsigned int i = 0; i < tTag->unitCnt; ++i)
		{
		CUnit *tUnit;
		
		  // Proxy units are not loaded, but rather pulled in order
		  // from the appropriate army.
		  if(tTag->units[i].is_proxy)
		  {
		  unsigned int  tTeam = tTag->units[i].team;
		 // static int           tIdx = 0;
		  
		    tUnit = mArmyList[tTeam]->GetActiveUnit(idxs[tTeam]++);
		    //tUnit = mArmyList[tTeam]->GetActiveUnit(tIdx++);
		    if(0 != tUnit)
		    {
          tUnit->Ident(i);
          tUnit->SetPosition(tTag->units[i].x,tTag->units[i].y);
          tUnit->Show(true);
          mUnitList.push_back(tUnit);
        }
		  }
		  else
		  {
		  unsigned int  tTeam = tTag->units[i].team;
		    
		    tUnit = new CUnit(tTag->units[i].name,tTeam,-1);
		    tUnit->Ident(i);
        tUnit->SetPosition(tTag->units[i].x,tTag->units[i].y);
        tUnit->Show(true);
        mUnitList.push_back(tUnit);  
		  }
		}
		
	 // Build groups.
    for(unsigned int i = 0; i < tTag->groupCnt; ++i)
    {
    StGroup *tGroup = new StGroup;
    
      tGroup->name = tTag->groups[i].name;
      tGroup->units = tTag->groups[i].units;
      mGroupList.push_back(tGroup);
      mGroupMap.insert(std::make_pair(tGroup->name,tGroup));
    }
		
		// Load up the damn waypoints.
		for(unsigned int i = 0; i < tTag->waypointCnt; ++i)
		{
		CWaypoint *wayp = new CWaypoint;
	 
	    wayp->x = tTag->waypoints[i].x;
	    wayp->y = tTag->waypoints[i].y;
		  mWaypointMap.insert(std::make_pair(tTag->waypoints[i].name,wayp));
		}
  }
}


/*  _________________________________________________________________________ */
CMap::StTile& CMap::Tile(unsigned int x,unsigned int y)
/*! @brief Retrieve tile information.

    Tile() retrieves information about the tile at the specified (X,Y)
    coordinates within the map. If the coordinates are out of range, they are
    clamped to produce an in-range value.
    
    @param x  X tile coordinate.
    @param y  Y tile coordinate
    
    @return
    A mutable reference to the tile at (or nearest to) the specified position.
*/
{
  // Clamp the coordinates.
  if(x >= mWidth)
    x = mWidth - 1;
  if(y >= mHeight)
    y = mHeight - 1;
  
  return *(mTiles[mWidth * y + x]);
}


/*  _________________________________________________________________________ */
CUnit* CMap::Unit(unsigned int u)
/*! @brief Retrieve unit information.

    Unit() retrieves information about the tile at the specified index within
    the map's unit list. Note that the unit information contained within the
    map itself is positional only and is not updated during the course of the
    game - that sort of information is contained within the active CS9Session.
    
    If the index is out of range, it is clamped to return a valid value.
    
    @param u  Unit index.
    
    @return
    A mutable reference to the unit at (or nearest to) the specified index.
*/
{
  nsl::clampval< size_t >(u,0,mUnitList.size() - 1);
  return (mUnitList[u]);
}


unsigned int CMap::SizeOfTeam(unsigned int t)
{
  return mArmyList[t]->GetSizeofAvailable();
}

CUnit* CMap::UnitOfTeam(unsigned int t,unsigned int u)
{
  return mArmyList[t]->GetUnit(u);
}

unsigned int CMap::SizeOfActiveTeam(unsigned int t)
{
  return mArmyList[t]->GetSizeofActive();
}

CUnit* CMap::UnitOfActiveTeam(unsigned int t,unsigned int u)
{
  return mArmyList[t]->GetActiveUnit(u);
}


unsigned int CMap::SizeOfGroup(char *g)
{
TGroupMap::iterator  tIter = mGroupMap.find(std::string(g));
  
  if(tIter != mGroupMap.end())
    return tIter->second->units.size();
  return (0);
}

CUnit* CMap::UnitOfGroup(char *g,unsigned int u)
{
TGroupMap::iterator  tIter = mGroupMap.find(std::string(g));
  
  if(tIter != mGroupMap.end())
    return mUnitList[ tIter->second->units[u] ];
  return (0);
}



/*  _________________________________________________________________________ */
void CMap::Update(void)
/*! @brief Performs periodic updating.

    @param sim  The current game session.
*/
{
  // Let the control script execute.
  ExecuteScript(nsl::stformat("data/script/map/%s.mcs",mControlScript.c_str()));
  
  // If somebody won...
  if(mWinningTeam >= 0)
  {
  CEvent_LevelEnd *tEndEvt = (CEvent_LevelEnd*)CGame->MakeEvent(kEvent_LevelEnd);
    
    tEndEvt->win = (mWinningTeam == CGame->RequestState()->thisTeam);
    CGame->PostEvent(tEndEvt);
  }
}

/*  _________________________________________________________________________ */
nsl::point2D< int > CMap::WorldToTile(float wx,float wy)
/*! @brief Get the tile coordinate pair for a world coordinate pair.

    If the specified world coordinates are out of range, they are clamped so
    as to return a valid value.

    @param wx  The world X coordinate.
    @param wy  The world Y coordinate.
    
    @return
    A 2D integer point indicating the tile that contains the specified world
    coordinate.
*/
{
  // Clamp.
  if(wx < 0.0f)
    wx = 0.0f;
  if(wy < 0.0f)
    wy = 0.0f;
  if(wx > WorldWidth())
    wx = WorldWidth();
  if(wy > WorldHeight())
    wy = WorldHeight();

int               tSplitY = scast< int >((wy + kMapTile_HalfHeight) / kMapTile_HalfHeight) - 1;
int               tSplitX = scast< int >((wx + kMapTile_HalfWidth) / kMapTile_HalfWidth) - 1;
int               tLocalX = scast< int >(wx) % scast< int >(kMapTile_HalfWidth);
int               tLocalY = scast< int >(wy) % scast< int >(kMapTile_HalfHeight);
nsl::point2D< int >  tMapTile;

  // The split coordinates index into a rectangle that encloses no more than two tiles,
  // split (thus the name) by a diagonal line. This diagonal is lower-left to upper-right
  // for odd X splits, and upper-left to lower-right for even X splits.
  // To get the map tile clicked, we first determine which side of the split the click hit.
  if((tSplitX % 2) ^ (tSplitY % 2))
  // Even split.
  {  
  float  tLineY = -kMapTile_Slope * tLocalX + kMapTile_HalfHeight;

    if(tLocalY < tLineY)
    {
      // On the lower half.
      tMapTile.x = tSplitX / 2;
      tMapTile.y = tSplitY;
    }
    else
    {
      // On the upper half.
      tMapTile.x = (tSplitX / 2) + (tSplitY % 2 ? 0 : 1);
      tMapTile.y = tSplitY + 1;
    }
  }
  else
  // Odd split.
  {
  float  tLineY = kMapTile_Slope * tLocalX;
  
    if(tLocalY < tLineY)
    {
      // On the lower half.
      tMapTile.x = (tSplitX / 2) + (tSplitY % 2 ? 1 : 0);
      tMapTile.y = tSplitY;
    }
    else
    {
      // On the upper half.
      tMapTile.x = tSplitX / 2;
      tMapTile.y = tSplitY + 1;
    }
  }
  
  return (tMapTile);
}

/*  _________________________________________________________________________ */
nsl::point2D< float > CMap::TileToWorld(unsigned int tx,unsigned int ty)
/*! @brief Get the world coordinate pair for a tile coordinate pair.

    If the specified tile coordinates are out of range, they are clamped so
    as to return a valid value.

    @param wx  The world X coordinate.
    @param wy  The world Y coordinate.
    
    @return
    A 2D real point indicating the center of the specified tile, in the world
    coordinate system.
*/
{
nsl::point2D< float >  tWorldPt;

  // Clamp.
  if(tx >= TileWidth())
    tx = TileWidth() - 1;
  if(ty >= TileHeight())
    ty = TileHeight() -1;

  tWorldPt.x = (tx * kMapTile_Width);
  if(ty % 2 == 0)
    tWorldPt.x += kMapTile_HalfWidth;
  tWorldPt.y = ty * kMapTile_HalfHeight;
  
  return (tWorldPt);
}


/*  _________________________________________________________________________ */
void CMap::AStarGetChildren(const CUnit &unit,const CMap::StTile &node,std::vector< CMap::StTile > &children)
/*! @brief Gets the legal child nodes of a specified node.
    
    @param unit      The unit doing the pathfinding.
    @param node      The parent node.
    @param children  A reference to a vector to be filled with node children.
                     It is assumed that this vector is empty.
*/
{
  nTryAStarChild(unit,children,node.x - 1,node.y + 0);  // Left.
  nTryAStarChild(unit,children,node.x + 1,node.y + 0);  // Right.
  nTryAStarChild(unit,children,node.x + 0,node.y + 2);  // Top.
  nTryAStarChild(unit,children,node.x + 0,node.y - 2);  // Bottom.

  // The legal nodes differ slightly depending on the parity of the parent node's Y value.
  if(node.y % 2 == 0)
  {
    nTryAStarChild(unit,children,node.x + 0,node.y + 1);  // Upper left diagonal.
    nTryAStarChild(unit,children,node.x + 0,node.y - 1);  // Lower left diagonal.
    nTryAStarChild(unit,children,node.x + 1,node.y + 1);  // Upper right diagonal.
    nTryAStarChild(unit,children,node.x + 1,node.y - 1);  // Lower right diagonal.
  }
  else
  {
    nTryAStarChild(unit,children,node.x - 1,node.y + 1);  // Upper left diagonal.
    nTryAStarChild(unit,children,node.x - 1,node.y - 1);  // Lower left diagonal.
    nTryAStarChild(unit,children,node.x + 0,node.y + 1);  // Upper right diagonal.
    nTryAStarChild(unit,children,node.x + 0,node.y - 1);  // Lower right diagonal.
  }
}


void CMap::UnitRemove(CUnit *u)
{
TUnitList::iterator it = mUnitList.begin();

  while(*it != u && it != mUnitList.end())
    ++it;
  
  mUnitList.erase(it);
}




/*  _________________________________________________________________________ */
float CMap::SetSDF(unsigned int sdf,float value)
/*! @brief Sets the specified SDF.
*/
{
float  tOldSDF;

  tOldSDF = mStuffDoneFlags[sdf];
  mStuffDoneFlags[sdf] = value;
  return (tOldSDF);
}


/*  _________________________________________________________________________ */
float CMap::GetSDF(unsigned int sdf)
/*! @brief Gets the specified SDF.
*/
{
  return (mStuffDoneFlags[sdf]);
}


/*  _________________________________________________________________________ */
void CMap::SetLevelComplete(int winningTeam)
/*! @brief Schedules the level for completion.

    @param winningTeam  Index of the winning team.
*/
{
  mWinningTeam = winningTeam;
}


/*  _________________________________________________________________________ */
void CMap::nTryAStarChild(const CUnit &unit,std::vector< StTile > &children,int x,int y)
/*! @brief Attempts to expand the specified node.
*/
{
  if(unit.TerrainCost(Tile(x,y).terrain) > 0.0f)
    children.push_back(Tile(x,y));
}


/*  _________________________________________________________________________ */
void CMap::nDestroy(void)
/*! @brief Cleans up any resources currently used by the map.
*/
{
  // Release tiles.
  for(unsigned int i = 0; i < mTiles.size(); ++i)
  {
    delete mTiles[i]->sprite;
    delete mTiles[i];
  }
  mTiles.clear();
  
  // Release all armies that we don't own.//FIXME
 // for(int i = 0; i < mArmyList.size(); ++i)
  //  delete mArmyList[i];
  
  // Uncache scripts.
//  CTagFactory::ClearCache(kTag_scri,mControlScript);
}