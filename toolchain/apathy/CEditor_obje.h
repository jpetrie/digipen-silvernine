//---------------------------------------------------------------------------

#ifndef CEditor_objeH
#define CEditor_objeH

#include "CEditor.h"
#include "CEditorFactory.h"
#include "CTag_obje.h"

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmOBJE : public CEditor
{
__published:	// IDE-managed Components
  TCheckBox *chkDrawSelection;
  TCheckBox *chkDrawStatus;
  TCheckBox *chkIgnoreCollision;
  TLabel *Label7;
  TLabel *Label9;
  TLabel *Label10;
  TLabel *Label11;
  TLabel *Label12;
  TLabel *Label13;
  TLabel *Label14;
  TLabel *Label15;
  TLabel *Label16;
  TLabel *Label17;
  TEdit *edtDmgKineticLo;
  TEdit *edtDmgKineticHi;
  TEdit *edtDmgExplosiveLo;
  TEdit *edtDmgExplosiveHi;
  TEdit *edtDmgBurningLo;
  TEdit *edtDmgBurningHi;
  TEdit *edtDmgElectricalHi;
  TEdit *edtDmgElectricalLo;
  TEdit *edtDmgSyncHi;
  TEdit *edtDmgSyncLo;
  TGroupBox *GroupBox1;
  TGroupBox *GroupBox2;
  TGroupBox *GroupBox3;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  TLabel *Label4;
  TLabel *Label5;
  TLabel *Label8;
  TEdit *edtArmorLo;
  TEdit *edtArmorHi;
  TEdit *edtShieldLo;
  TEdit *edtShieldHi;
  TEdit *edtMass;
  TEdit *edtRadius;
  TCheckBox *chkUnused1;
  TCheckBox *chkUnused2;
  TButton *btnCancel;
  TButton *btnSave;
  TLabel *Label6;
  TEdit *edtHeight;
  void __fastcall btnCancelClick(TObject *Sender);
  void __fastcall btnSaveClick(TObject *Sender);
private:
  CTag_obje *mTag;

  void __fastcall PopulateControls(void);
  void __fastcall PopulateTag(void);

public:		// User declarations
  __fastcall TfrmOBJE(TComponent* Owner,const std::string &fn);
};
//---------------------------------------------------------------------------
class CEditorFactory_obje : public CEditorFactory
{
public:
  CEditorFactory_obje(void) : CEditorFactory(kTag_obje) { }


protected:
  CEditor* DoLaunch(const std::string &fn) { return new TfrmOBJE(0,fn); }

  private:
    static CEditorFactory_obje  smRegistrar;
};
CEditorFactory_obje  CEditorFactory_obje::smRegistrar;
//---------------------------------------------------------------------------
extern PACKAGE TfrmOBJE *frmOBJE;
//---------------------------------------------------------------------------
#endif
