//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CTagMgrS.h"
#include "CTagFactory.h"
#include "CEditor_obje.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmOBJE *frmOBJE;
//---------------------------------------------------------------------------
__fastcall TfrmOBJE::TfrmOBJE(TComponent* Owner,const std::string &fn)
: CEditor(Owner,kTag_obje)
{
  // Load the tag.
  mTag = (CTag_obje*)CTagMgr->Unarchive(kTag_obje,fn);
  PopulateControls();

  // Set the name.
  Caption = nsl::stformat("obje %s (%s)",mTag->Name().c_str(),mTag->Desc().c_str()).c_str();
}
//---------------------------------------------------------------------------
void __fastcall TfrmOBJE::btnCancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmOBJE::PopulateControls(void)
{
  // Copy data from the tag to the form controls.
  edtArmorHi->Text = mTag->armorHi;
  edtArmorLo->Text = mTag->armorLo;
  edtShieldHi->Text = mTag->shieldHi;
  edtShieldLo->Text = mTag->shieldLo;

  edtMass->Text = mTag->mass;
  edtRadius->Text = mTag->radius;
  edtHeight->Text = mTag->height;

  edtDmgKineticHi->Text = mTag->dmgKineticHi;
  edtDmgKineticLo->Text = mTag->dmgKineticLo;
  edtDmgExplosiveHi->Text = mTag->dmgExplosiveHi;
  edtDmgExplosiveLo->Text = mTag->dmgExplosiveLo;
  edtDmgBurningHi->Text = mTag->dmgBurningHi;
  edtDmgBurningLo->Text = mTag->dmgBurningLo;
  edtDmgElectricalHi->Text = mTag->dmgElectricalHi;
  edtDmgElectricalLo->Text = mTag->dmgElectricalLo;
  edtDmgSyncHi->Text = mTag->dmgSyncHi;
  edtDmgSyncLo->Text = mTag->dmgSyncLo;

  chkIgnoreCollision->Checked = !!(mTag->flags & kObject_IgnoreCollision);
  chkDrawSelection->Checked = !!(mTag->flags & kObject_DrawSelection);
  chkDrawStatus->Checked = !!(mTag->flags & kObject_DrawStatus);
}
//---------------------------------------------------------------------------
void __fastcall TfrmOBJE::PopulateTag(void)
{
  // Copy data from the controls to the tag.
  mTag->armorHi = atof(edtArmorHi->Text.c_str());
  mTag->armorLo = atof(edtArmorLo->Text.c_str());
  mTag->shieldHi = atof(edtShieldHi->Text.c_str());
  mTag->shieldLo = atof(edtShieldLo->Text.c_str());

  mTag->mass = atof(edtMass->Text.c_str());
  mTag->radius = atof(edtRadius->Text.c_str());
  mTag->height = atof(edtHeight->Text.c_str());

  mTag->dmgKineticHi = atof(edtDmgKineticHi->Text.c_str());
  mTag->dmgKineticLo = atof(edtDmgKineticLo->Text.c_str());
  mTag->dmgExplosiveHi = atof(edtDmgExplosiveHi->Text.c_str());
  mTag->dmgExplosiveLo = atof(edtDmgExplosiveLo->Text.c_str());
  mTag->dmgBurningHi = atof(edtDmgBurningHi->Text.c_str());
  mTag->dmgBurningLo = atof(edtDmgBurningLo->Text.c_str());
  mTag->dmgElectricalHi = atof(edtDmgElectricalHi->Text.c_str());
  mTag->dmgElectricalLo = atof(edtDmgElectricalLo->Text.c_str());
  mTag->dmgSyncHi = atof(edtDmgSyncHi->Text.c_str());
  mTag->dmgSyncLo = atof(edtDmgSyncLo->Text.c_str());

  mTag->flags = 0;
  mTag->flags |= (chkIgnoreCollision->Checked ? kObject_IgnoreCollision : 0);
  mTag->flags |= (chkDrawSelection->Checked ? kObject_DrawSelection : 0);
  mTag->flags |= (chkDrawStatus->Checked ? kObject_DrawStatus : 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmOBJE::btnSaveClick(TObject *Sender)
{
  // Archive the tag.
  PopulateTag();
  CTagMgr->Archive(mTag->Ident(),mTag);

  // Close the editor.
  Close();
}
//---------------------------------------------------------------------------

