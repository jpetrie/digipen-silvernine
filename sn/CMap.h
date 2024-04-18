/*! =========================================================================

      @file    CMap.h
      @author  jpetrie
      @brief   Interface to in-game map class.

    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_MAP_H_
#define _C_MAP_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CScriptableM.h"
#include "CScriptMgrS.h"

#include "CSprite.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// tile dimensions
const float kMapTile_Width      = 128.0f;                  // World units.
const float kMapTile_Height     = kMapTile_Width / 2.0f;   // World units.
const float kMapTile_HalfWidth  = kMapTile_Width / 2.0f;
const float kMapTile_HalfHeight = kMapTile_Height / 2.0f;  

// adjustments
const float kMapTile_EvenRowAdjust  = 0.0f;
const float kMapTile_OddRowAdjust   = -kMapTile_HalfWidth;
const float kMapTile_TopAdjust      = 32.0f;
const float kMapTile_BotAdjust      = 32.0f;
const float kMapTile_FirstRowAdjust = -2.0f * kMapTile_BotAdjust;
const float kMapTile_NextRowAdjust  = kMapTile_BotAdjust;
const float kMapTile_RawWidth       = kMapTile_Width;
const float kMapTile_RawHeight      = kMapTile_Height + kMapTile_TopAdjust + kMapTile_BotAdjust;
const float kMapTile_Slope          = kMapTile_Height / kMapTile_Width;

// terrain types
enum ETerrainType
{
  kTerrainGrass = 0,
  kTerrainPavement,
  kTerrainShallowWater,
  kTerrainDeepWater,
  kTerrainBrush,
  kTerrainRocky,
  kTerrainWalkingImpassable,
  kTerrainFlyingImpassable,
  kTerrain_Types              // Count of terrain types.
};

const COLORQUAD kTerrainColors[8] = {	COLORQUAD(0.f, .5f, 0.f),
										COLORQUAD(.2f, .2f, .2f),
										COLORQUAD(0.f, 1.f, 1.f),
										COLORQUAD(0.f, 0.f, .5f),
										COLORQUAD(1.f, 1.f, .7f),
										COLORQUAD(.5f, .5f, .5f),
										COLORQUAD(), 
										COLORQUAD() 
									};


/*                                                                    classes
----------------------------------------------------------------------------- */

// forward declarations
class CArmy;
class CUnit;

class CWaypoint : public CScriptableM< CWaypoint >
{
  public:
    CWaypoint(void) {}
    ~CWaypoint(void) {}
    
    EXPORT float X(void) { return (x); }
    EXPORT float Y(void) { return (y); }
    
    float x;
    float y;
};

