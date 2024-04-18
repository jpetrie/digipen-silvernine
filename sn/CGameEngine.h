/*! =========================================================================
      
      @file    CGameEngine.h
      @brief   Interface to game engine class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_GAMEENGINE_H_
#define _C_GAMEENGINE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEventFactory.h"
#include "CEvent.h"

#include "CScriptMgrS.h"
#include "CScriptableM.h"

//#include "CMap.h"
#include "CArmy.h"

#include "CAStar.h"

#include "UIScreen.h"
#include "UIText.h"
#include "CSocket.h"
#include "CNetworkMgrS.h"


/*                                                                  constants
----------------------------------------------------------------------------- */

// shop sizes
const int kShop_UnitSize = 10;
const int kShop_WeaponSize = 5;
const int kShop_AbilitySize = 5;


const int kArmyListBiasLo = 1000; // Bias value for response codes from army pool list box
const int kArmyListBiasHi = 2000; // Bias value for response codes from army pool list box

// Bias value for response codes in army shop list boxes
const int kShopListBiasLO = 3000;
const int kUnitListBiasHI = 3300;
const int kAblpListBiasLO = 3301;
const int kAblpListBiasHI = 3600;
const int kAblmListBiasLO = 3601;
const int kAblmListBiasHI = 3900;
const int kShopListBiasHI = 4000;


/*                                                                    classes
----------------------------------------------------------------------------- */

// forward declarations
class CGameState;
class CProjectileGroup;
class CMap;

/*  _________________________________________________________________________ */
class CGameEngine : public nsl::singleton< CGameEngine >
/*! @brief Gameplay engine class.
*/
{
  // contracts
  nlCONTRACT_NOCOPY(CGameEngine);
  
  
  public:
    // ct and dt
	   CGameEngine(void);
	  ~CGameEngine(void);
	  
	  // state
	  CGameState* RequestState(void) { return (mClientState); }
	  CGameState* RequestServerState() { return mServerState; }
	  UIScreen*   RequestScreen(void) { return (mScreen); } 
	  
	  // events
	  CEvent* MakeEvent(CEvent::ID evt);
	  void    PostEvent(CEvent *evt);
	  
	  // task processing
	  void ProcessServerTasks(void);
	  void ProcessClientTasks(void);
	  
	  // ui hooks
	  bool GetKey(int k)         { return (mKeys[k]); }
	  void SetKey(int k,bool v)  { mKeys[k] = v; }
	  void SetMouse(int x,int y) { mMouseX = x; mMouseY = y; }
	  void LeftMouseDown(void);
	  void RightMouseDown(void);
	  void LeftMouseUp(void);
	  void LeftMouseDrag(void);
	  void MouseMove(int x, int y);
	  void LoadUIScreen(const std::string &sn) { mScreen->Show(false); mScreen->ClearScreen(); mScreen->ExecuteScript(sn); mScreen->Show(true); }
	  UIScreen * GetScreen() { return mScreen; }

	  // state transitions
	  void SetupForGameplay(void);
	  void EndGameplay(void);
	  
	
	  // Required for packet auth
	  bool NetGame() { return NetworkGame; }
	  void SetNetGame(bool NetGame) { NetworkGame = NetGame; }

	  // Accessors for socket communication
	  CSocket & GetServSock() { return mServSocket; }

	   // Socket data
	  vector<CSocket> mClientSocks; // Sockets for use by the server to communicate with clients
	
	  std::vector<int> mWaitingUnits;     // untis waiting to be purchased
	  std::vector<int> mWaitingAblp;      // physical abilities waiting to be purchased
	  std::vector<int> mWaitingAblm;      // mental abilities waiting to be purchased
	  
	  nsl::stringlist attacksAvail;
	
	private:
	  // typedefs
	  typedef std::queue< CEvent* >  TEventQueue;
	  
	  
	  // processing
	  void nProcessQueue(TEventQueue &q,CGameState *state);
	  void nProcessUpdates(CGameState *state);
	  void nProcessUI(CGameState *state);
	  
	  // data members
    nsl::uint32_t  mFrameTime;    // Length of an update frame (milliseconds).
    nsl::uint32_t  mLastTime;     // Time of last update.
    nsl::uint32_t  mElapsedTime;  // Time since last update.
	  
	  CGameState  *mClientState;  // Client (local) state.
	  CGameState  *mServerState;  // Server (remote) state.
	  TEventQueue  mClientQueue;  // Client events.
	  TEventQueue  mServerQueue;  // Server events.
	  
	  bool   mKeys[256];
	  int    mMouseX;
	  int    mMouseY;
	  DWORD  mClickTime;
	  
	  CSprite				*mParallax;
	  int					 mParallaxTimer;
	  int					 mParallaxDelay;
	  float					 mParallaxXstep;
	  float					 mParallaxYstep;
	  float					 mParallaxSpeed;
	  CRect                 *mSelRect;
	  bool                   mSelecting;
	  nsl::point2D< float >  mSelAnchor;
	  
	  UIScreen *mScreen;

	  // Socket data
	  bool NetworkGame;			    // Determine if the current game is network enabled
	  CSocket  mServSocket;		    // Connection to the server
	  
	  bool mAbort;
};


