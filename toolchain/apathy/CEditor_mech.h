//---------------------------------------------------------------------------

#ifndef CEditor_mechH
#define CEditor_mechH

#include "CEditor.h"
#include "CEditorFactory.h"
#include "CTag_mech.h"

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmMECH : public CEditor
{
__published:	// IDE-managed Components
        TButton *btnSave;
        TButton *btnCancel;
        TGroupBox *SpeedMult;
        TEdit *edtGround;
        TEdit *edtPave;
        TEdit *edtShallow;
        TEdit *edtDeep;
        TEdit *edtBrush;
        TEdit *edtRocky;
        TEdit *edtGrndImpas;
        TEdit *edtAirImpas;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TGroupBox *Props;
        TEdit *edtObje;
        TEdit *edtImgc;
        TLabel *Label9;
        TLabel *Label10;
        TGroupBox *SequenceIndx;
        TLabel *Label11;
        TEdit *edtIdle;
        TLabel *Label12;
        TLabel *Label13;
        TEdit *edtWalk;
        TEdit *edtFire;
  TLabel *Label14;
  TEdit *edtBaseSpeed;
  TGroupBox *GroupBox1;
  TLabel *Label22;
  TListBox *lstMentAttacks;
  TBitBtn *btnAddMent;
  TBitBtn *btnDeleteMent;
  TEdit *edtVisionRange;
  TEdit *edtRadarRange;
  TLabel *Label15;
  TLabel *Label16;
  TComboBox *cmbMentName;
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall btnSaveClick(TObject *Sender);
  void __fastcall btnAddMentClick(TObject *Sender);
  void __fastcall cmbMentNameChange(TObject *Sender);
  void __fastcall btnDeleteMentClick(TObject *Sender);
  void __fastcall lstMentAttacksClick(TObject *Sender);
private:
  CTag_mech *mTag;

  void __fastcall PopulateControls(void);
  void __fastcall PopulateTag(void);

public:		// User declarations
        __fastcall TfrmMECH(TComponent* Owner,const std::string &fn);
};
//---------------------------------------------------------------------------
class CEditorFactory_mech : public CEditorFactory
{
public:
  CEditorFactory_mech(void) : CEditorFactory(kTag_mech) { }


protected:
  CEditor* DoLaunch(const std::string &fn) { return new TfrmMECH(0,fn); }

  private:
    static CEditorFactory_mech  smRegistrar;
};
CEditorFactory_mech  CEditorFactory_mech::smRegistrar;
//---------------------------------------------------------------------------
extern PACKAGE TfrmMECH *frmMECH;
//---------------------------------------------------------------------------
#endif
