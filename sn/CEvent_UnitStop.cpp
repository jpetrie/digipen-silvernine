/*! =========================================================================
      
      @file    CEvent_UnitStop.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_UnitStop.h"
#include "CPacket_StopUnit.h"

/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_UnitStop::CEvent_UnitStop(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_UnitStop)
{
}


/*  _________________________________________________________________________ */
CEvent_UnitStop::~CEvent_UnitStop(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_UnitStop::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
	if(!CGame->NetGame())
	{
		for(unsigned int i = 0; i < units.size(); ++i)
			units[i]->MovePathFlush();
	}
	else
	{
		if(CGame->RequestState()->RequireStopValidation)
		{
			CPacket_StopUnit * packet = rcast<CPacket_StopUnit *>(NetworkManager->MakePacket(kPacket_StopUnit));
			packet->units = units;
			CGame->RequestState()->RequireStopValidation = false;	
		}
		else
		{
			for(unsigned int i = 0; i < units.size(); ++i)
			units[i]->MovePathFlush();
		}
	}
}