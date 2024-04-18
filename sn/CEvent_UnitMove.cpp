/*! =========================================================================
      
      @file    CEvent_UnitMove.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_UnitMove.h"
#include "CPacket_MoveRequest.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_UnitMove::CEvent_UnitMove(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_UnitMove)
{
}


/*  _________________________________________________________________________ */
CEvent_UnitMove::~CEvent_UnitMove(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_UnitMove::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{

	if(!CGame->NetGame())
	{
		std::vector< CMap::StTile >           tPath;
		nsl::point2D< int >                   tStart;
		nsl::point2D< int >                   tGoal;
		CMap::StTile                          tStartTile;
		CMap::StTile                          tGoalTile;
		std::vector< nsl::point2D< float > >  tFinalPath;

		for(unsigned int i = 0; i < units.size(); ++i)
		{
		float  deltaX = (units[i]->X() - units[0]->X());
		float  deltaY = (units[i]->Y() - units[0]->Y());
		  
			tStart = data->map->WorldToTile(units[i]->X(),units[i]->Y());
			tGoal = data->map->WorldToTile(x + deltaX,y + deltaY);
			tStartTile = data->map->Tile(tStart.x,tStart.y);
			tGoalTile = data->map->Tile(tGoal.x,tGoal.y);
		    
			// Units that can't get to their destination don't try and move.
			if(units[i]->TerrainCost(tGoalTile.terrain) == 0.0f)
			continue;
		    
			tPath.clear();
			data->pathEngine.GeneratePathSync(*(data->map),*units[i],tStartTile,tGoalTile,tPath);
			units[i]->MovePathFlush();
			units[i]->MovePathDestInternal(x + deltaX,y + deltaY);
			tFinalPath.clear();
			for(unsigned int j = 0; j < tPath.size() - 1; ++j)
			{
			nsl::point2D< float > tStep = { tPath[j].gx * 2.0f,tPath[j].gy };

			tFinalPath.push_back(tStep);    
			}
			units[i]->MovePathAppend(tFinalPath);
		}
	}
	else
	{
		if(CGame->RequestState()->RequiresMoveValidation)
		{
			CPacket_MoveRequest * mReq = rcast<CPacket_MoveRequest *>(NetworkManager->MakePacket(kPacket_MoveRequest));
			mReq->x = this->x;
			mReq->y = this->y;
			mReq->units = this->units;

			CGame->GetServSock().Send(*mReq);

			CGame->RequestState()->RequiresMoveValidation = true;
			//CGame->RequestState()->RequiresMoveValidation = !(CGame->RequestState()->RequiresMoveValidation);	
		}
		else
		{
			std::vector< CMap::StTile >           tPath;
			nsl::point2D< int >                   tStart;
			nsl::point2D< int >                   tGoal;
			CMap::StTile                          tStartTile;
			CMap::StTile                          tGoalTile;
			std::vector< nsl::point2D< float > >  tFinalPath;

			for(unsigned int i = 0; i < units.size(); ++i)
			{
				float  deltaX = (units[i]->X() - units[0]->X());
				float  deltaY = (units[i]->Y() - units[0]->Y());
			  
				std::cout << units[i]->Ident();
				tStart = data->map->WorldToTile(units[i]->X(),units[i]->Y());
				tGoal = data->map->WorldToTile(x + deltaX,y + deltaY);
				tStartTile = data->map->Tile(tStart.x,tStart.y);
				tGoalTile = data->map->Tile(tGoal.x,tGoal.y);
			    
				// Units that can't get to their destination don't try and move.
				if(units[i]->TerrainCost(tGoalTile.terrain) == 0.0f)
				continue;
			    
				tPath.clear();
				data->pathEngine.GeneratePathSync(*(data->map),*units[i],tStartTile,tGoalTile,tPath);
				units[i]->MovePathFlush();
				units[i]->MovePathDestInternal(x + deltaX,y + deltaY);
				tFinalPath.clear();
				for(unsigned int j = 0; j < tPath.size() - 1; ++j)
				{
				nsl::point2D< float > tStep = { tPath[j].gx * 2.0f,tPath[j].gy };

				tFinalPath.push_back(tStep);    
				}
				units[i]->MovePathAppend(tFinalPath);
			}

			CGame->RequestState()->RequiresMoveValidation = true;
			
		}
	}
}