//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ApathyNewTag.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmNewTag *frmNewTag;
//---------------------------------------------------------------------------
__fastcall TfrmNewTag::TfrmNewTag(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewTag::btnCreateClick(TObject *Sender)
{
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewTag::btnCancelClick(TObject *Sender)
{
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

