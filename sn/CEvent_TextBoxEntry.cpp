/*! =========================================================================
      
      @file    CEvent_TextBoxEntry.cpp
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CEvent_TextBoxEntry.h"


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CEvent_TextBoxEntry::CEvent_TextBoxEntry(void)
/*! @brief Default constructor.
*/
: CEvent(kEvent_TextBoxEntry)
{
}


/*  _________________________________________________________________________ */
CEvent_TextBoxEntry::~CEvent_TextBoxEntry(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
void CEvent_TextBoxEntry::Handle(CGameState *data)
/*! @brief Handles the event.
*/
{
  /*  SERVER_NAME_ENTRY, SERVER_IP_ENTRY, CHAT_TEXT_ENTRY */
	if( CGameState::SERVER_NAME_ENTRY == CGame->RequestServerState()->TextType )
	{
		CGame->RequestServerState()->serverName = text;	
		CGame->LoadUIScreen("data/script/ui_chat.uis");
		CGame->RequestServerState()->TextType = CGameState::SERVER_IP_ENTRY;
	}
	else if(CGameState::SERVER_IP_ENTRY == CGame->RequestServerState()->TextType)
	{
		// FOR GOODNESS SAKE, DO NOT USE THIS YET!!!
	}
	else if(CGameState::CHAT_TEXT_ENTRY == CGame->RequestServerState()->TextType)
	{
		// USE THIS WHEN CHATTING IS WORKING
	}

}