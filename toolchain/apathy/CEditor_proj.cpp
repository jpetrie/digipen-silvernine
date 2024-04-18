//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CTagMgrS.h"
#include "CEditor_proj.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPROJ *frmPROJ;
//---------------------------------------------------------------------------
__fastcall TfrmPROJ::TfrmPROJ(TComponent* Owner,const std::string &fn)
    : CEditor(Owner,kTag_proj)
{
    Tag = (CTag_proj*)CTagMgr->Unarchive(kTag_proj,fn);

    Caption = nsl::stformat("proj %s (%s)",Tag->Name().c_str(),Tag->Desc().c_str()).c_str();
    PopulateControls();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPROJ::FormCreate(TObject *Sender)
{
    for(int i = 0; i < DAMAGE_TYPES; ++i)
        cmbPROJDamageType->AddItem(kDamageType[i], NULL);
    // Select first type
    //cmbPROJDamageType->ItemIndex = 0;

    nsl::stringlist tTags;

    // Fill combo boxes.
    frmMain->GetTagList(kTag_obje,tTags);
    for(unsigned int i = 0; i < tTags.size(); ++i)
        cmbPROJobje_tag->Items->Add(tTags[i].c_str());
    frmMain->GetTagList(kTag_sprc,tTags);
    for(unsigned int i = 0; i < tTags.size(); ++i)
        cmbPROJsprc_tag->Items->Add(tTags[i].c_str());
}
//---------------------------------------------------------------------------

void __fastcall TfrmPROJ::btnPROJApplyClick(TObject *Sender)
{
    std::string name = Tag->Name();
    std::string desc = Tag->Desc();
    
    delete Tag;
    Tag = new CTag_proj;
    Tag->Name(name);
    Tag->Desc(desc);
            
    int det_flag = 0;
    int dam_flag = 0;

    if(chkPROJDetonateCollision->Checked == true)
        det_flag += kDetonatesOnCollision;
    if(chkPROJDetonateRest->Checked == true)
        det_flag += kDetonatesAtRest;
    if(chkPROJPromotes->Checked == true)
        det_flag += kPromotesOnDetonation;
    if(chkPROJIgnoreOwner->Checked == true)
        dam_flag += kIgnoresOwner;
    if(chkPROJIgnoreShielding->Checked == true)
        dam_flag += kIgnoresShielding;
    if(chkPROJDetonateExplosives->Checked == true)
        dam_flag += kDetonatesExplosives;
    
    Tag->obje_tag = cmbPROJobje_tag->Text.c_str();
    Tag->sprc_tag = cmbPROJsprc_tag->Text.c_str();
    Tag->in_flight_seq_idx = (float)editPROJInFlightSeqIdx->Text.ToDouble();
    Tag->at_rest_seq_idx = (float)editPROJAtRestSeqIdx->Text.ToDouble();
    Tag->det_seq_idx = (float)editPROJDetonationSeqIdx->Text.ToDouble();
    Tag->det_flags = det_flag;
    Tag->dam_flags = dam_flag;

    for(int i = 0; i < DAMAGE_TYPES; ++i)
        if(cmbPROJDamageType->Text == kDamageType[i])
        {
            Tag->damage_type = i;
            break;
        }
            
    Tag->damage_min = editPROJDamageMin->Text.ToDouble();
    Tag->damage_max = editPROJDamageMax->Text.ToDouble();
    Tag->damage_radius_min = editPROJDamageRadiusMin->Text.ToDouble();
    Tag->damage_radius_max = editPROJDamageRadiusMax->Text.ToDouble();
    Tag->damage_radius_fill_rate = editPROJDamageFillRate->Text.ToDouble();
    
       
    CTagMgr->Archive(kTag_proj, Tag);
    Release();
    
}
//---------------------------------------------------------------------------
void __fastcall TfrmPROJ::PopulateControls(void)
{
    chkPROJDetonateCollision->Checked   = Tag->det_flags & kDetonatesOnCollision;
    chkPROJDetonateRest->Checked        = Tag->det_flags & kDetonatesAtRest;
    chkPROJPromotes->Checked            = Tag->det_flags & kPromotesOnDetonation;
    chkPROJIgnoreOwner->Checked         = Tag->dam_flags & kIgnoresOwner;
    chkPROJIgnoreShielding->Checked     = Tag->dam_flags & kIgnoresShielding;
    chkPROJDetonateExplosives->Checked  = Tag->dam_flags & kDetonatesExplosives;
    
    cmbPROJobje_tag->Text                       = Tag->obje_tag.c_str();
    cmbPROJsprc_tag->Text                       = Tag->sprc_tag.c_str();

    if( Tag->obje_tag.length() == 0)
        cmbPROJobje_tag->Text = "obje tag";
    if( Tag->sprc_tag.length() == 0)
        cmbPROJsprc_tag->Text = "sprc tag";
        
    editPROJInFlightSeqIdx->Text                = Tag->in_flight_seq_idx;
    editPROJAtRestSeqIdx->Text                  = Tag->at_rest_seq_idx;  
    editPROJDetonationSeqIdx->Text              = Tag->det_seq_idx;      
    cmbPROJDamageType->Text                     = kDamageType[Tag->damage_type];      
    editPROJDamageMin->Text                     = Tag->damage_min;       
    editPROJDamageMax->Text                     = Tag->damage_max;       
    editPROJDamageRadiusMin->Text               = Tag->damage_radius_min;
    editPROJDamageRadiusMax->Text               = Tag->damage_radius_max;
    editPROJDamageFillRate->Text                = Tag->damage_radius_fill_rate;    
}
void __fastcall TfrmPROJ::btnPROJCancelClick(TObject *Sender)
{
    Release();    
}
//---------------------------------------------------------------------------

void __fastcall TfrmPROJ::btnPROJRevertClick(TObject *Sender)
{
    PopulateControls();    
}
//---------------------------------------------------------------------------


