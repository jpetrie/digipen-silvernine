//---------------------------------------------------------------------------

#ifndef ApathyTagPropsH
#define ApathyTagPropsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmTagProps : public TForm
{
__published:	// IDE-managed Components
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  TEdit *edtTagName;
  TEdit *edtTagDesc;
  TStaticText *txtFileSize;
  TButton *btnSave;
  TButton *btnCancel;
  void __fastcall btnSaveClick(TObject *Sender);
  void __fastcall btnCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TfrmTagProps(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmTagProps *frmTagProps;
//---------------------------------------------------------------------------
#endif
