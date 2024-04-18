//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "ApathyMain.h"
#include "CTagMgrS.h"
#include "CTagFactory.h"
#include "CEditor_mech.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMECH *frmMECH;
//---------------------------------------------------------------------------
__fastcall TfrmMECH::TfrmMECH(TComponent* Owner,const std::string &fn)
: CEditor(Owner,kTag_mech)
{
nsl::stringlist  tTags;

  // Load the tag.
  mTag = (CTag_mech*)CTagMgr->Unarchive(kTag_mech,fn);

  // Fill combo boxes.
  //frmMain->GetTagList(kTag_ablm,tTags);
 /// for(unsigned int i = 0; i < tTags.size(); ++i)
   // cmbMentName->Items->Add(tTags[i].c_str());

  PopulateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMECH::btnCancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMECH::PopulateControls(void)
{
  // Copy data from the tag to the form controls.
  edtObje->Text = mTag->objeTag.c_str();
  edtImgc->Text = mTag->sprcTag.c_str();

  edtIdle->Text = mTag->idleSeqncIndx;

  edtBaseSpeed->Text = mTag->baseSpeed;
  edtGround->Text = mTag->speedModGrass;
  edtPave->Text = mTag->speedModPavement;
  edtShallow->Text = mTag->speedModShallowWater;
  edtDeep->Text = mTag->speedModDeepWater;
  edtBrush->Text = mTag->speedModBrush;
  edtRocky->Text = mTag->speedModRocky;
  edtGrndImpas->Text = mTag->speedModGroundImpass;
  edtAirImpas->Text = mTag->speedModAirImpass;

  edtVisionRange->Text = mTag->visionRadius;
  edtRadarRange->Text = mTag->radarRadius;

  for(unsigned int i = 0; i < mTag->mentCnt; ++i)
  {
    lstMentAttacks->Items->Add(mTag->mentAttacks[i].c_str());
    lstMentAttacks->ItemIndex = lstMentAttacks->Items->Count - 1;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMECH::PopulateTag(void)
{
  // Copy data from the controls to the tag.
  mTag->objeTag = edtObje->Text.c_str();
  mTag->sprcTag = edtImgc->Text.c_str();

  mTag->idleSeqncIndx = atoi(edtIdle->Text.c_str());

  mTag->baseSpeed = edtBaseSpeed->Text.ToDouble();
  mTag->speedModGrass = edtGround->Text.ToDouble();
  mTag->speedModPavement = edtPave->Text.ToDouble();
  mTag->speedModShallowWater = edtShallow->Text.ToDouble();
  mTag->speedModDeepWater = edtDeep->Text.ToDouble();
  mTag->speedModBrush = edtBrush->Text.ToDouble();
  mTag->speedModRocky = edtRocky->Text.ToDouble();
  mTag->speedModGroundImpass = edtGrndImpas->Text.ToDouble();
  mTag->speedModAirImpass = edtAirImpas->Text.ToDouble();

  mTag->radarRadius = edtRadarRange->Text.ToDouble();
  mTag->visionRadius = edtVisionRange->Text.ToDouble();

  mTag->mentAttacks.clear();
  mTag->mentCnt = lstMentAttacks->Items->Count;
  for(unsigned int i = 0; i < lstMentAttacks->Items->Count; ++i)
    mTag->mentAttacks.push_back(lstMentAttacks->Items->Strings[i].c_str());
}
//---------------------------------------------------------------------------
void __fastcall TfrmMECH::btnSaveClick(TObject *Sender)
{
  // Archive the tag.
  PopulateTag();
  CTagMgr->Archive(mTag->Ident(),mTag);

  // Close the editor.
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMECH::btnAddMentClick(TObject *Sender)
{
  lstMentAttacks->Items->Add("????????");
  lstMentAttacks->ItemIndex = lstMentAttacks->Items->Count - 1;

  if(lstMentAttacks->Items->Count != 0)
    cmbMentName->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMECH::cmbMentNameChange(TObject *Sender)
{
int tIdx = lstMentAttacks->ItemIndex;

  lstMentAttacks->Items->Strings[tIdx] = cmbMentName->Text;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMECH::btnDeleteMentClick(TObject *Sender)
{
  lstMentAttacks->DeleteSelected();
  if(lstMentAttacks->Items->Count == 0)
    cmbMentName->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMECH::lstMentAttacksClick(TObject *Sender)
{
int tIdx = lstMentAttacks->ItemIndex;

  cmbMentName->Text = lstMentAttacks->Items->Strings[tIdx];
}
//---------------------------------------------------------------------------

