/*!
    @file   CEditor_ablp.cpp
    @author Scott Smith
    @date   October 15, 2003

    @brief  Implements the actions of the Mental Ability editor
______________________________________________________________________________*/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/

#include <vcl.h>
#pragma hdrstop
/*-----------------------------------------------------------------------------
Local Includes
-----------------------------------------------------------------------------*/
#include "CEditor_ablp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmABLP *frmABLP;

/*!
    TfrmABLM::TfrmABLP()
    @param  Owner   The parent form

    @brief  Setup for the Editor main form
______________________________________________________________________________*/
__fastcall TfrmABLP::TfrmABLP(TComponent* Owner)
        : TForm(Owner)
{
}
/*!
    TfrmABLM::btnABLPCancelClick()
    @param  Sender  The object to which the button belongs

    @brief  Closes the editor when the cancel button is clicked
______________________________________________________________________________*/
void __fastcall TfrmABLP::btnABLPCancelClick(TObject *Sender)
{
        this->Close();        
}
//---------------------------------------------------------------------------
