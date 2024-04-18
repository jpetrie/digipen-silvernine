/*! =========================================================================
      
      @file    client.cpp
      @brief   Client main source file.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "sn.h"
#include "sn_buildstamp.h"

#include "CConfigMgrS.h"
#include "CGraphicsMgrS.h"
#include "CScriptMgrS.h"
#include "CTagMgrs.h"
#include "CSoundMgrS.h"

#include "CGameEngine.h"

#include "CNetworkMgrS.h"

/*                                                        internal prototypes
----------------------------------------------------------------------------- */

// config defaults
void LoadConfigDefaults(void);


/*                                                                  functions
----------------------------------------------------------------------------- */
void NetRecvCallBack(CPacket & packet, CSocket & socket)
{
	packet.Handle(CGame->RequestState(), &socket);
}


/*  _________________________________________________________________________ */
int WINAPI WinMain(HINSTANCE thisInst,HINSTANCE prevInst,LPSTR cmdLine,int cmdShow)
/*! @brief Application entry point.

    @param thisInst  Handle to current application instance.
    @param prevInst  Handle to previous application instance.
    @param cmdLine   Specifies command-line options.
    @param cmdShow   Specifies window-presentation method.

    @return
    A result code.
*/
{
int  tResult = -1;

  __try
  {
    // Reactivate the console.
    if(AllocConsole())
    {
      SetConsoleTitle("Silver Nine");
      freopen("CONOUT$","w",stdout);
    }
    
    // Run.
    tResult = WinMainHandled(thisInst,prevInst,cmdLine,cmdShow);
  }
  __except(WinExceptInfo(GetExceptionInformation()))
  {
  }
  
  // Cleanup.
  FreeConsole();
  return (tResult);
}


/*  _________________________________________________________________________ */
int WINAPI WinMainHandled(HINSTANCE /*thisInst*/,HINSTANCE /*prevInst*/,LPSTR /*cmdLine*/,int /*cmdShow*/)
/*! @brief SEH-controlled entry point.

    @param thisInst  Handle to current application instance.
    @param prevInst  Handle to previous application instance.
    @param cmdLine   Specifies command-line options.
    @param cmdShow   Specifies window-presentation method.

    @return
    A result code.
*/
{
bool  tDone = false;
MSG   tMsg;

  srand(timeGetTime());
  std::cout << "Silver Nine\n";
  std::cout << "  Build " << build_stamp() << ")\n\n";

  // Note that the order in which things are done in this try block
  // is VERY IMPORTANT. So don't screw around unless you know
  // what you're doing.
  try
  {
  CConfigMgrS    tCoM;           // The config manager.

    // Read config file.
    LoadConfigDefaults();
    CConfigMgr->ParseConfig("data/silvernine.cfg");
    
    
  CGraphicsMgrS  tGrM(WinProc);  // The graphics manager.
  CTagMgrS       tTaM;           // The tag manager.
  CScriptMgrS    tScM;           // The script manager.
  CNetworkMgrS   tNeM;			     // The network manager.
  CSoundMgrS	tSoM;
  
    // Scriptable registration.
	  UIScreen::RegisterScriptableClass(UIScreen());
	  CUnit::RegisterScriptableClass(CUnit());
	  CArmy::RegisterScriptableClass(CArmy());
	  CMap::RegisterScriptableClass(CMap());
	  CWaypoint::RegisterScriptableClass(CWaypoint());
	  CAttack::RegisterScriptableClass(CAttack());
	
	  // Build quad tree.
	  CGraphicsMgr->BuildQuadTree(0,0,CConfigMgr->GetValueAsInt("gfx_resx"),CConfigMgr->GetValueAsInt("gfx_resy"));
	
	  
  CGameEngine    tGameEngine;    // The game engine.

	// General setup.
	tNeM.RegisterRecvFunc(NetRecvCallBack);
	
	tSoM.Init();
	char songtest[] = "./data/patch/sound collections/scars left by time.mp3";
	
	//tSoM.Play(songtest, true);
	
    // And run.
	  while(!tDone)
	  {
      // Handle Windows messages.
      if(PeekMessage(&tMsg,0,0,0,PM_REMOVE))
        if(tMsg.message == WM_QUIT)
          tDone = true;
        else
          DispatchMessage(&tMsg);
      
	    // Process any pending network messages
	    tNeM.ProcessNetwork();

      // Handle game messages.
      CGame->ProcessServerTasks();
      CGame->ProcessClientTasks();
    }
  }
  catch(std::exception &e)
  {
    MessageBox(0,e.what(),"Exception Caught",MB_OK);
  }
  catch(...)
  {
    MessageBox(0,"Caught unknown exception.","Exception Caught",MB_OK);
  }
  
  return (0);
}


/*  _________________________________________________________________________ */
LRESULT CALLBACK WinProc(HWND wind,UINT msg,WPARAM wp,LPARAM lp)
/*! @brief Application message handler.

    @param wind  Handle to the window the message is for.
    @param msg   Message identifer.
    @param wp    Message payload 1.
    @param lp    Message payload 2.

    @return
    A result code.
*/
{
  if(!CGameEngine::exists())
    return (DefWindowProc(wind,msg,wp,lp));

  switch(msg)
  {
    case WM_CLOSE:
    {
			PostQuitMessage(0);
      return (0);
    }
    case WM_MOUSEMOVE:
    {
      if(!!(wp & MK_LBUTTON))
      {
        // Drag mouse move.
        CGame->SetMouse(LOWORD(lp),HIWORD(lp));
        CGame->LeftMouseDrag();
      }
      else
      {
        // Regular mouse move.
        CGame->SetMouse(LOWORD(lp),HIWORD(lp));
		CGame->MouseMove(LOWORD(lp),HIWORD(lp));
      }
      return (0);
    }
    case WM_LBUTTONDOWN:
    {
      CGame->LeftMouseDown();
      return (0);
    }
    case WM_LBUTTONUP:
    {
      CGame->LeftMouseUp();
      return (0);
    }
    case WM_RBUTTONDOWN:
    {
      CGame->RightMouseDown();
      return (0);
    }
    case WM_KEYDOWN:
    {
      CGame->SetKey((int)wp,true);
      return (0);
    }
    case WM_KEYUP:
    {
      CGame->SetKey((int)wp,false);
      return (0);
    }
	case WM_SIZE:
	{
		CGraphicsMgr->ReSizeGLScene(LOWORD(lp), HIWORD(lp));
		return (0);
	}
    default:
    {
      return (DefWindowProc(wind,msg,wp,lp));
    }
  }
}


/*  _________________________________________________________________________ */
int WINAPI WinExceptInfo(LPEXCEPTION_POINTERS /*ptrs*/)
/*! @brief SEH exception filter function.

    @param ptrs  Exception data pointers.

    @return
    A result code indicating whether the __except block should be executed.
    This function will always return EXCEPTION_CONTINUE_SEARCH.
*/
{
  return (EXCEPTION_CONTINUE_SEARCH);
}


/*  _________________________________________________________________________ */
void LoadConfigDefaults(void)
/*! @brief Sets up config value defaults.
*/
{
  CConfigMgr->SetValueAsBool("gfx_fullscreen",false);
  CConfigMgr->SetValueAsInt("gfx_resx",800);
  CConfigMgr->SetValueAsInt("gfx_resy",600);
  
  CConfigMgr->SetValueAsString("tag_patches","data/patch");
  CConfigMgr->SetValueAsString("tag_packages","data/pack");
}