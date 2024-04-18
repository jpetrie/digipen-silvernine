//---------------------------------------------------------------------------

#ifndef CEditor_tmapResizeH
#define CEditor_tmapResizeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmTMAP_Resize : public TForm
{
__published:	// IDE-managed Components
  TButton *btnCancel;
  TButton *btnResize;
  TEdit *edtWidth;
  TEdit *edtHeight;
  TRadioButton *radPreserve;
  TRadioButton *radNukeAndPave;
  TGroupBox *GroupBox1;
  TLabel *Label1;
  TLabel *Label2;
  void __fastcall btnCancelClick(TObject *Sender);
  void __fastcall btnResizeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TfrmTMAP_Resize(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmTMAP_Resize *frmTMAP_Resize;
//---------------------------------------------------------------------------
#endif
