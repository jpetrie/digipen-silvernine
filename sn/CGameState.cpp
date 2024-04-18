/*! =========================================================================
      
      @file    CGameState.cpp
      @author  plaukait
      @brief   Current State of the Game
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "CGameState.h"
/*                                                                    methods
----------------------------------------------------------------------------- */

/*!
	@brief		GameState Constructor
*/
CGameState::CGameState()
{
	// construct something
	map = 0;
}

/*!
	@brief		GameState destructor --> free all of the units
*/
CGameState::~CGameState()
{
	for(vector<CUnit *>::iterator CurUnit = masterUnits.begin(); CurUnit < masterUnits.end(); ++CurUnit)
		delete *CurUnit;

  delete map;
}