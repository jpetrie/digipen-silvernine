//---------------------------------------------------------------------------

#ifndef CEditor_unitH
#define CEditor_unitH

#include "ApathyMain.h"

#include "CTagFactory.h"

#include "CTag_mech.h"
#include "CTag_strc.h"
//#include "CTag_scri.h"
#include "CTag_unit.h"

#include "CEditorFactory.h"


//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmUNIT : public CEditor
{
__published:	// IDE-managed Components
  TButton *btnSave;
  TButton *btnCancel;
  TLabel *Label2;
  TComboBox *cmbMechTag;
  TLabel *Label3;
  TComboBox *cmbCharTag;
  TLabel *Label4;
  TComboBox *cmbScriTag;
        TComboBox *cmbNames;
        TLabel *Label1;
        TComboBox *cmbFlavor;
        TLabel *Label5;
  void __fastcall btnSaveClick(TObject *Sender);
  void __fastcall btnCancelClick(TObject *Sender);
private:	// User declarations

    CTag_unit *mTag;  // The tag.

    
public:
  void __fastcall PopulateControls(void);
  void __fastcall PopulateTag(void);

  __fastcall TfrmUNIT(TComponent* Owner,const std::string &fn);
};
//---------------------------------------------------------------------------
class CEditorFactory_unit : public CEditorFactory
{
public:
  CEditorFactory_unit(void) : CEditorFactory(kTag_unit) { }

protected:
  CEditor* DoLaunch(const std::string &fn) { return new TfrmUNIT(0,fn); }

  private:
    static CEditorFactory_unit  smRegistrar;
};
CEditorFactory_unit  CEditorFactory_unit::smRegistrar;
//---------------------------------------------------------------------------
extern PACKAGE TfrmUNIT *frmUNIT;
//---------------------------------------------------------------------------
#endif
