/*! =========================================================================
      
      @file    sn.h
      @brief   Silver Nine main header file.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _SILVERNINE_H_
#define _SILVERNINE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"


/*                                                                 prototypes
----------------------------------------------------------------------------- */

// main
int WINAPI WinMain(HINSTANCE thisInst,HINSTANCE prevInst,LPSTR cmdLine,int cmdShow);
int WINAPI WinMainHandled(HINSTANCE thisInst,HINSTANCE prevInst,LPSTR cmdLine,int cmdShow);

// message handler
LRESULT CALLBACK WinProc(HWND wind,UINT msg,WPARAM wp,LPARAM lp);

// exception info
int WINAPI WinExceptInfo(LPEXCEPTION_POINTERS ptrs);


#endif  /* _SILVERNINE_H_ */
