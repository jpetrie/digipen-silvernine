//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "ApathyMain.h"
#include "ApathyNewTag.h"
#include "ApathyNewPackage.h"
#include "ApathyTagProps.h"

#include "CTagMgrS.h"

#include "CEditor.h"
#include "CEditorFactory.h"


#include "CEditor_sprc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
: TForm(Owner)
{
  CTagMgr->PatchPath("../../data/patch");
  CTagMgr->PackagePath("../../data/pack");
  cmbBrowsePath->Text = CTagMgr->PatchPath().c_str();

  UpdateTreeView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::UpdateTreeView(void)
{
std::string   tPath;
nsl::stringlist  tTypes;
TTreeNode    *tSibNode = 0;
CTag::ID      tTagID;

  // Get the browse path.
  treeTagList->Items->Clear();
  tPath = cmbBrowsePath->Text.c_str();

  // Get all the folders in that directory.
  nsl::fdenum_directories(tPath,tTypes);
  for(unsigned int i = 0; i < tTypes.size(); ++i)
  {
    // Populate the treeview; insert only valid kinds.
    tTagID = CTagMgr->GetIDFromKind(tTypes[i]);
    if(tTagID != kTag_Unknown)
    {
    nsl::stringlist  tFiles;

      tSibNode = treeTagList->Items->Add(tSibNode,tTypes[i].c_str());

      // Populate the node with children that are the actual tag files.
      nsl::stpslash(tPath);
      nsl::fdenum_files(tPath + tTypes[i],tFiles);
      for(unsigned int j = 0; j < tFiles.size(); ++j)
        treeTagList->Items->AddChild(tSibNode,tFiles[j].c_str());
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::GetTagList(CTag::ID id,nsl::stringlist &list)
{
std::string  tDirectory;

  // Now get all the tags in the appropriate folder.
  tDirectory = nsl::stformat("%s/%s",CTagMgr->PatchPath().c_str(),CTagMgr->GetKindFromID(id).c_str());
  nsl::fdenum_files(tDirectory,list);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Exit1Click(TObject *Sender)
{
  // Quit.
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnBrowseClick(TObject *Sender)
{
  UpdateTreeView();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::treeTagListDblClick(TObject *Sender)
{
  if(treeTagList->Selected->Parent != 0)
  {
  CTag::ID  tID;

    // Recover the typecode of the parent.
    tID = CTagMgr->GetIDFromKind(treeTagList->Selected->Parent->Text.c_str());
    if(tID != kTag_Unknown)
    {
    CEditor *tEditor = CEditorFactory::Launch(tID,treeTagList->Selected->Text.c_str());

      mEditors.push_back(tEditor);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Properties1Click(TObject *Sender)
{
  if(treeTagList->Selected->Parent != 0)
  {
  CTag::ID  tID;

    // Recover the typecode of the parent.
    tID = CTagMgr->GetIDFromKind(treeTagList->Selected->Parent->Text.c_str());
    if(tID != kTag_Unknown)
    {
    CTag        *tTag;
    std::string  tName = treeTagList->Selected->Text.c_str();

      // Read the tag.
      tTag = CTagMgr->Unarchive(tID,tName);
      frmTagProps->edtTagName->Text = tTag->Name().c_str();
      frmTagProps->edtTagDesc->Text = tTag->Desc().c_str();
      frmTagProps->txtFileSize->Caption = "0 bytes";
      frmTagProps->ShowModal();

      if(frmTagProps->ModalResult == mrOk)
      {
      std::string  tOldFile = nsl::stformat("%s/%s/%s",CTagMgr->PatchPath().c_str(),
                                                  CTagMgr->GetKindFromID(tID).c_str(),
                                                  tTag->Name().c_str());
        //TODO: Use file manager call to unlink.
        DeleteFile(tOldFile.c_str());
        tTag->Name(frmTagProps->edtTagName->Text.c_str());
        tTag->Desc(frmTagProps->edtTagDesc->Text.c_str());
        CTagMgr->Archive(tID,tTag);
        UpdateTreeView();
      }

      delete tTag;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::NewTag1Click(TObject *Sender)
{
  frmNewTag->edtTagType->Text = "type";
  frmNewTag->edtTagName->Text = "name";
  frmNewTag->edtTagDesc->Text = "description";
  frmNewTag->ShowModal();
  if(frmNewTag->ModalResult == mrOk)
  {
  CTag::ID  tID = CTagMgr->GetIDFromType(frmNewTag->edtTagType->Text.c_str());

    // If the ID is valid, create a new tag and archive it immediately.
    if(tID != kTag_Unknown)
    {
    CTag *tTag = CTagMgr->Create(tID);

      tTag->Name(frmNewTag->edtTagName->Text.c_str());
      tTag->Desc(frmNewTag->edtTagDesc->Text.c_str());
      CTagMgr->Archive(tID,tTag);
      CTagMgr->Release(tTag);

      // Instead of forcing a complete re-read of the directory,
      // we should instead just add the new tag where it needs to be.
      UpdateTreeView();
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Delete1Click(TObject *Sender)
{
  if(treeTagList->Selected->Parent != 0)
  {
  CTag::ID  tID;

    // Recover the typecode of the parent.
    tID = CTagMgr->GetIDFromKind(treeTagList->Selected->Parent->Text.c_str());
    if(tID != kTag_Unknown)
    {
    CTag        *tTag;
    std::string  tPath = nsl::stformat("%s/%s/%s",CTagMgr->PatchPath().c_str(),
                                             CTagMgr->GetKindFromID(tID).c_str(),
                                             treeTagList->Selected->Text.c_str());

        DeleteFile(tPath.c_str());//CFileMgr->RemoveFile(tPath);
        UpdateTreeView();
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::CompilePackage1Click(TObject *Sender)
{
  frmNewPackage->edtPackName->Text = "";
  frmNewPackage->ShowModal();
 // if(frmNewPackage->ModalResult == mrOk)
  //  CTagFactory::BuildPackageTag(frmNewPackage->edtPackName->Text.c_str());
}
//---------------------------------------------------------------------------

