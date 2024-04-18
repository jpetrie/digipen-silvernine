//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CEditor_tmapResize.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmTMAP_Resize *frmTMAP_Resize;
//---------------------------------------------------------------------------
__fastcall TfrmTMAP_Resize::TfrmTMAP_Resize(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP_Resize::btnCancelClick(TObject *Sender)
{
  ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP_Resize::btnResizeClick(TObject *Sender)
{
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------
