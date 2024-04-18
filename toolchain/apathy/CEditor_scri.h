//---------------------------------------------------------------------------

#ifndef CEditor_scriH
#define CEditor_scriH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include "CEditor.h"
#include "CEditorFactory.h"
#include "CTagFactory.h"
//#include "CTag_scri.h"
//---------------------------------------------------------------------------
class TfrmSCRI : public CEditor
{
__published:	// IDE-managed Components
  TMemo *edtScript;
  TButton *btnSave;
  TButton *btnCancel;
  void __fastcall btnSaveClick(TObject *Sender);
  void __fastcall btnCancelClick(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
private:
  //CTag_scri *mTag;

public:		// User declarations
  __fastcall TfrmSCRI(TComponent* Owner,const std::string &fn);

  void __fastcall PopulateControls(void);
  void __fastcall PopulateTag(void);
};
//---------------------------------------------------------------------------
class CEditorFactory_scri : public CEditorFactory
{
public:
  CEditorFactory_scri(void) : CEditorFactory('scri') { }

protected:
  CEditor* DoLaunch(const std::string &fn) { return new TfrmSCRI(0,fn); }

  private:
    static CEditorFactory_scri  smRegistrar;
};
CEditorFactory_scri  CEditorFactory_scri::smRegistrar;
//---------------------------------------------------------------------------
extern PACKAGE TfrmSCRI *frmSCRI;
//---------------------------------------------------------------------------
#endif
