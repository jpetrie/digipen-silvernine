//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include "CEditor_pgrp.h"
#include "CTagMgrS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPGRP *frmPGRP;
//---------------------------------------------------------------------------
__fastcall TfrmPGRP::TfrmPGRP(TComponent* Owner, const std::string &fn)
        :CEditor(Owner,kTag_pgrp)
{
    Tag = (CTag_pgrp*)CTagMgr->Unarchive(kTag_pgrp,fn);

    Caption = nsl::stformat("pgrp %s (%s)",Tag->Name().c_str(),Tag->Desc().c_str()).c_str();

    std::string path = CTagMgr->PatchPath() + "/projectiles";

    nsl::stringlist  tFiles;

    // Populate the node with children that are the actual tag files.
    nsl::stpslash(path);
    nsl::fdenum_files(path, tFiles);
    for(unsigned int j = 0; j < tFiles.size(); ++j)
        lstPGRPAvailableTags->AddItem(tFiles[j].c_str(), 0);

}
//---------------------------------------------------------------------------
void __fastcall TfrmPGRP::btnPGRPAddProjClick(TObject *Sender)
{
    // verify that there are files in the list
    if(lstPGRPAvailableTags->Count == 0)
        return;
    int index = lstPGRPAvailableTags->ItemIndex;
    // make sure that an item is selected
    if(index == -1)
    {
        lstPGRPAvailableTags->ItemIndex = 0;
        index = 0;
    }
    lstPGRPTagList->AddItem(lstPGRPAvailableTags->Items->Strings[index], 0);
    PopulateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPGRP::btnPGRPRemoveProjClick(TObject *Sender)
{
    // verify that there are files in the list
    if(lstPGRPTagList->Count == 0)
        return;
    int index = lstPGRPTagList->ItemIndex;
    // make sure that an item is selected
    if(index == -1)
    {
        lstPGRPTagList->ItemIndex = 0;
        index = 0;
    }
    lstPGRPTagList->DeleteSelected();
    PopulateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPGRP::PopulateControls(void)
{
    char buf[100];
    if(lstPGRPTagList->Count == 0)
    {
        sprintf(buf, "Count: 0");
        return;
    }
    if(chkPGRPFan->Checked)
    {
        sprintf(buf, "Count: %d\tAngle of Separation: %f", lstPGRPTagList->Count, editPGRPAngle->Text.ToDouble()/(double)lstPGRPTagList->Count);
    }
    else
    {
        sprintf(buf, "Count: %d", lstPGRPTagList->Count);
    }

    stsPGRPStatus->SimpleText = buf;


}
void __fastcall TfrmPGRP::chkPGRPFanClick(TObject *Sender)
{
    if(chkPGRPFan->Checked == true)
    {
        chkPGRPRandom->Checked = false;
        editPGRPAngle->Enabled = true;
    }
    else
    {
        editPGRPAngle->Enabled = false;
    }
    PopulateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPGRP::chkPGRPRandomClick(TObject *Sender)
{
    if(chkPGRPRandom->Checked == true)
    {
        chkPGRPFan->Checked = false;
        editPGRPAngle->Enabled = false;
    }
    PopulateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPGRP::FormCreate(TObject *Sender)
{
    for(unsigned int i = 0; i < Tag->mTags.size(); ++i)
    {
        lstPGRPTagList->AddItem(Tag->mTags[i].c_str(), 0);
    }
    chkPGRPFan->Checked = Tag->mType & kProjectileGroupType_Fan;
    chkPGRPRandom->Checked = Tag->mType & kProjectileGroupType_Random;
    chkPGRPSeek->Checked = Tag->mType & kProjectileGroupType_Seek;
    char buf[50];
    sprintf(buf, "%f", Tag->mSpread);
    editPGRPAngle->Text = buf;
    PopulateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPGRP::btnPGRPApplyClick(TObject *Sender)
{
    Tag->mType = 0;
    if(chkPGRPFan->Checked == true)
        Tag->mType += kProjectileGroupType_Fan;
    if(chkPGRPRandom->Checked == true)
        Tag->mType += kProjectileGroupType_Random;
    if(chkPGRPSeek->Checked == true)
        Tag->mType += kProjectileGroupType_Seek;

    Tag->mSpread = editPGRPAngle->Text.ToDouble();
    Tag->mCount = lstPGRPTagList->Count;
    Tag->mTags.clear();
    for(unsigned int i = 0; i < Tag->mCount; ++i)
    {
        Tag->mTags.push_back(lstPGRPTagList->Items->Strings[i].c_str());
    }
    CTagMgr->Archive(Tag->Ident(), Tag);
    Release();

}
//---------------------------------------------------------------------------
void __fastcall TfrmPGRP::btnPGRPRevertClick(TObject *Sender)
{
    lstPGRPTagList->Clear();
    for(unsigned int i = 0; i < Tag->mTags.size(); ++i)
    {
        lstPGRPTagList->AddItem(Tag->mTags[i].c_str(), 0);
    }
    chkPGRPFan->Checked = Tag->mType & kProjectileGroupType_Fan;
    chkPGRPRandom->Checked = Tag->mType & kProjectileGroupType_Random;
    chkPGRPSeek->Checked = Tag->mType & kProjectileGroupType_Seek;
    char buf[50];
    sprintf(buf, "%f", Tag->mSpread);
    editPGRPAngle->Text = buf;
    PopulateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPGRP::btnPGRPCancelClick(TObject *Sender)
{
    Release();    
}
//---------------------------------------------------------------------------