/*  _________________________________________________________________________ */
class CGameState : public CScriptableM< CGameState >
/*! @brief Gameplay state class.
*/
{
  public:
    // ct and dt
     CGameState(void) { nInit(); }
    ~CGameState(void) { };
  
    // properties
    CMap        *map;    // Map of current level.
    std::string  level;  // Name of current level.
    
    int                    thisTeam;    // Team ID of local machine.
    int                    thisPlayer;  // Player ID of local machine.
    std::vector< CArmy* >  teams;       // Teams on the map.
    //std::vector< CProjectile* > projectiles;
	std::vector< CProjectileGroup* > projGroups;
	std::vector< CUnit* >  selected;    // List of selected units.
 
    std::vector< CUnit* > hireUnits;
    nsl::stringlist  unitShop;  // List of tags for unit shop.
    nsl::stringlist  ablpShop;  // List of tags for weapon shop.
    nsl::stringlist  ablmShop;  // List of tags for ability shop.
 
    CText *army_Briefing;
 
    CAStar< CMap::StTile,CMap,CUnit >  pathEngine;  // The pathfinder.
   




	std::string serverName;				// Name of the server sent in response to net game requests
	std::map<int, std::string> serverIndex;	// Map of button indecies and their associated servers.
											// Used in conjunction with the server map below
	std::map<std::string, std::string> servers;		// List of servers currently on the network -- populated by a NetGame broadcast
	std::string gameName;				// Name of the game currently being run on the server
	std::string serverAddress;			// Address of the server
	std::string datagramAddress;					// Temp address for miscellaneous use
	bool IAmServer;						// Test if I am the current server
	UIText * TextBox;					// Text box currently in use
	enum TextBoxTypes { SERVER_NAME_ENTRY, SERVER_IP_ENTRY, CHAT_TEXT_ENTRY };
	enum TextBoxTypes TextType;

	int ButtonBoxIndex;					// Index of the button box (used for listing servers.  Set and reset by events)
    int CurrentServerListCode;			// Current code to be used for the list of servers
	int userServerChoice;				// Index into the UI button list that holds the user's choice of what game to join
										// Used by some events
	int currentUserID;					// Current user ID -- should be re-set to 0 upon creating a new game
	bool okToStartNetGame;				// Set by a packet when the server wants to start a game
	bool sentArmyData;					// Flag to check if army data was sent
	bool RequiresMoveValidation;		// Used for the move event to prevent cyclical authorization
	bool RequireStopValidation;			// Used for the stop event to prevent cyclical authorization
	bool RequireAttackValidation;		// Used for the attack event to prevent cyclical authorization
	int localPlayer;					// thisPlayer keeps getting set to 0 -> this holds the real value
  
  int army_PlayerUnitsList;  // Index of player units listbox.
    
  void Load(const std::string &fn) { CScriptMgr->ExecuteFile(fn); }
    
  private:
    // init
    void nInit(void);
};
 

/*                                                                     macros
----------------------------------------------------------------------------- */

// singleton accessor
#define CGame  CGameEngine::instance()


// This crap is for loading the initial game state.
EXPORT void DefinePlayerArmy(void);
EXPORT void DefinePlayerUnit(char *unit);

#endif  /* _C_GAMEENGINE_H_ */