/*!
    @file   CEditor_ablm.cpp
    @author Scott Smith
    @date   October 15, 2003

    @brief  Implements the actions of the Mental Ability editor
______________________________________________________________________________*/

//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "CEditor_ablm.h"
#include "CTagMgrS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmABLM *frmABLM;
//---------------------------------------------------------------------------
__fastcall TfrmABLM::TfrmABLM(TComponent* Owner,const std::string &fn)
: CEditor(Owner,kTag_ablm)
{
  // Load the tag.
  mTag = (CTag_ablm*)CTagMgr->Unarchive(kTag_ablm,fn);
  PopulateControls();

  // Set the name of the window.
  Caption = nsl::stformat("ablm %s (%s)",mTag->Name().c_str(),mTag->Desc().c_str()).c_str();
}
//---------------------------------------------------------------------------
void __fastcall TfrmABLM::PopulateControls(void)
{
  // Copy data from the tag to the form controls.
  cmbCollection->Text = mTag->collection.c_str();
  cmbUseGroup->Text = mTag->groupEffect.c_str();
  cmbProjGroup->Text = mTag->groupFired.c_str();
  edtBuyCost->Text = mTag->cashCost;
  edtSyncCost->Text = mTag->syncCost;
  edtMinDist->Text = mTag->minDistance;
  edtMaxDist->Text = mTag->maxDistance;
  edtDelay->Text = mTag->delay;
}
//---------------------------------------------------------------------------
void __fastcall TfrmABLM::PopulateTag(void)
{
  // Copy data from the controls to the tag.
  mTag->collection = cmbCollection->Text.c_str();
  mTag->groupEffect = cmbUseGroup->Text.c_str();
  mTag->groupFired = cmbProjGroup->Text.c_str();
  mTag->cashCost = edtBuyCost->Text.ToInt();
  mTag->syncCost = edtSyncCost->Text.ToDouble();
  mTag->minDistance = edtMinDist->Text.ToDouble();
  mTag->maxDistance = edtMaxDist->Text.ToDouble();
  mTag->delay = atoi(edtDelay->Text.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TfrmABLM::btnCancelClick(TObject *Sender)
{
  CTagMgr->Release(mTag);
  Release();
}
//---------------------------------------------------------------------------
void __fastcall TfrmABLM::btnSaveClick(TObject *Sender)
{
  PopulateTag();
  CTagMgr->Archive(kTag_ablm,mTag);
  CTagMgr->Release(mTag);
  Release();
}
//---------------------------------------------------------------------------


