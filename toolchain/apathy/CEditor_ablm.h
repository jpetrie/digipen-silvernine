/*!
    @file   CEditor_ablm.h
    @author Scott Smith
    @date   October 15, 2003

    @brief  Implements the actions of the Mental Ability editor
______________________________________________________________________________*/


//---------------------------------------------------------------------------
#ifndef CEditor_ablmH
#define CEditor_ablmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "CEditor.h"
#include "CEditorFactory.h"

#include "CTag.h"
#include "CTagFactory.h"
#include "CTag_ablm.h"
//---------------------------------------------------------------------------
class TfrmABLM : public CEditor
{
__published:	// IDE-managed Components
  TLabel *Label1;
  TComboBox *cmbCollection;
  TGroupBox *GroupBox1;
  TButton *btnSave;
  TButton *btnCancel;
  TEdit *Edit1;
  TLabel *Label2;
  TGroupBox *GroupBox2;
  TLabel *Label3;
  TComboBox *cmbUseGroup;
  TLabel *Label4;
  TComboBox *cmbProjGroup;
  TGroupBox *GroupBox3;
  TLabel *Label5;
  TEdit *edtBuyCost;
  TLabel *Label6;
  TEdit *edtSyncCost;
  TLabel *Label7;
  TEdit *edtMinDist;
  TLabel *Label8;
  TEdit *edtMaxDist;
  TLabel *Label9;
  TEdit *edtDelay;
  void __fastcall btnCancelClick(TObject *Sender);
  void __fastcall btnSaveClick(TObject *Sender);
private:
  CTag_ablm *mTag;
public:
  __fastcall TfrmABLM(TComponent* Owner,const std::string &fn);

  __fastcall void PopulateControls(void);
  __fastcall void PopulateTag(void);
};
//---------------------------------------------------------------------------
class CEditorFactory_ablm : public CEditorFactory
{
public:
  CEditorFactory_ablm(void) : CEditorFactory(kTag_ablm) { }


protected:
  CEditor* DoLaunch(const std::string &fn) { return new TfrmABLM(0,fn); }

  private:
    static CEditorFactory_ablm  smRegistrar;
};
CEditorFactory_ablm  CEditorFactory_ablm::smRegistrar;
//---------------------------------------------------------------------------
extern PACKAGE TfrmABLM *frmABLM;
//---------------------------------------------------------------------------
#endif
