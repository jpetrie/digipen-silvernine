//---------------------------------------------------------------------------

#ifndef CEditor_sprcH
#define CEditor_sprcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <vector>


#include "CEditor.h"
#include "CTag_sprc.h"
#include "BMops.h"
#include "CEditorFactory.h"

using std::vector;

// extract individual color components from a Borland color
#define EXTRACT_R(c)    ((c & 0x000000FF)>>0)   ///> extract the red component
#define EXTRACT_G(c)    ((c & 0x0000FF00)>>8)   ///> extract the red component
#define EXTRACT_B(c)    ((c & 0x00FF0000)>>16)  ///> extract the red component

struct ImageList
{
    CTag_sprc::DataMembers Header;
    vector < unsigned char* > images;
};
//---------------------------------------------------------------------------
class TfrmSPRC : public CEditor
{
__published:	// IDE-managed Components
    TLabel *txtSPRCSequences;
    TListBox *lstSPRCSequences;
    TButton *btnSPRCNewSequence;
    TButton *btnSPRCRemoveSequence;
    TLabel *txtSPRCImages;
    TListBox *lstSPRCSequenceImages;
    TButton *btnSPRCNewSequenceImage;
    TButton *btnSPRCRemoveSequenceImage;
    TEdit *editSPRCFacings;
    TEdit *editSPRCFrameWidth;
    TEdit *editSPRCFrameHeight;
    TUpDown *spnSPRCFacings;
    TUpDown *spnSPRCWidth;
    TUpDown *spnSPRCHeight;
    TLabel *txtSPRCFrames;
    TLabel *txtSPRCFacings;
    TLabel *txtSPRCWidth;
    TLabel *txtSPRCHeight;
    TPanel *pnlSPRCImagePreview;
    TButton *btnSPRCApply;
    TButton *btnSPRCCancel;
    TLabel *txtSPRCSequenceCount;
    TOpenDialog *OpenDialogSPRCBitmaps;
    TButton *btnSPRCRevert;
    TBevel *Bevel1;
    TColorDialog *dlgAlphaPicker;
    TImage *imgSPRCAlphaPicker;
    TStaticText *txtSPRCAlphaRed;
    TStaticText *txtSPRCAlphaGreen;
    TStaticText *txtSPRCAlphaBlue;
    TStaticText *txtSPRCAlphaValueRed;
    TStaticText *txtSPRCAlphaValueGreen;
    TStaticText *txtSPRCAlphaValueBlue;
    TLabel *lblSPRCAlphaIgnore;
    TCheckBox *chkSPRCBlend;
    TLabel *lblSPRCBlend;
    TTrackBar *trkSPRCBlend;
    void __fastcall btnSPRCCancelClick(TObject *Sender);
    void __fastcall btnSPRCNewSequenceClick(TObject *Sender);
    void __fastcall btnSPRCRemoveSequenceClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnSPRCNewSequenceImageClick(TObject *Sender);
    void __fastcall btnSPRCApplyClick(TObject *Sender);
    void __fastcall dlgAlphaPickerClose(TObject *Sender);
    void __fastcall imgSPRCAlphaPickerDblClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall editSPRCFacingsChange(TObject *Sender);
    void __fastcall editSPRCFrameHeightChange(TObject *Sender);
    void __fastcall editSPRCFrameWidthChange(TObject *Sender);
    void __fastcall lstSPRCSequencesClick(TObject *Sender);
    void __fastcall btnSPRCNewSequenceMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall lstSPRCSequenceImagesClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall btnSPRCRevertClick(TObject *Sender);
    void __fastcall chkSPRCBlendClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall btnSPRCRemoveSequenceImageClick(TObject *Sender);
    

private:	// User declarations
    int m_Sequences;
    BYTE *atPointer;
    CTag_sprc *Tag;
    vector < ImageList > Sequences;
    vector < CTexture > Textures;
    CTexture CurrTexture;
        
    // OpenGL data members
    HDC    mDC;        // Device context.
    HGLRC  mRC;        // Render context.
    int    mPF;        // Pixel format.
    int    mContextW;  // Render area width.
    int    mContextH;  // Render area height.

    bool LoadBitmapFile(const char *Filename);
    bool ExtractFromTag(void);
    int Scale(int old_w, int old_h, int new_w, int new_h, 
                    unsigned char *bits);
    void MaintainSequenceImages(void);

public:		// User declarations
    __fastcall TfrmSPRC(TComponent* Owner,const std::string &fn);
    void __fastcall IdleLoop(TObject*, bool& done);
};
//---------------------------------------------------------------------------
class CEditorFactory_sprc : public CEditorFactory
{
public:
  CEditorFactory_sprc(void) : CEditorFactory(kTag_sprc) { }

protected:
  CEditor* DoLaunch(const std::string &fn) { return new TfrmSPRC(0,fn); }

  private:
    static CEditorFactory_sprc  smRegistrar;
};
CEditorFactory_sprc  CEditorFactory_sprc::smRegistrar;
//---------------------------------------------------------------------------
extern PACKAGE TfrmSPRC *frmSPRC;
//---------------------------------------------------------------------------
#endif
