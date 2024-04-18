//---------------------------------------------------------------------------

#ifndef ApathyNewPackageH
#define ApathyNewPackageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmNewPackage : public TForm
{
__published:	// IDE-managed Components
  TEdit *edtPackName;
  TLabel *Label1;
  TGroupBox *GroupBox1;
  TCheckBox *CheckBox1;
  TCheckBox *CheckBox2;
  TCheckBox *CheckBox3;
  TCheckBox *CheckBox4;
  TCheckBox *CheckBox5;
  TCheckBox *CheckBox6;
  TCheckBox *CheckBox7;
  TCheckBox *CheckBox8;
  TCheckBox *CheckBox11;
  TCheckBox *CheckBox12;
  TCheckBox *CheckBox13;
  TCheckBox *CheckBox15;
  TCheckBox *CheckBox10;
  TCheckBox *CheckBox16;
  TCheckBox *CheckBox17;
  TCheckBox *CheckBox18;
  TCheckBox *CheckBox19;
  TCheckBox *CheckBox20;
  TCheckBox *CheckBox21;
  TCheckBox *CheckBox22;
  TButton *btnCompile;
  TButton *btnCancel;
  void __fastcall btnCompileClick(TObject *Sender);
  void __fastcall btnCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TfrmNewPackage(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmNewPackage *frmNewPackage;
//---------------------------------------------------------------------------
#endif
