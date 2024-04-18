//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "CTagMgrS.h"
#include "CEditor_scri.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSCRI *frmSCRI;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
__fastcall TfrmSCRI::TfrmSCRI(TComponent* Owner,const std::string &fn)
: CEditor(Owner,kTag_scri)
{
  // Load the tag.
  mTag = (CTag_scri*)CTagMgr->Unarchive(kTag_scri,fn);
  PopulateControls();

  // Set the name of the window.
  Caption = nsl::stformat("scri %s (%s)",mTag->Name().c_str(),mTag->Desc().c_str()).c_str();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSCRI::PopulateControls(void)
{
  // Copy data from the tag to the form controls.
  edtScript->Text = mTag->uncompiled.c_str();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSCRI::PopulateTag(void)
{
  // Copy data from the controls to the tag.
  mTag->uncompiled = edtScript->Text.c_str();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSCRI::btnSaveClick(TObject *Sender)
{
  // Archive the tag.
  PopulateTag();
  CTagMgr->Archive(mTag->Ident(),mTag);

  // Close the editor.
  delete mTag;
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSCRI::btnCancelClick(TObject *Sender)
{
  delete mTag;
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSCRI::FormCreate(TObject *Sender)
{
//  
}
//---------------------------------------------------------------------------

