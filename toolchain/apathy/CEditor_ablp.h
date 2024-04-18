/*!
    @file   CEditor_ablp.h
    @author Scott Smith
    @date   October 15, 2003

    @brief  Implements the actions of the Mental Ability editor
______________________________________________________________________________*/

//---------------------------------------------------------------------------

#ifndef CEditor_ablpH
#define CEditor_ablpH
/*------------------------------------------------------------------------------
Local Includes
------------------------------------------------------------------------------*/
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>

/*!
    @class  TfrmABLM

    @brief  Defines an editor for mental abilities
______________________________________________________________________________*/
class TfrmABLP : public TForm
{
__published:	// IDE-managed Components
        TComboBox *comboABLPident;
        TComboBox *comboABLPProjCreate;
        TLabel *txtABLPSprites;
        TLabel *txtABLPProjGroupCreate;
        TLabel *txtABLPAbilityCost;
        TEdit *editABLPAbilityCost;
        TUpDown *spnABLPAbilityCost;
        TLabel *txtABLPIconID;
        TEdit *editABLPIconID;
        TUpDown *spnABLPIconID;
        TLabel *txtABLPAmmunition;
        TEdit *editABLPAmmunition;
        TUpDown *spnABLPAmmunition;
        TComboBox *comboABLPProjUse;
        TLabel *txtABLPProjGroupUse;
        TButton *btnABLPApply;
        TButton *btnABLPCancel;
        void __fastcall btnABLPCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmABLP(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmABLP *frmABLP;
//---------------------------------------------------------------------------
#endif
