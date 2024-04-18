//---------------------------------------------------------------------------

#ifndef CEditor_sprcSCTH
#define CEditor_sprcSCTH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "CEditor.h"
//---------------------------------------------------------------------------
class TfrmSPRCCollectionTitle : public CEditor
{
__published:	// IDE-managed Components
    TButton *btnSPRCCollectionOK;
    TButton *btnSPRCCollectionCancel;
    TEdit *editSPRCSpriteCollectionTitle;
    TLabel *txtSPRCCollectionTitle;
    void __fastcall btnSPRCCollectionCancelClick(TObject *Sender);
    void __fastcall btnSPRCCollectionOKClick(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall editSPRCSpriteCollectionTitleKeyDown(TObject *Sender,
          WORD &Key, TShiftState Shift);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmSPRCCollectionTitle(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSPRCCollectionTitle *frmSPRCCollectionTitle;
//---------------------------------------------------------------------------
#endif
