//---------------------------------------------------------------------------

#ifndef CEditor_projH
#define CEditor_projH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <string>

#include "ApathyMain.h"

#include "CTagFactory.h"
#include "CTag_proj.h"
#include "CTag_sprc.h"
#include "CTag_obje.h"

#include "CEditorFactory.h"

const char* kDamageType[DAMAGE_TYPES] = {   "Kinetic", 
                                            "Explosive", 
                                            "Burn", 
                                            "Electrical", 
                                            "Sync"  };
//---------------------------------------------------------------------------
class TfrmPROJ : public CEditor
{
__published:	// IDE-managed Components
    TComboBox *cmbPROJobje_tag;
    TComboBox *cmbPROJsprc_tag;
    TGroupBox *grpPROJSequences;
    TGroupBox *grpPROJDamageAttributes;
    TGroupBox *grpPROJFlags;
    TEdit *editPROJInFlightSeqIdx;
    TEdit *editPROJAtRestSeqIdx;
    TEdit *editPROJDetonationSeqIdx;
    TLabel *lblPROJInFlightSeqIdx;
    TLabel *lblPROJAtRestSeqIdx;
    TLabel *lblPROJDetonationSeqIdx;
    TCheckBox *chkPROJPromotes;
    TCheckBox *chkPROJDetonateCollision;
    TCheckBox *chkPROJDetonateRest;
    TCheckBox *chkPROJDetonateExplosives;
    TCheckBox *chkPROJIgnoreShielding;
    TCheckBox *chkPROJIgnoreOwner;
    TEdit *editPROJDamageMin;
    TEdit *editPROJDamageMax;
    TEdit *editPROJDamageRadiusMin;
    TEdit *editPROJDamageRadiusMax;
    TEdit *editPROJDamageFillRate;
    TButton *btnPROJApply;
    TButton *btnPROJRevert;
    TButton *btnPROJCancel;
    TLabel *lblPROJDamage;
    TLabel *lblPROJDamageRadius;
    TLabel *lblPROJDamageRadiusFillRate;
    TLabel *lblPROJDamageType;
    TComboBox *cmbPROJDamageType;
    TStaticText *txtPROJDamageRange;
    TStaticText *txtPROJDamageRadius;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnPROJApplyClick(TObject *Sender);
    void __fastcall btnPROJCancelClick(TObject *Sender);
    void __fastcall btnPROJRevertClick(TObject *Sender);
private:	// User declarations
    CTag_proj *Tag;
    void __fastcall TfrmPROJ::PopulateControls(void);
public:		// User declarations
    __fastcall TfrmPROJ::TfrmPROJ(TComponent* Owner,const std::string &fn);
};

class CEditorFactory_proj : public CEditorFactory
{
public:
  CEditorFactory_proj(void) : CEditorFactory(kTag_proj) { }

protected:
  CEditor* DoLaunch(const std::string &fn) { return new TfrmPROJ(0,fn); }

  private:
    static CEditorFactory_proj  smRegistrar;
};
CEditorFactory_proj  CEditorFactory_proj::smRegistrar;
//---------------------------------------------------------------------------
extern PACKAGE TfrmPROJ *frmPROJ;
//---------------------------------------------------------------------------
#endif
