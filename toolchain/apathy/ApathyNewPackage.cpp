//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ApathyNewPackage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmNewPackage *frmNewPackage;
//---------------------------------------------------------------------------
__fastcall TfrmNewPackage::TfrmNewPackage(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewPackage::btnCompileClick(TObject *Sender)
{
  ModalResult = mrOk;  
}
//---------------------------------------------------------------------------
void __fastcall TfrmNewPackage::btnCancelClick(TObject *Sender)
{
  ModalResult = mrCancel;  
}
//---------------------------------------------------------------------------
