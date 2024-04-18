//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CTagMgrS.h"

#include "CEditor_unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmUNIT *frmUNIT;
//---------------------------------------------------------------------------
__fastcall TfrmUNIT::TfrmUNIT(TComponent* Owner,const std::string &fn)
: CEditor(Owner,kTag_unit)
{
nsl::stringlist tTags;

  // Grab the tag.
  mTag = (CTag_unit*)CTagMgr->Unarchive(kTag_unit,fn);

  // Fill combo boxes.
  frmMain->GetTagList(kTag_mech,tTags);
  for(unsigned int i = 0; i < tTags.size(); ++i)
    cmbMechTag->Items->Add(tTags[i].c_str());
  //frmMain->GetTagList(kTag_scri,tTags);
  //for(unsigned int i = 0; i < tTags.size(); ++i)
   // cmbScriTag->Items->Add(tTags[i].c_str());

  frmMain->GetTagList(kTag_strc,tTags);
  for(unsigned int i = 0; i < tTags.size(); ++i)
    cmbNames->Items->Add(tTags[i].c_str());

  PopulateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmUNIT::btnSaveClick(TObject *Sender)
{
  PopulateTag();
  CTagMgr->Archive(mTag->Ident(),mTag);
  CTagMgr->Release(mTag);
  Release();
}
//---------------------------------------------------------------------------

void __fastcall TfrmUNIT::btnCancelClick(TObject *Sender)
{
  CTagMgr->Release(mTag);
  Release();
}
//---------------------------------------------------------------------------
void __fastcall TfrmUNIT::PopulateControls(void)
{
  cmbMechTag->Text = mTag->mech.c_str();
  cmbCharTag->Text = mTag->character.c_str();
  cmbScriTag->Text = mTag->script.c_str();

  cmbNames->Text = mTag->names.c_str();
  cmbFlavor->Text = "foo";

}
//---------------------------------------------------------------------------
void __fastcall TfrmUNIT::PopulateTag(void)
{
  mTag->mech = cmbMechTag->Text.c_str();
  mTag->character = cmbCharTag->Text.c_str();
  mTag->script = cmbScriTag->Text.c_str();

  mTag->names = cmbNames->Text.c_str();
  mTag->flavor = cmbFlavor->Text.c_str();
}
