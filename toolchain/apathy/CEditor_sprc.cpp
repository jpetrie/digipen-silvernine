//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <windef.h>
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#pragma hdrstop
#include "CTagMgrS.h"
#include "CEditor_sprc.h"
#include "CEditor_sprcSCT.h"
#include "CTagFactory_sprc.h"
#include "CTagFactory.h"

#define COLOR_DEPTH 3

static unsigned long CRGB(BYTE r, BYTE g, BYTE b)
{
    return (DWORD)((((DWORD)(r)<<24) | ((DWORD)(g)<<16)) | ((DWORD)(b)<<8));
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSPRC *frmSPRC;
//---------------------------------------------------------------------------
__fastcall TfrmSPRC::TfrmSPRC(TComponent* Owner,const std::string &fn)
: CEditor(Owner,kTag_sprc)
{
  CurrTexture = 0;
  Sequences.clear();
  // Load the tag.
  Tag = (CTag_sprc*)CTagMgr->Unarchive(kTag_sprc,fn);
  
  if(ExtractFromTag())
  {
    MaintainSequenceImages();
    Textures = Tag->TextureCollection;
  }
  m_Sequences = Tag->SequenceCount;
  
  // Set the name.
  Caption = nsl::stformat("sprc %s (%s)",Tag->Name().c_str(),Tag->Desc().c_str()).c_str();

  imgSPRCAlphaPicker->Canvas->Brush->Color = dlgAlphaPicker->Color;   
  imgSPRCAlphaPicker->Canvas->Rectangle(0,0,44,44);

  
  Application->OnIdle = IdleLoop;
  
  Show();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSPRC::btnSPRCCancelClick(TObject *Sender)
{
    Release();
    //delete this;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSPRC::btnSPRCNewSequenceClick(TObject *Sender)
{
    frmSPRCCollectionTitle->ShowModal();
    if(frmSPRCCollectionTitle->editSPRCSpriteCollectionTitle->Text.Length() == 0)
        return;
    //m_Sequences++;
    //char buf[10];
    AnsiString Item = frmSPRCCollectionTitle->editSPRCSpriteCollectionTitle->Text;
    // update count text object
    
    lstSPRCSequences->AddItem(Item, NULL);
    m_Sequences = Sequences.size();
    // add a new sequence to the collection
    ImageList il;
    il.Header.facings = 0;
    il.Header.frames_per_facing = 0;
    il.Header.frameWidth = 0;
    il.Header.frameHeight = 0;
    Sequences.push_back(il);
    
    char buf[10];
    itoa((int)Sequences.size(), buf, 10);
    txtSPRCSequenceCount->Caption = buf;
    txtSPRCSequenceCount->Refresh();
    m_Sequences = Sequences.size();
    lstSPRCSequences->ItemIndex = m_Sequences - 1;
    Show();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSPRC::btnSPRCRemoveSequenceClick(TObject *Sender)
{
    if(Sequences.size() == 0)
    {   
        Refresh();
        return;
    }        
    vector <ImageList>::iterator it = Sequences.begin();
    
    if(lstSPRCSequences->ItemIndex == -1)
    {
        lstSPRCSequences->ItemIndex = 0;
        lstSPRCSequences->DeleteSelected();
        Sequences.erase(Sequences.begin());
    }
    else
    {    
        for(int i = 0; i < Sequences.size(); ++i, ++it)
        {
            if(i == lstSPRCSequences->ItemIndex)
            {
                lstSPRCSequences->DeleteSelected();
                Sequences.erase(it);
                break;
            }
        }
    }
    char buf[10];
    itoa((int)Sequences.size(), buf, 10);
    txtSPRCSequenceCount->Caption = buf;
    txtSPRCSequenceCount->Refresh();
    m_Sequences = Sequences.size();

    Show();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSPRC::FormCreate(TObject *Sender)
{
    lstSPRCSequences->DoubleBuffered = true;
    lstSPRCSequenceImages->DoubleBuffered = true;
    pnlSPRCImagePreview->DoubleBuffered = true;

    PIXELFORMATDESCRIPTOR  tPFD = { sizeof(PIXELFORMATDESCRIPTOR),
                                1,
                                PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                                PFD_TYPE_RGBA,
                                24,
                                0,0,0,0,0,0,
                                0,0,
                                0,0,0,0,0,
                                32,
                                0,
                                0,
                                PFD_MAIN_PLANE,
                                0,
                                0,0 };


  // Set up the GL render context.
  mDC = GetDC(pnlSPRCImagePreview->Handle);
  mPF = ChoosePixelFormat(mDC,&tPFD);
  SetPixelFormat(mDC,mPF,&tPFD);
  mRC = wglCreateContext(mDC);
  if(0 == mRC)
    ShowMessage("Failed to create render context.");
  if(!wglMakeCurrent(mDC,mRC))
    ShowMessage("Failed to make context current.");

  mContextW = pnlSPRCImagePreview->ClientWidth;
  mContextH = pnlSPRCImagePreview->ClientHeight;

  // Set up GL.
  glEnable(GL_CULL_FACE);
  glClearColor(0.0f,0.0f,0.4f,1.0f);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_DONT_CARE,GL_FASTEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSPRC::btnSPRCNewSequenceImageClick(TObject *Sender)
{
     int index = lstSPRCSequences->ItemIndex;
     // no sequence selected
     if(index == -1)
        return;
     // check for valid sequence values
    if(Sequences[index].Header.facings == 0 ||
        Sequences[index].Header.frameWidth == 0 ||
        Sequences[index].Header.frameHeight == 0)
    {
        MessageBox(this->Handle, "Please enter non-zero data in the sequence data fields.",
                   "Insufficient Data Provided.", MB_OK);
        return;
    }
    // we're okay to go
    if(OpenDialogSPRCBitmaps->Execute())
    {
        char buf[10];
        AnsiString Item = OpenDialogSPRCBitmaps->FileName;
        LoadBitmapFile(Item.c_str());
        lstSPRCSequenceImages->AddItem(Item, NULL);
      
        Show();
    }

    MaintainSequenceImages();
}
//---------------------------------------------------------------------------


void __fastcall TfrmSPRC::btnSPRCApplyClick(TObject *Sender)
{
    std::string name = Tag->Name();
    std::string desc = Tag->Desc();
    unsigned long ident = Tag->Ident();

    CTagMgr->Release(Tag);
    Tag = dcast< CTag_sprc* >(CTagMgr->Create(kTag_sprc));
    //delete Tag;
    //Tag = new CTag_sprc;
    Tag->Name(name);
    Tag->Desc(desc);
    
    Tag->SequenceCount = Sequences.size();
    if(Sequences.size() == 0)
    {
        Beep(2000, 30);
        return;
    }
    unsigned long MaxBufferSize = 0;
    for(int i = 0; i < Sequences.size(); ++i)
    {
        Sequences[i].Header.frames_per_facing = Sequences[i].images.size() / Sequences[i].Header.facings;
        Tag->Sequence.push_back(Sequences[i].Header);
        MaxBufferSize += (Sequences[i].Header.frameWidth * 
                            Sequences[i].Header.frameHeight *
                            Sequences[i].images.size() * 4);     // fixme
        
    }
    
    Tag->ImageData = new unsigned char[MaxBufferSize];
    atPointer = Tag->ImageData;
    for(int i = 0; i < Sequences.size(); ++i)
        for(int j = 0; j < Sequences[i].images.size(); ++j)
        {
            int size = Sequences[i].Header.frameWidth * Sequences[i].Header.frameHeight * 4;    // fixme
            FILE *fp2;
            char buf[25];
            sprintf(buf, "saveout.raw", j);
            fp2 = fopen(buf, "wb");
            if(!fp2)
                Beep(2000, 200);

            fwrite(Sequences[i].images[j], size , 1, fp2);
            //nsl::bstream b;
            //b.raw_put(Sequences[i].images[j],size);
            //fwrite(b.raw_get(), size, 1 , fp2);
            fclose(fp2);

            memcpy(atPointer, Sequences[i].images[j], size);
            atPointer += size;
        }
    CTagMgr->Archive(kTag_sprc, Tag);
    Release();
    //delete this;
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TfrmSPRC::dlgAlphaPickerClose(TObject *Sender)
{
    imgSPRCAlphaPicker->Canvas->Brush->Color = dlgAlphaPicker->Color;   
    imgSPRCAlphaPicker->Canvas->Rectangle(0,0,44,44);
    Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSPRC::imgSPRCAlphaPickerDblClick(TObject *Sender)
{
 dlgAlphaPicker->Execute();
 imgSPRCAlphaPicker->Canvas->Brush->Color = dlgAlphaPicker->Color;   
 imgSPRCAlphaPicker->Canvas->Rectangle(0,0,44,44);
 Show();
 char red[10], green[10], blue[10];
 itoa(EXTRACT_R(dlgAlphaPicker->Color), red, 10);
 itoa(EXTRACT_G(dlgAlphaPicker->Color), green, 10);
 itoa(EXTRACT_B(dlgAlphaPicker->Color), blue, 10);
 txtSPRCAlphaValueRed->Caption = red;
 txtSPRCAlphaValueGreen->Caption = green;
 txtSPRCAlphaValueBlue->Caption = blue;
}
//---------------------------------------------------------------------------

 
//---------------------------------------------------------------------------

void __fastcall TfrmSPRC::FormShow(TObject *Sender)
{
    imgSPRCAlphaPicker->Canvas->Rectangle(0,0,44,44);
    
}
//---------------------------------------------------------------------------

void __fastcall TfrmSPRC::editSPRCFacingsChange(TObject *Sender)
{
    int Index = lstSPRCSequences->ItemIndex;
    if (Index == -1)
        return;
    Sequences[Index].Header.facings = editSPRCFacings->Text.ToInt();
    MaintainSequenceImages();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSPRC::editSPRCFrameHeightChange(TObject *Sender)
{
    int Index = lstSPRCSequences->ItemIndex;
    if (Index == -1)
        return;
    Sequences[Index].Header.frameHeight = editSPRCFrameHeight->Text.ToInt();    
}
//---------------------------------------------------------------------------

void __fastcall TfrmSPRC::editSPRCFrameWidthChange(TObject *Sender)
{
    int Index = lstSPRCSequences->ItemIndex;
    if (Index == -1)
        return;
    Sequences[Index].Header.frameWidth = editSPRCFrameWidth->Text.ToInt();     
}
//---------------------------------------------------------------------------

void __fastcall TfrmSPRC::lstSPRCSequencesClick(TObject *Sender)
{
    int Index = lstSPRCSequences->ItemIndex;
    if (Index == -1)
        return;
    lstSPRCSequenceImages->ItemIndex = 0;
    char facings[1024], width[4096], height[4096];
    itoa(Sequences[Index].Header.facings, facings, 10);
    itoa(Sequences[Index].Header.frameHeight, height, 10);
    itoa(Sequences[Index].Header.frameWidth, width, 10);
    editSPRCFacings->Text = facings;
    editSPRCFrameHeight->Text = height;
    editSPRCFrameWidth->Text = width; 

    MaintainSequenceImages();
    if(Sequences[Index].images.size() > 0)
        lstSPRCSequenceImages->ItemIndex = 0;
    Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSPRC::btnSPRCNewSequenceMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    int Index = lstSPRCSequences->ItemIndex;
    if (Index == -1)
        return;
    char facings[1024], width[4096], height[4096];
    itoa(Sequences[Index].Header.facings, facings, 10);
    itoa(Sequences[Index].Header.frameHeight, height, 10);
    itoa(Sequences[Index].Header.frameWidth, width, 10);
    editSPRCFacings->Text = facings;
    editSPRCFrameHeight->Text = height; 
    editSPRCFrameWidth->Text = width;   
}
//---------------------------------------------------------------------------

bool TfrmSPRC::LoadBitmapFile(const char *Filename)
{
    int Index = lstSPRCSequences->ItemIndex;
    AUX_RGBImageRec *bits = new AUX_RGBImageRec;

    // attempt to load a bitmap file
    FILE *fp = NULL;									// File Handle
    if (!Filename)										// Make Sure A Filename Was Given
		return NULL;									// If Not Return NULL
	
	fp = fopen(Filename,"r");							// Check To See If The File Exists

	if (fp)										    	// Does The File Exist?
	{
		fclose(fp);									    // Close The Handle
		bits = auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}
    else
        return NULL;									// If Load Failed Return NULL

    unsigned char r, g, b;
    r = txtSPRCAlphaValueRed->Caption.ToInt();
    g = txtSPRCAlphaValueGreen->Caption.ToInt();
    b = txtSPRCAlphaValueBlue->Caption.ToInt();

    int new_w, new_h;
    new_w = editSPRCFrameWidth->Text.ToInt();
    new_h = editSPRCFrameHeight->Text.ToInt();
//    if(Scale(bits->sizeX, bits->sizeY, new_w, new_h, bits->data))
//    {
        bits->sizeX = new_w;
        bits->sizeY = new_h;
//    }
//    else
//    {
//        return false;
//   }

    unsigned char blend;

    if(chkSPRCBlend->Checked)
        blend = trkSPRCBlend->Position;
    else
        blend = 255;

    BYTE *buf = new BYTE[4 * bits->sizeX * bits->sizeY];
 		for(int i = 0, j = 0; i < (3 * bits->sizeX * bits->sizeY); )
  		{
   		   	buf[j] = *(bits->data + i);
			buf[j + 1] = *(bits->data + i + 1);
	 		buf[j + 2] = *(bits->data + i + 2);
            if(buf[j] == r &&  buf[j + 1] == g && buf[j + 2] == b)
	   			buf[j + 3] = 0;		// transparent
 			else
    			buf[j + 3] = blend;  
            i += 3;
            j += 4;
  	  	}
    FILE *fp2;
    fp2 = fopen("savein.raw", "wb");
    if(!fp2)
        Beep(2000, 200);
    fwrite(buf, 64*64*4 , 1, fp2);
    fclose(fp2);
    Sequences[Index].images.push_back(buf);
    delete bits->data;
    delete bits;
    return true;
}

int TfrmSPRC::Scale(int old_w, int old_h, int new_w, int new_h,
                    unsigned char *bits)
{
    unsigned char *new_bits;
    if(new_w && new_h && old_w && old_h)
    {
        new_bits = new unsigned char[new_h * new_w * 3];
    }
	else
	{
		return 0;
	}
	
	int channelAmount = 3;

	unsigned char *SrcL;
	unsigned char *DstL;
	
	int SrcHeight = old_h;
	int SrcWidth  = old_w;
	int DstHeight   = new_h;
	int DstWidth    = new_w;
	
	double SrcX = 0;
	double SrcY = 0;
	int DstX	= 0;
	int DstY	= 0;
	int channel = 0;
	
	
	SrcY = 0;
	SrcX = 0;
	int ErrorAccumulatorX	= 0;
	//int ErrorAccumulatorY	= (SrcHeight / 2) - DstHeight;
	int channelOffsetDest	= 0;
	int channelOffsetSource = 0;

	for (DstY = 0; DstY < DstHeight; ++DstY)
	{
		SrcY = (DstY * SrcHeight + 	(SrcHeight >> 1)) / DstHeight;
		
		SrcL = bits + (int)SrcY * ((old_w * 3 + 3) & ~3);
		DstL   = new_bits + (int)DstY * ((new_w * 3 + 3) & ~3);

		SrcX = 0;
		ErrorAccumulatorX = SrcWidth / 2 - DstWidth;

		for (DstX = 0; DstX < DstWidth; ++DstX)
		{
			while (ErrorAccumulatorX >= 0)
			{
				++SrcX;
				ErrorAccumulatorX -= DstWidth;
			}

			if(SrcX >= SrcWidth)
				SrcX = SrcWidth - 1;
			else if(SrcX < 0)
				SrcX = 0;
							
			assert(SrcX >= 0 && SrcX < SrcWidth);
		
			ErrorAccumulatorX += SrcWidth;
			channelOffsetDest = DstX * channelAmount;
			channelOffsetSource = SrcX * channelAmount;
			
			for (channel = 0; channel < channelAmount; ++channel)
				DstL[channelOffsetDest + channel] = SrcL[channelOffsetSource + channel];
					
		} // end for DestX
	} // end for DestY

	delete[] bits;
    bits = new_bits;	
	
	
    return 1;


}
void __fastcall TfrmSPRC::lstSPRCSequenceImagesClick(TObject *Sender)
{
    if(lstSPRCSequences->ItemIndex == -1)
        return;
    else
    {
       /* CurrTexture = Textures[lstSPRCSequences->ItemIndex];
        CurrTexture.Bind(lstSPRCSequenceImages->ItemIndex);
        Show();*/
        int x = Sequences[lstSPRCSequences->ItemIndex].Header.frameWidth;
        int y = Sequences[lstSPRCSequences->ItemIndex].Header.frameHeight;
        BYTE *buf = Sequences[lstSPRCSequences->ItemIndex].images[lstSPRCSequenceImages->ItemIndex];
        glDrawPixels(x, y, GL_RGBA, GL_UNSIGNED_BYTE, buf);
    }
}
//---------------------------------------------------------------------------
void TfrmSPRC::MaintainSequenceImages(void)
{
    int Index = lstSPRCSequences->ItemIndex;
    if(Index == -1)
        return;
    lstSPRCSequenceImages->Clear();
    if(Sequences[Index].Header.facings > 0 &&
        Sequences[Index].Header.frameHeight > 0 &&
        Sequences[Index].Header.frameWidth > 0)
    {    
        int frames = Sequences[Index].images.size();
        int facings = Sequences[Index].Header.facings;
        int *FaceList = new int[facings];
        int fpf = frames / facings;
        int curFace = 0;
        //Sequences[Index].Header.frames_per_facing = fpf;
        memset(FaceList, 0, facings * sizeof(int));
        //Sequences[Index].Header.frames_per_facing = fpf;
        
        for(int i = 0; i < frames; ++i)
        {
            if(curFace == facings)
                curFace = 0;
            FaceList[curFace] += 1;
            curFace++;
        }
        for(int i = 0; i < facings; ++i)
        {
            for(int j = 0; j < FaceList[i]; ++j)
            {
                char buf[50];
                sprintf(buf, "Facing: %d, Frame: %d", i, j);
                AnsiString Item = buf;
                lstSPRCSequenceImages->AddItem(Item, NULL);    
            }
        }
        delete[] FaceList;
    }
    Show(); 
    
}

bool TfrmSPRC::ExtractFromTag(void)
{
    if(Tag->SequenceCount == 0)
    {
        return false;
    }
    unsigned char *atPtr = Tag->ImageData;

    for(int i = 0; i < Tag->SequenceCount; ++i)
    {
        char buf[50];
        sprintf(buf, "Sequence: %d", i);
        AnsiString Item = buf;
        lstSPRCSequences->AddItem(Item, NULL);
        ImageList il;
        il.Header = Tag->Sequence[i];

        for(int j = 0; j < (il.Header.frames_per_facing * il.Header.facings); ++j)
        {
            unsigned char *t = new unsigned char[il.Header.frameHeight * il.Header.frameWidth * 4];
            il.images.push_back(t);
            memcpy(il.images[j], atPtr, il.Header.frameHeight * il.Header.frameWidth * 4);
            atPtr += il.Header.frameHeight * il.Header.frameWidth * 4;
        }
        Sequences.push_back(il);
    }
    return true;
}

void __fastcall TfrmSPRC::FormDestroy(TObject *Sender)
{
   // Clean up after OGL.
  wglMakeCurrent(0,0);
  wglDeleteContext(mRC);
  Application->OnIdle = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSPRC::btnSPRCRevertClick(TObject *Sender)
{
    Release();
    //delete this;    
}
//---------------------------------------------------------------------------

void __fastcall TfrmSPRC::chkSPRCBlendClick(TObject *Sender)
{
    trkSPRCBlend->Enabled = chkSPRCBlend->Checked;
    trkSPRCBlend->Visible =  chkSPRCBlend->Checked;
    Show();    
}
//---------------------------------------------------------------------------

void __fastcall TfrmSPRC::FormClose(TObject *Sender, TCloseAction &Action)
{
    CTagMgr->Release(Tag);
    Application->OnIdle = 0; 
}
//---------------------------------------------------------------------------

void __fastcall TfrmSPRC::FormActivate(TObject *Sender)
{
    //Sequences.clear();    
}
//---------------------------------------------------------------------------

void __fastcall TfrmSPRC::FormResize(TObject *Sender)
{
    // Adjust sizes.
    mContextW = pnlSPRCImagePreview->ClientWidth;
    mContextH = pnlSPRCImagePreview->ClientHeight;
    if(mContextH == 0)
        mContextH = 1;

  // Recompute viewport and projection matrix.
  glViewport(0,0,mContextW,mContextH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f,(float)(mContextW) * 2.0f,0.0f, (float)(mContextH) * 2.0f,-20.0f,20.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();    
}
//---------------------------------------------------------------------------

void __fastcall TfrmSPRC::FormPaint(TObject *Sender)
{
  /*if(lstSPRCSequences->ItemIndex == -1)
    return;
  else if(lstSPRCSequenceImages->ItemIndex == -1)
    return;

  CurrTexture = Textures[lstSPRCSequences->ItemIndex];  
  // Set up.
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  CurrTexture.Bind(lstSPRCSequenceImages->ItemIndex);
  
  glBegin(GL_QUADS);
  	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  	glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.f, 0.f, 0.0f);				// bottom-left
  	glTexCoord2f(1.0f, 0.0f); glVertex3f( (float)mContextW , 0.f, 0.0f);			// bottom-right
  	glTexCoord2f(1.0f, 1.0f); glVertex3f( (float)mContextW,  (float)mContextH, 0.0f);				// top-right
  	glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.f,  (float)mContextH, 0.0f);					// top-left
  	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glEnd();

  // Force rendering to finish.
  glFlush();
  
  SwapBuffers(mDC);
  */
}
//---------------------------------------------------------------------------
void __fastcall TfrmSPRC::IdleLoop(TObject*, bool& done)
{
  done = true;
  if(lstSPRCSequences->ItemIndex == -1)
    return;
  else if(lstSPRCSequenceImages->ItemIndex == -1)
    return;

//  CurrTexture = Textures[lstSPRCSequences->ItemIndex];
  // Set up.
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

//  CurrTexture.Bind(lstSPRCSequenceImages->ItemIndex);

  glViewport(0, 0, mContextW, mContextH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-.5f,0.5f, -0.5f, 0.5f,-20.0f,20.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();    
  
/*  glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  	glTexCoord2f(0.0f, 0.0f); glVertex3f( -.5f,  -.5f, 0.0f);				// bottom-left
    glTexCoord2f(1.0f, 0.0f); glVertex3f( .5f , -.5f, 0.0f);			// bottom-right
  	glTexCoord2f(1.0f, 1.0f); glVertex3f( .5f,  .5f, 0.0f);				// top-right
  	glTexCoord2f(0.0f, 1.0f); glVertex3f( -.5f,  .5f, 0.0f);					// top-left
  	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glEnd();
*/
  // Force rendering to finish.
  glFlush();

  int x = Sequences[lstSPRCSequences->ItemIndex].Header.frameWidth;
        int y = Sequences[lstSPRCSequences->ItemIndex].Header.frameHeight;
        BYTE *buf = Sequences[lstSPRCSequences->ItemIndex].images[lstSPRCSequenceImages->ItemIndex];
        glDrawPixels(x, y, GL_RGBA, GL_UNSIGNED_BYTE, buf);
  SwapBuffers(mDC);
}
void __fastcall TfrmSPRC::btnSPRCRemoveSequenceImageClick(TObject *Sender)
{
    int Index = lstSPRCSequences->ItemIndex;
        
    if(Sequences.size() == 0)
    {   
        Refresh();
        return;
    }        

    vector <unsigned char *>::iterator it = Sequences[Index].images.begin();
    
    if(lstSPRCSequenceImages->ItemIndex == -1)
    {
        lstSPRCSequenceImages->ItemIndex = 0;
        lstSPRCSequenceImages->DeleteSelected();
        Sequences[Index].images.erase(Sequences[Index].images.begin());
    }
    else
    {    
        for(int i = 0; i < Sequences[Index].images.size(); ++i, ++it)
        {
            if(i == lstSPRCSequenceImages->ItemIndex)
            {
                lstSPRCSequenceImages->DeleteSelected();
                Sequences[Index].images.erase(it);
                break;
            }
        }
    }
    //char buf[10];
    //itoa((int)Sequences.size(), buf, 10);
    //txtSPRCSequenceCount->Caption = buf;
    //txtSPRCSequenceCount->Refresh();
    //m_Sequences = Sequences.size();
    MaintainSequenceImages();
    Show();
}
//---------------------------------------------------------------------------

