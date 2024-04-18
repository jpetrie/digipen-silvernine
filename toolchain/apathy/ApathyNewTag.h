//---------------------------------------------------------------------------

#ifndef ApathyNewTagH
#define ApathyNewTagH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmNewTag : public TForm
{
__published:	// IDE-managed Components
  TEdit *edtTagType;
  TEdit *edtTagDesc;
  TLabel *Label2;
  TLabel *Label1;
  TEdit *edtTagName;
  TLabel *Label3;
  TButton *btnCreate;
  TButton *btnCancel;
  void __fastcall btnCreateClick(TObject *Sender);
  void __fastcall btnCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TfrmNewTag(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmNewTag *frmNewTag;
//---------------------------------------------------------------------------
#endif
