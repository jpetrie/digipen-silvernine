//---------------------------------------------------------------------------
#ifndef ApathyMainH
#define ApathyMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#include "precompiled.h"

#include "CEditor.h"
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
  TTreeView *treeTagList;
  TMainMenu *mnuApathy;
  TMenuItem *File1;
  TMenuItem *Help1;
  TMenuItem *Exit1;
  TMenuItem *About1;
  TMenuItem *Tag1;
  TMenuItem *Properties1;
  TMenuItem *N1;
  TMenuItem *CompilePackage1;
  TMenuItem *NewTag1;
  TMenuItem *N2;
  TComboBox *cmbBrowsePath;
  TButton *btnBrowse;
  TMenuItem *Delete1;
  TPopupMenu *popTagList;
  TMenuItem *Delete2;
  TMenuItem *Properties2;

  void __fastcall Exit1Click(TObject *Sender);
  void __fastcall btnBrowseClick(TObject *Sender);
  void __fastcall treeTagListDblClick(TObject *Sender);
  void __fastcall Properties1Click(TObject *Sender);
  void __fastcall NewTag1Click(TObject *Sender);
  void __fastcall Delete1Click(TObject *Sender);
  void __fastcall CompilePackage1Click(TObject *Sender);
private:
  std::vector< CEditor* >  mEditors;

public:
  __fastcall TfrmMain(TComponent* Owner);

  void __fastcall UpdateTreeView(void);
  void __fastcall GetTagList(CTag::ID id,nsl::stringlist &list);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