/*  _________________________________________________________________________ */
class CMap : public CScriptableM< CMap >
/*! @brief Defines in-game map class.

    The map is layed out as an isometric grid of square tiles, represented
    internally as a single-dimensional array (that can be interpreted as a 2D
    grid). Tile numbering begins from the lower-left corner, such that the
    center of tile (0,0) is at (0,0) in the world. Every odd row (1, 3, 5, etc.)
    is offset in the world by half the width of the tile to produce the
    staggered, interlocking effect.
    
    There used to be a diagram here, but it didn't make the transition to
    Doxygen well, so it's gone now.
    
    The map, in-game, also holds ownership of the armies (and thus, indirectly,
    the units) and scenery objects on it. This is primarily to reduce the
    clutter required to access the aforementioned objects from script code.
*/
{
  // stereotypes
  nlCONTRACT_NOCOPY(CMap);
  
  public:
    // structs
    struct StTile
    //! Represents a tile.
    {
      int           x;            // X coordinate (tile space).
      int           y;            // Y coordinate (tile space).
      float         gx;           // X coordinate (graph space).
      float         gy;           // Y coordinate (graph space).
      ETerrainType  terrain;      // Tile terrain type.
      bool          is_burnable;  // Flag: Is the tile burnable?
      
      CSprite *sprite;  // Sprite used to render the tile.
      
      
      // A* node model functions
      bool AStarEquiv(const StTile &t) const;
      int  AStarCost(const CUnit &unit) const;
      int  AStarDist(const CUnit &unit,const StTile &t) const;
    };
    
    struct StGroup
    //! Represents a group of units. Used for scripting.
    {
      std::string         name;   // Group name.
      std::vector< int >  units;  // Units within the group.
    };
    
    
    // typedefs
    typedef void                              (*TLoadCallback)(const std::string&);
    typedef std::vector< StTile* >              TTileList;
    typedef std::vector< CArmy* >               TArmyList;
    typedef std::vector< CUnit* >               TUnitList;
    typedef std::vector< StGroup* >             TGroupList;
    typedef std::map< std::string,StGroup* >    TGroupMap;
    typedef std::map< std::string,CWaypoint* >  TWaypointMap;
    
    
    // ct and dt
             CMap(const std::string &tag = "",std::vector< CArmy* > *armies = 0,TLoadCallback progress = 0);
    virtual ~CMap(void);
    
    // initialization
    void LoadFromTag(const std::string &tag,std::vector< CArmy* > *armies,TLoadCallback progress = 0);
  
    // accessors
    StTile&      Tile(unsigned int x,unsigned int y);
    CUnit*       Unit(unsigned int u);
    unsigned int TileWidth(void) const   { return (mWidth); }
    unsigned int TileHeight(void) const  { return (mHeight); }
    float        WorldWidth(void) const  { return ((mWidth * kMapTile_Width) - kMapTile_HalfWidth); }
    float        WorldHeight(void) const { return ((mHeight * kMapTile_HalfHeight) - kMapTile_HalfHeight); }
    size_t       UnitCount(void) const   { return (mUnitList.size()); }
    size_t       TeamCount(void) const   { return (mArmyList.size()); }
    size_t       GroupCount(void) const  { return (mGroupList.size()); }
    
    // scriptable accessors
    EXPORT unsigned int SizeOfTeam(unsigned int t);
    EXPORT CUnit*       UnitOfTeam(unsigned int t,unsigned int u);
    EXPORT unsigned int SizeOfActiveTeam(unsigned int t);
    EXPORT CUnit*       UnitOfActiveTeam(unsigned int t,unsigned int u);
   
    EXPORT unsigned int SizeOfGroup(char *g);
   EXPORT  CUnit*       UnitOfGroup(char *g,unsigned int u);
    EXPORT CWaypoint* Waypoint(char *wp) { return(mWaypointMap[wp]); }
    
    // cleanup
    void UnitRemove(CUnit *u);
    
    TUnitList   mUnitList;   // Units on the map.
    
    // flow control
    EXPORT float SetSDF(unsigned int sdf,float value);
    EXPORT float GetSDF(unsigned int sdf);
    EXPORT void  SetLevelComplete(int winningTeam);
    EXPORT int WinningTeam(void) { return mWinningTeam; }
    
    // updates
    void Update(void);
    
    // tools
    nsl::point2D< int >   WorldToTile(float wx,float wy);
    nsl::point2D< float > TileToWorld(unsigned int tx,unsigned int ty);
    
    // A* map model functions
    void AStarGetChildren(const CUnit &unit,const StTile &node,std::vector< StTile > &children);


  private:
    // A* children
    void nTryAStarChild(const CUnit &unit,std::vector< StTile > &children,int x,int y);
  
    // cleanup
    void nDestroy(void);
    
    
    // data members
    unsigned int  mWidth;   // In tiles.
    unsigned int  mHeight;  // In tiles.
    
    TTileList  mTiles;     // Tiles in the map.
    
    std::vector< float >  mStuffDoneFlags;  // Variables for use with scripts.
    std::string           mControlScript;   // Level control script.
    
    TArmyList   mArmyList;   // Armies on the map (owns, except for the first few, see below).
    TGroupList  mGroupList;  // Groups on the map.
    
    TGroupMap  mGroupMap;  // Maps group names to actual groups.
    
    TWaypointMap  mWaypointMap;
    
    unsigned int  mUnownedArmies;  // Number of armies not owned by the map; always the first few in the list.
    
    int  mWinningTeam;  // The ID of the team that won the map.
};


#endif  /* _C_MAP_H_ */
