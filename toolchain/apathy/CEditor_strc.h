//---------------------------------------------------------------------------

#ifndef CEditor_strcH
#define CEditor_strcH

#include "CEditor.h"
#include "CEditorFactory.h"
#include "CTag_strc.h"

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmSTRC : public CEditor
{
__published:	// IDE-managed Components
        TMemo *txtStrings;
        TButton *btnSave;
        TButton *btnCancel;
        void __fastcall btnSaveClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
private:	// User declarations

        CTag_strc *mTag;

public:		// User declarations
        __fastcall TfrmSTRC(TComponent* Owner,const std::string &fn);

        void PopulateControls(void);
        void PopulateTag(void);
};
//---------------------------------------------------------------------------
class CEditorFactory_strc : public CEditorFactory
{
public:
  CEditorFactory_strc(void) : CEditorFactory(kTag_strc) { }


protected:
  CEditor* DoLaunch(const std::string &fn) { return new TfrmSTRC(0,fn); }

  private:
    static CEditorFactory_strc  smRegistrar;
};
CEditorFactory_strc  CEditorFactory_strc::smRegistrar;
//---------------------------------------------------------------------------
extern PACKAGE TfrmSTRC *frmSTRC;
//---------------------------------------------------------------------------
#endif
