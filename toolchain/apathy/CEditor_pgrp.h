//---------------------------------------------------------------------------

#ifndef CEditor_pgrpH
#define CEditor_pgrpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "CTagFactory.h"
#include "CTag_pgrp.h"
#include "CEditor.h"
#include "CTag_sprc.h"
#include "CTag_obje.h"

#include "CEditorFactory.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmPGRP : public CEditor
{
__published:	// IDE-managed Components
    TListBox *lstPGRPAvailableTags;
    TListBox *lstPGRPTagList;
    TGroupBox *grpPGRPGroupType;
    TCheckBox *chkPGRPFan;
    TCheckBox *chkPGRPRandom;
    TCheckBox *chkPGRPSeek;
    TEdit *editPGRPAngle;
    TLabel *lblPGRPSpread;
    TBitBtn *btnPGRPAddProj;
    TBitBtn *btnPGRPRemoveProj;
    TStatusBar *stsPGRPStatus;
    TButton *btnPGRPApply;
    TButton *btnPGRPRevert;
    TButton *btnPGRPCancel;
    void __fastcall btnPGRPAddProjClick(TObject *Sender);
    void __fastcall btnPGRPRemoveProjClick(TObject *Sender);
    void __fastcall chkPGRPFanClick(TObject *Sender);
    void __fastcall chkPGRPRandomClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnPGRPApplyClick(TObject *Sender);
    void __fastcall btnPGRPRevertClick(TObject *Sender);
    void __fastcall btnPGRPCancelClick(TObject *Sender);
private:	// User declarations
    CTag_pgrp *Tag;
    void __fastcall PopulateControls(void);
public:		// User declarations
     __fastcall TfrmPGRP(TComponent* Owner, const std::string &fn);
};

class CEditorFactory_pgrp : public CEditorFactory
{
public:
  CEditorFactory_pgrp(void) : CEditorFactory(kTag_pgrp) { }

protected:
  CEditor* DoLaunch(const std::string &fn) { return new TfrmPGRP(0,fn); }

  private:
    static CEditorFactory_pgrp smRegistrar;
};
//---------------------------------------------------------------------------
CEditorFactory_pgrp  CEditorFactory_pgrp::smRegistrar;
//---------------------------------------------------------------------------
extern PACKAGE TfrmPGRP *frmPGRP;
//---------------------------------------------------------------------------
#endif

