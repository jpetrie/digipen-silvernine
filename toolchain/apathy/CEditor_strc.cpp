//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CTagMgrS.h"
#include "CEditor_strc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSTRC *frmSTRC;
//---------------------------------------------------------------------------
__fastcall TfrmSTRC::TfrmSTRC(TComponent* Owner,const std::string &fn)
: CEditor(Owner,kTag_strc)
{
  // Load the tag.
  mTag = (CTag_strc*)CTagMgr->Unarchive(kTag_strc,fn);
  PopulateControls();

  // Set the name.
  Caption = nsl::stformat("strc %s (%s)",mTag->Name().c_str(),mTag->Desc().c_str()).c_str();

}
//---------------------------------------------------------------------------
void TfrmSTRC::PopulateControls(void)
{
  txtStrings->Lines->Clear();

  for(unsigned int i = 0; i < mTag->stringCnt; ++i)
    txtStrings->Lines->Add(mTag->strings[i].c_str());
}
//---------------------------------------------------------------------------
void TfrmSTRC::PopulateTag(void)
{
  mTag->strings.clear();
  for(unsigned int i = 0; i < txtStrings->Lines->Count; ++i)
    mTag->strings.push_back(txtStrings->Lines->Strings[i].c_str());

  mTag->stringCnt = txtStrings->Lines->Count;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSTRC::btnSaveClick(TObject *Sender)
{
  // Archive the tag.
  PopulateTag();
  CTagMgr->Archive(mTag->Ident(),mTag);

  // Close the editor.
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSTRC::btnCancelClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------

