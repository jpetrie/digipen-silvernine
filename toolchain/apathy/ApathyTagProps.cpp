//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ApathyTagProps.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmTagProps *frmTagProps;
//---------------------------------------------------------------------------
__fastcall TfrmTagProps::TfrmTagProps(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmTagProps::btnSaveClick(TObject *Sender)
{
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTagProps::btnCancelClick(TObject *Sender)
{
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

