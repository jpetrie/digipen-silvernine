//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CEditor_sprcSCT.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSPRCCollectionTitle *frmSPRCCollectionTitle;
//---------------------------------------------------------------------------
__fastcall TfrmSPRCCollectionTitle::TfrmSPRCCollectionTitle(TComponent* Owner)
    : CEditor(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSPRCCollectionTitle::btnSPRCCollectionCancelClick(
      TObject *Sender)
{
    editSPRCSpriteCollectionTitle->Text = "";
    this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSPRCCollectionTitle::btnSPRCCollectionOKClick(
      TObject *Sender)
{
    this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSPRCCollectionTitle::FormActivate(TObject *Sender)
{
    editSPRCSpriteCollectionTitle->Text = "";
    editSPRCSpriteCollectionTitle->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TfrmSPRCCollectionTitle::editSPRCSpriteCollectionTitleKeyDown(
      TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_RETURN)
        this->Close();
}
//---------------------------------------------------------------------------

