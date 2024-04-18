//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "ApathyMain.h"

#include "CEditor_tmap.h"
#include "CEditor_tmapResize.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmTMAP *frmTMAP;
//---------------------------------------------------------------------------
// tile dimensions
const float kMapTile_Width      = 128.0f;                  // World units.
const float kMapTile_Height     = kMapTile_Width / 2.0f;   // World units.
const float kMapTile_HalfWidth  = kMapTile_Width / 2.0f;
const float kMapTile_HalfHeight = kMapTile_Height / 2.0f;

// adjustments
const float kMapTile_EvenRowAdjust  = kMapTile_HalfWidth;
const float kMapTile_OddRowAdjust   = 0.0f;
const float kMapTile_TopAdjust      = 32.0f;
const float kMapTile_BotAdjust      = 32.0f;
const float kMapTile_FirstRowAdjust = -kMapTile_BotAdjust;
const float kMapTile_NextRowAdjust  = kMapTile_BotAdjust;
const float kMapTile_RawWidth       = kMapTile_Width;
const float kMapTile_RawHeight      = kMapTile_Height + kMapTile_TopAdjust + kMapTile_BotAdjust;
const float kMapTile_Slope          = kMapTile_Height / kMapTile_Width;

// scroll zones
const int    kScrollZoneSize = 24;     // Pixels.
const float  kScrollSpeed    = 100.0f;  // World units.

// proxies
const float  kProxyWidth  = 50.0f;
const float  kProxyHeight = 100.0f;
const float  kProxyShade  = 0.75f; // Intensity value of proxy blur.
//---------------------------------------------------------------------------
__fastcall TfrmTMAP::TfrmTMAP(TComponent* Owner,const std::string &fn)
: CEditor(Owner,kTag_tmap)
{
  // Load the tag.
  mTag = (CTag_tmap*)CTagMgr->Unarchive(kTag_tmap,fn);

  // Set the name of the window.
  Caption = nsl::stformat("tmap %s (%s)",mTag->Name().c_str(),mTag->Desc().c_str()).c_str();

  // Redraw the map view on idle.
  Application->OnIdle = IdleLoop;

  // Position camera.
  mCamX = 100.0f;
  mCamY = 100.0f;
  mCamZ = 2.0f;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::UpdateTileMap(void)
{
  // Erase existing tile sprites.
  for(unsigned int i = 0; i < mTileSprites.size(); ++i)
    delete mTileSprites[i];
  mTileSprites.clear();
  mTileLayoutSprites.clear();

  // Cache the collection used to render the map.
  if(mTag->collection == "")
    mTag->collection = "sprc_dbg";
  CTagMgr->Cache(kTag_sprc,cmbCollection->Text.c_str());

  // Make sure there is at least one tile in the map.
  if(mTag->tileCnt == 0)
  {
  CTag_tmap::StTile  tDummyTile;

    tDummyTile.name = "basic tile";
    tDummyTile.terrainType = 0;
    tDummyTile.sequenceNormal = 0;
    tDummyTile.sequenceBurnt = 0;
    tDummyTile.flags = 0;

    mTag->tileData.push_back(tDummyTile);
    ++mTag->tileCnt;
  }

  // Rebuild master tile sprites.
  for(int i = 0; i < mTag->tileCnt; ++i)
  {
    mTileSprites.push_back(new CSprite(0,0,kMapTile_RawWidth,kMapTile_RawHeight,
                                       cmbCollection->Text.c_str(),
                                       false,
                                       mTag->tileData[i].sequenceNormal,
                                       0));
    // Master sprites are all set to draw at 0,0.
    // When the map is drawn, they'll be moved as needed, based on the
    // the layout.
  }

  // Rebuild layout.
  for(int i = 0; i < mTag->mapHeight; ++i)
    for(int j = 0; j < mTag->mapWidth; ++j)
      mTileLayoutSprites.push_back(mTag->tileLayout[i * mTag->mapWidth + j]);
  
  // Clear cache.
 // CTagMgr->ClearCache(kTag_sprc,cmbCollection->Text.c_str());
}

//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::IdleLoop(TObject*, bool& done)
{
  done = true;
  RenderTileMap();
  SwapBuffers(mDC);

  if(mTag->groupCnt == 0)
  {
    edtGroupName->Enabled = false;
    lstUnitsInGroup->Enabled = false;
  }
  else
  {
    edtGroupName->Enabled = true;
    lstUnitsInGroup->Enabled = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::RenderTileMap(void)
{
float  tX = kMapTile_EvenRowAdjust;
float  tY = kMapTile_FirstRowAdjust;
int    tIdx = 0;

  // Set up.
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Orient the camera.
  glTranslatef(mCamX,mCamY,0.0f);

  // Draw the tiles.
  for(int i = 0; i < mTag->mapHeight; ++i)
  {
    for(int j = 0; j < mTag->mapWidth; ++j)
    {
    int  tTileIdx = mTileLayoutSprites[tIdx];

      mTileSprites[tTileIdx]->SetWorldX(tX);
      mTileSprites[tTileIdx]->SetWorldY(tY);
      mTileSprites[tTileIdx]->Draw();
      tX += kMapTile_Width;
      ++tIdx;
    }

    // Move to the next row.
    tY += kMapTile_NextRowAdjust;
    if(i % 2)
      tX = kMapTile_EvenRowAdjust;
    else
      tX = kMapTile_OddRowAdjust;
  }

  // Draw the units.
  for(int i = 0 ; i < mUnitSprites.size(); ++i)
    mUnitSprites[i]->Draw();

  // Force rendering to finish.
  glFlush();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::ScreenToWorld(int x,int y,float &ox,float &oy)
{
GLint viewport[4];
GLdouble modelview[16];
GLdouble projection[16];
GLfloat winX, winY, winZ;
GLdouble posX, posY, posZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( (GLint)winX, (GLint)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	ox = posX;
  oy = posY;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::WorldToTile(float x,float y,int &tx,int &ty)
{
  // Inputs must be adjusted to handle the fact that
  // Apathy lets you view just beyond the edge of the map.
  y -= kMapTile_BotAdjust;
  x -= kMapTile_HalfWidth;

int  tSplitY = scast< int >((y + kMapTile_HalfHeight) / kMapTile_HalfHeight) - 1;
int  tSplitX = scast< int >((x + kMapTile_HalfWidth) / kMapTile_HalfWidth) - 1;
int  tLocalX = scast< int >(x) % scast< int >(kMapTile_HalfWidth);
int  tLocalY = scast< int >(y) % scast< int >(kMapTile_HalfHeight);

  // The split coordinates index into a rectangle that encloses no more than two tiles,
  // split (thus the name) by a diagonal line. This diagonal is lower-left to upper-right
  // for odd X splits, and upper-left to lower-right for even X splits.
  // To get the map tile clicked, we first determine which side of the split the click hit.
  if((tSplitX % 2) ^ (tSplitY % 2))
  // Even split.
  {
  float  tLineY = -kMapTile_Slope * tLocalX + kMapTile_HalfHeight;

    if(tLocalY < tLineY)
    {
      // On the lower half.
      tx = tSplitX / 2;
      ty = tSplitY;
    }
    else
    {
      // On the upper half.
      tx = (tSplitX / 2) + (tSplitY % 2 ? 0 : 1);
      ty = tSplitY + 1;
    }
  }
  else
  // Odd split.
  {
  float  tLineY = kMapTile_Slope * tLocalX;

    if(tLocalY < tLineY)
    {
      // On the lower half.
      tx = (tSplitX / 2) + (tSplitY % 2 ? 1 : 0);
      ty = tSplitY;
    }
    else
    {
      // On the upper half.
      tx = tSplitX / 2;
      ty = tSplitY + 1;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::PopulateControls(void)
{
  // Use a valid collection.
  if(mTag->collection == "")
    cmbCollection->ItemIndex = 0;
  else
    cmbCollection->Text = mTag->collection.c_str();

  cmbStartScript->Text = mTag->startScript.c_str();
  cmbEndScript->Text = mTag->stopScript.c_str();
  txtWidth->Caption = mTag->mapWidth;
  txtHeight->Caption = mTag->mapHeight;
  edtMaxTeams->Text = mTag->teamCnt;

  // Read all the tiles; set up rendering stuff
  // (sprites, et cetera).
  UpdateTileMap();

  // Load up the units.
  for(unsigned int i = 0; i < mTag->unitCnt; ++i)
    mUnitSprites.push_back(new CRect(mTag->units[i].y,mTag->units[i].x - 25,50,100));

  // Populate tile type list box.
  for(unsigned int i = 0; i < mTag->tileCnt; ++i)
    lstTileList->Items->Add(mTag->tileData[i].name.c_str());
  lstTileList->ItemIndex = 0;
  lstTileListClick(0);

  // Populate group list box.
  for(unsigned int i = 0; i < mTag->groupCnt; ++i)
    lstUnitGroups->Items->Add(mTag->groups[i].name.c_str());
  lstUnitGroups->ItemIndex = 0;
  lstUnitGroupsClick(0);

  // Populate waypoints list box.
  for(unsigned int i = 0; i < mTag->waypointCnt; ++i)
    lstWaypoints->Items->Add(mTag->waypoints[i].name.c_str());
  lstWaypoints->ItemIndex = 0;
  //lstWaypointsClick(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::PopulateTag(void)
{
  // Copy data from the controls to the tag.
  mTag->collection = cmbCollection->Text.c_str();
  mTag->startScript = cmbStartScript->Text.c_str();
  mTag->stopScript = cmbEndScript->Text.c_str();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::DeselectAllUnits(void)
{
  // Deselect everybody.
  for(int j = 0; j < mSelectedUnits.size(); ++j)
    mUnitSprites[mSelectedUnits[j]]->SetBorderColor(0.0f,0.0f,0.0f,1.0f);
  mSelectedUnits.clear();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::FormCreate(TObject *Sender)
{
nsl::stringlist           tTags;
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
  mDC = GetDC(panMapView->Handle);
  mPF = ChoosePixelFormat(mDC,&tPFD);
  SetPixelFormat(mDC,mPF,&tPFD);
  mRC = wglCreateContext(mDC);
  if(0 == mRC)
    ShowMessage("Failed to create render context.");
  if(!wglMakeCurrent(mDC,mRC))
    ShowMessage("Failed to make context current.");

  mContextW = panMapView->ClientWidth;
  mContextH = panMapView->ClientHeight;

  // Set up GL.
  glEnable(GL_CULL_FACE);
  glClearColor(0.0f,0.0f,0.0f,1.0f);
	glShadeModel(GL_SMOOTH);
  glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_DONT_CARE,GL_FASTEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

  // Fill collection combo box.
  frmMain->GetTagList(kTag_sprc,tTags);
  for(unsigned int i = 0; i < tTags.size(); ++i)
    cmbCollection->Items->Add(tTags[i].c_str());

  // Fill script combo boxes.
  /*frmMain->GetTagList(kTag_scri,tTags);
  for(unsigned int i = 0; i < tTags.size(); ++i)
  {
    cmbStartScript->Items->Add(tTags[i].c_str());
    cmbEndScript->Items->Add(tTags[i].c_str());
  } */

  // Fill unit list box.
  frmMain->GetTagList(kTag_unit,tTags);
  for(unsigned int i = 0; i < tTags.size(); ++i)
  {
    lstUnitList->Items->Add(tTags[i].c_str());
  }

  // Default to property tool.
  pagToolOpts->ActivePage = tabPropertyTool;

  // Make list boxes and combo boxes have selections.
  lstTileList->ItemIndex = 0;
  lstUnitList->ItemIndex = 0;

  // Populate the controls.
  PopulateControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::FormDestroy(TObject *Sender)
{
  // Delete the tag.
  CTagMgr->Release(mTag);

  // Clean up after OGL.
  wglMakeCurrent(0,0);
  wglDeleteContext(mRC);

  // Do nothing during idle now.
  Application->OnIdle = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::FormResize(TObject *Sender)
{
  // Adjust sizes.
  mContextW = panMapView->ClientWidth;
  mContextH = panMapView->ClientHeight;
  if(mContextH == 0)
    mContextH = 1;

  // Recompute viewport and projection matrix.
  glViewport(0,0,mContextW,mContextH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f,(float)(mContextW) * mCamZ,0.0f, (float)(mContextH) * mCamZ,-20.0f,20.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::FormPaint(TObject *Sender)
{
  RenderTileMap();
  SwapBuffers(mDC);
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::FormClose(TObject *Sender, TCloseAction &Action)
{
  Release();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::btnSaveClick(TObject *Sender)
{
  // Archive the tag.
  PopulateTag();
  CTagMgr->Archive(mTag->Ident(),mTag);

  // Close the editor.
  Release();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::btnCancelClick(TObject *Sender)
{
  Release();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::btnPropertyToolClick(TObject *Sender)
{
  // Adjust down states.
  btnPropertyTool->Down = true;
  btnTileTool->Down = false;
  btnUnitTool->Down = false;
  btnGroupTool->Down = false;
        btnWayTool->Down = false;
  pagToolOpts->ActivePage = tabPropertyTool;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::btnTileToolClick(TObject *Sender)
{
  // Adjust down states.
  btnPropertyTool->Down = false;
  btnTileTool->Down = true;
  btnUnitTool->Down = false;
  btnGroupTool->Down = false;
    btnWayTool->Down = false;
  pagToolOpts->ActivePage = tabTileTool;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::btnUnitToolClick(TObject *Sender)
{
  // Adjust down states.
  btnPropertyTool->Down = false;
  btnTileTool->Down = false;
  btnUnitTool->Down = true;
  btnGroupTool->Down = false;
          btnWayTool->Down = false;
  pagToolOpts->ActivePage = tabUnitTool;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::btnResizeClick(TObject *Sender)
{
  frmTMAP_Resize->ShowModal();
  if(frmTMAP_Resize->ModalResult == mrOk)
  {
    // Resize the map.
    mTag->mapWidth = frmTMAP_Resize->edtWidth->Text.ToInt();
    mTag->mapHeight = frmTMAP_Resize->edtHeight->Text.ToInt();
    txtWidth->Caption = mTag->mapWidth;
    txtHeight->Caption = mTag->mapHeight;

    // Just in case....
    frmTMAP_Resize->edtWidth->Text = mTag->mapWidth;
    frmTMAP_Resize->edtHeight->Text = mTag->mapHeight;

    // Erase tile layout data, then force an update.
    mTag->tileLayout.clear();
    mTag->tileLayout.insert(mTag->tileLayout.begin(),(mTag->mapWidth * mTag->mapHeight),0);
    UpdateTileMap();
  }
  else
  {
    // Put old values in width/height fields.
    frmTMAP_Resize->edtWidth->Text = mTag->mapWidth;
    frmTMAP_Resize->edtHeight->Text = mTag->mapHeight;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::panMapViewMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
float  tWX,tWY;
int    tTX,tTY;

  // Doku deshita ka?
  ScreenToWorld(X,Y,tWX,tWY);
  WorldToTile(tWX,tWY,tTX,tTY);

  if(pagToolOpts->ActivePage == tabTileTool)
  {
    if(tTX >= 0 && tTX < mTag->mapWidth &&
       tTY >= 0 && tTY < mTag->mapHeight)
    {
    int  tTile = lstTileList->ItemIndex;

      // Place the selected tile at the clicked location.
      mTileLayoutSprites[tTY * mTag->mapWidth + tTX] = tTile;
      mTag->tileLayout[tTY * mTag->mapWidth + tTX] = tTile;
    }
  }
  else if(pagToolOpts->ActivePage == tabUnitTool && btnUnitSelect->Down)
  {
  bool  tHitUnit = false;

    // Bounding-box collision test to find the unit that was hit.
    for(int i = 0; i < mTag->unitCnt; ++i)
    {
      if(tWX >= mUnitSprites[i]->GetWorldX() &&
         tWX <= (mUnitSprites[i]->GetWorldX() + mUnitSprites[i]->GetWidth()) &&
         tWY >= mUnitSprites[i]->GetWorldY() &&
         tWY <= (mUnitSprites[i]->GetWorldY() + mUnitSprites[i]->GetHeight()))
      {
        // We hit the unit. Select it.
        if(std::find(mSelectedUnits.begin(),mSelectedUnits.end(),i) == mSelectedUnits.end())
        {
          DeselectAllUnits();

          mSelectedUnits.push_back(i);
          mUnitSprites[i]->SetBorderColor(1.0f,1.0f,1.0f,1.0f);
        }

        // Don't need to continue the search.
        tHitUnit = true;
      }

      // If user clicked off a unit, deselect everything.
      if(!tHitUnit)
      {
        panInspectSomething->Visible = false;
        panInspectNothing->Visible = true;
        DeselectAllUnits();
      }
      else
      {
        panInspectSomething->Visible = true;
        panInspectNothing->Visible = false;

        // Put meaningful data in the inspector window.
        for(int i = 0; i < mSelectedUnits.size(); ++i)
        {
          edtUnitTeam->Text = (int)(mTag->units[mSelectedUnits[i]].team);
          chkUnitIsProxy->Checked = mTag->units[mSelectedUnits[i]].is_proxy;
        }

        break;
      }
    }
  }
  else if(pagToolOpts->ActivePage == tabUnitTool && btnPaintUnit->Down)
  {
    // Is the world coordinate within the bounds of the map?
    // Note that the "jagged" edges of the map are not valid.
    if(tWX >= kMapTile_HalfWidth && tWX < ((mTag->mapWidth * kMapTile_Width) - kMapTile_HalfWidth) &&
       tWY >= kMapTile_HalfHeight && tWY < ((mTag->mapHeight * kMapTile_HalfHeight) - kMapTile_HalfHeight))
    {
    CTag_tmap::StUnit  tUnitData;
    int                tUnit = lstUnitList->ItemIndex;

      //FIXME use unit sprites, not rectangles.
      mUnitSprites.push_back(new CRect(tWY,tWX - 25,50,100));

      // Set up the unit in the tag.
      tUnitData.name = lstUnitList->Items->Strings[tUnit].c_str();
      tUnitData.x = tWX;
      tUnitData.y = tWY;
      tUnitData.is_proxy = false;
      tUnitData.team = 1;
      mTag->units.push_back(tUnitData);
      ++mTag->unitCnt;
    }
  }
  else if(pagToolOpts->ActivePage == tabUnitTool && btnPaintProxy->Down)
  {
    // Is the world coordinate within the bounds of the map?
    // Note that the "jagged" edges of the map are not valid.
    if(tWX >= kMapTile_HalfWidth && tWX < ((mTag->mapWidth * kMapTile_Width) - kMapTile_HalfWidth) &&
       tWY >= kMapTile_HalfHeight && tWY < ((mTag->mapHeight * kMapTile_HalfHeight) - kMapTile_HalfHeight))
    {
    CTag_tmap::StUnit  tUnitData;
    int                tUnit = lstUnitList->ItemIndex;

      // Set up the unit in the tag.
      tUnitData.name = lstUnitList->Items->Strings[tUnit].c_str();
      tUnitData.x = tWX;
      tUnitData.y = tWY;
      tUnitData.is_proxy = true;
      tUnitData.team = 1;
      mTag->units.push_back(tUnitData);
      ++mTag->unitCnt;

      // The CRect constructor expects (bottom,left), not (x,y).
    CRect *tProxyRect;

      tProxyRect = new CRect(tWY,tWX - 25,50,100);
      tProxyRect->SetInteriorColorBR(kProxyShade,kProxyShade,kProxyShade,1.0f);
      tProxyRect->SetInteriorColorBL(kProxyShade,kProxyShade,kProxyShade,1.0f);
      tProxyRect->SetInteriorColorTR(kProxyShade,kProxyShade,kProxyShade,0.0f);
      tProxyRect->SetInteriorColorTL(kProxyShade,kProxyShade,kProxyShade,0.0f);
      tProxyRect->SetBorderColor(0.0f,0.0f,0.0f,0.0f);
      mUnitSprites.push_back(tProxyRect);
    }
  }
  else if(pagToolOpts->ActivePage == tabUnitTool && btnClearUnit->Down)
  {
  std::vector< CRect* >::iterator  tIter = mUnitSprites.begin();
  std::vector< CTag_tmap::StUnit >::iterator  tTagIter = mTag->units.begin();

    // Bounding-box collision test to find the unit that was hit.
    while(tIter != mUnitSprites.end())
    {
      if(tWX >= (*tIter)->GetWorldX() &&
         tWX <= ((*tIter)->GetWorldX() + (*tIter)->GetWidth()) &&
         tWY >= (*tIter)->GetWorldY() &&
         tWY <= ((*tIter)->GetWorldY() + (*tIter)->GetHeight()))
      {
        // Delete this unit.
        delete *tIter;
        mUnitSprites.erase(tIter);
        mTag->units.erase(tTagIter);
        mTag->unitCnt--;
        break;
      }

      ++tIter;
      ++tTagIter;
    }
  }
  else if(pagToolOpts->ActivePage == tabGroupTool && btnAddToGroup->Down)
  {
    // Get the clicked unit.
  std::vector< CRect* >::iterator  tIter = mUnitSprites.begin();
  std::vector< CTag_tmap::StUnit >::iterator  tTagIter = mTag->units.begin();
  int i = 0;                                                         // Bounding-box collision test to find the unit that was hit.
    while(tIter != mUnitSprites.end())
    {
      if(tWX >= (*tIter)->GetWorldX() &&
         tWX <= ((*tIter)->GetWorldX() + (*tIter)->GetWidth()) &&
         tWY >= (*tIter)->GetWorldY() &&
         tWY <= ((*tIter)->GetWorldY() + (*tIter)->GetHeight()))
      {
      long         tIdx = lstUnitGroups->ItemIndex;
      std::string  tStr;

        // Add this unit to the current group.
        mTag->groups[tIdx].units.push_back(i);
        tStr = nsl::stformat("%s (#%d) @ (%f %f)",mTag->units[ i ].name.c_str(),
                                             i,
                                             mTag->units[ i ].x,
                                             mTag->units[ i ].y);
        lstUnitsInGroup->Items->Add(tStr.c_str());
        break;
      }

      ++tIter;
      ++tTagIter;
      ++i;
    }
  }
  else if(pagToolOpts->ActivePage == tabGroupTool && btnRemoveFromGroup->Down)
  {
    // Get the clicked unit.
  std::vector< CRect* >::iterator  tIter = mUnitSprites.begin();
  std::vector< CTag_tmap::StUnit >::iterator  tTagIter = mTag->units.begin();
  int i = 0;

    // Bounding-box collision test to find the unit that was hit.
    while(tIter != mUnitSprites.end())
    {
      if(tWX >= (*tIter)->GetWorldX() &&
         tWX <= ((*tIter)->GetWorldX() + (*tIter)->GetWidth()) &&
         tWY >= (*tIter)->GetWorldY() &&
         tWY <= ((*tIter)->GetWorldY() + (*tIter)->GetHeight()))
      {
      long         tIdx = lstUnitGroups->ItemIndex;
      std::string  tStr;
      std::vector< int >::iterator  tGroupIter;

        // Remove this unit from the current group.
        tGroupIter = std::find(mTag->groups[tIdx].units.begin(),
                               mTag->groups[tIdx].units.end(),
                               i);
        if(tGroupIter != mTag->groups[tIdx].units.end())
        {
          mTag->groups[tIdx].units.erase(tGroupIter);
          lstUnitGroupsClick(0);
        }
        break;
      }

      ++tIter;
      ++tTagIter;
      ++i;
    }
  }
  else if(pagToolOpts->ActivePage == tabWaypoints)
  {
  int idx = lstWaypoints->ItemIndex;

    mTag->waypoints[idx].x = tWX;       //hi
    mTag->waypoints[idx].y = tWY;
    edtWayX->Text = tWX;
    edtWayY->Text = tWY;
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  // Scroll the mapview.
  if(Key == VK_LEFT)
    mCamX += kScrollSpeed;
  if(Key == VK_RIGHT)
    mCamX -= kScrollSpeed;
  if(Key == VK_UP)
    mCamY -= kScrollSpeed;
  if(Key == VK_DOWN)
    mCamY += kScrollSpeed;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::btnNewTileClick(TObject *Sender)
{
CTag_tmap::StTile  tTile;

  // Make a new tile.
  tTile.name = "new tile";
  tTile.sequenceNormal = 0;
  tTile.sequenceBurnt = 0;
  tTile.terrainType   = 0;
  tTile.flags = 0;

  lstTileList->Items->Add(tTile.name.c_str());
  mTag->tileData.push_back(tTile);
  mTag->tileCnt++;

  // Make a new tile sprite.
  mTileSprites.push_back(new CSprite(0,0,kMapTile_RawWidth,kMapTile_RawHeight,
                                       "sprc_dbg",
                                        false,
                                        tTile.sequenceNormal,
                                        0));
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::edtTileNameChange(TObject *Sender)
{
int  tIdx = lstTileList->ItemIndex;

  // Change the name of the selected tile type.
  lstTileList->Items->Strings[tIdx] = edtTileName->Text;
  mTag->tileData[tIdx].name = edtTileName->Text.c_str();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::lstTileListClick(TObject *Sender)
{
int  tIdx = lstTileList->ItemIndex;

  // Update the property fields of the selected tile type.
  edtTileName->Text = mTag->tileData[tIdx].name.c_str();
  edtSeqNormal->Text = mTag->tileData[tIdx].sequenceNormal;
  edtSeqBurnt->Text = mTag->tileData[tIdx].sequenceBurnt;
  cmbTerrain->ItemIndex = mTag->tileData[tIdx].terrainType;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::edtSeqNormalChange(TObject *Sender)
{
int  tIdx = lstTileList->ItemIndex;

  // Change the sequence.
  mTag->tileData[tIdx].sequenceNormal = atoi(edtSeqNormal->Text.c_str());
  mTileSprites[tIdx]->SetSequence(atoi(edtSeqNormal->Text.c_str()),0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::btnDeleteTileClick(TObject *Sender)
{
  ShowMessage("You REALLY don't want to do that.");
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::btnPaintUnitClick(TObject *Sender)
{
  // Adjust down states.
  btnUnitSelect->Down = false;
  btnPaintUnit->Down = true;
  btnPaintProxy->Down = false;
  btnClearUnit->Down = false;

  DeselectAllUnits();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::btnPaintProxyClick(TObject *Sender)
{
  // Adjust down states.
  btnUnitSelect->Down = false;
  btnPaintUnit->Down = false;
  btnPaintProxy->Down = true;
  btnClearUnit->Down = false;

  DeselectAllUnits();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::btnUnitSelectClick(TObject *Sender)
{
  // Adjust down states.
  btnUnitSelect->Down = true;
  btnPaintUnit->Down = false;
  btnPaintProxy->Down = false;
  btnClearUnit->Down = false;

  DeselectAllUnits();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::panMapViewMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  // Is the left mouse down?
  if(Shift.Contains(ssLeft))
  {

  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::edtSeqBurntChange(TObject *Sender)
{
int  tIdx = lstTileList->ItemIndex;

  // Change the sequence.
  mTag->tileData[tIdx].sequenceBurnt = atoi(edtSeqBurnt->Text.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::cmbTerrainChange(TObject *Sender)
{
int  tTileIdx = lstTileList->ItemIndex;
int  tTerrainIdx = cmbTerrain->ItemIndex;

  // Change the terrain type.
  mTag->tileData[tTileIdx].terrainType = tTerrainIdx;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::btnClearUnitClick(TObject *Sender)
{
  // Adjust down states.
  btnUnitSelect->Down = false;
  btnPaintUnit->Down = false;
  btnPaintProxy->Down = false;
  btnClearUnit->Down = true;

  DeselectAllUnits();
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::btnGroupToolClick(TObject *Sender)
{
  // Adjust down states.
  btnPropertyTool->Down = false;
  btnTileTool->Down = false;
  btnUnitTool->Down = false;
  btnGroupTool->Down = true;
             btnWayTool->Down = false;
  pagToolOpts->ActivePage = tabGroupTool;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::btnAddGroupClick(TObject *Sender)
{
CTag_tmap::StGroup  tGroup;

  // Add a new group to the tag.
  tGroup.name = "new group";
  mTag->groups.push_back(tGroup);
  mTag->groupCnt++;

  // Add to the list.
  lstUnitGroups->Items->Add(tGroup.name.c_str());
  lstUnitGroups->ItemIndex = mTag->groupCnt - 1;

}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::lstUnitGroupsClick(TObject *Sender)
{
int tIdx = lstUnitGroups->ItemIndex;

  if(tIdx < 0)
    return;
    
  // Show group name.
  edtGroupName->Text = mTag->groups[tIdx].name.c_str();

  // And fill the unit list box.
  lstUnitsInGroup->Clear();
  for(unsigned int i = 0; i < mTag->groups[tIdx].units.size(); ++i)
  {
  std::string  tItem;

    tItem = nsl::stformat("%s (#%d) @ (%f %f)",mTag->units[ mTag->groups[tIdx].units[i] ].name.c_str(),
                                          mTag->groups[tIdx].units[i],
                                          mTag->units[ mTag->groups[tIdx].units[i] ].x,
                                          mTag->units[ mTag->groups[tIdx].units[i] ].y);
    lstUnitsInGroup->Items->Add(tItem.c_str());
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::edtGroupNameChange(TObject *Sender)
{
unsigned long  tIdx = lstUnitGroups->ItemIndex;

  mTag->groups[tIdx].name = edtGroupName->Text.c_str();
  lstUnitGroups->Items->Strings[tIdx] = edtGroupName->Text;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::btnAddToGroupClick(TObject *Sender)
{
  // Adjust down states.
  btnAddToGroup->Down = true;
  btnRemoveFromGroup->Down = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmTMAP::chkUnitIsProxyClick(TObject *Sender)
{
  // Turn all the selected units into proxies (or regular guys)
  // as appropriate.
  for(unsigned int i = 0; i < mSelectedUnits.size(); ++i)
  {
    mTag->units[mSelectedUnits[i]].is_proxy = chkUnitIsProxy->Checked;
    if(chkUnitIsProxy->Checked)
      mUnitSprites[mSelectedUnits[i]]->SetInteriorColor(1.0,1.0,1.0,1.0);
    else
      mUnitSprites[mSelectedUnits[i]]->SetInteriorColor(0.0,0.0,0.0,1.0);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmTMAP::edtUnitTeamChange(TObject *Sender)
{
  for(unsigned int i = 0; i < mSelectedUnits.size(); ++i)
    mTag->units[mSelectedUnits[i]].team = edtUnitTeam->Text.ToInt();
}
//---------------------------------------------------------------------------

void __fastcall TfrmTMAP::edtMaxTeamsChange(TObject *Sender)
{
  mTag->teamCnt = edtMaxTeams->Text.ToInt();  
}
//---------------------------------------------------------------------------


void __fastcall TfrmTMAP::btnRemoveFromGroupClick(TObject *Sender)
{
  // Adjust down states.
  btnAddToGroup->Down = false;
  btnRemoveFromGroup->Down = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmTMAP::btnDeleteGroupClick(TObject *Sender)
{
int  tIdx = lstUnitGroups->ItemIndex;
std::vector< CTag_tmap::StGroup >::iterator  tIter = mTag->groups.begin();

  // Point the iterator at the group, then remove it.
  for(int i = 0; i < tIdx; ++i)
    ++tIter;

  // Groups don't contain any pointers so erase() can be called without
  // manually deleting the contents of the group.
  mTag->groups.erase(tIter);
  --mTag->groupCnt;
  lstUnitGroups->Items->Delete(tIdx);

  // Make sure there is a valid selection.
  if(lstUnitGroups->ItemIndex < 0)
    lstUnitGroups->ItemIndex = 0;
  lstUnitGroupsClick(0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTMAP::btnWayToolClick(TObject *Sender)
{
  // Adjust down states.
  btnPropertyTool->Down = false;
  btnTileTool->Down = false;
  btnUnitTool->Down = false;
  btnGroupTool->Down = false;
  btnWayTool->Down = true;

  pagToolOpts->ActivePage = tabWaypoints;
}
//---------------------------------------------------------------------------


void __fastcall TfrmTMAP::btnAddWayClick(TObject *Sender)
{
CTag_tmap::StMarker  wayp;

  wayp.name = "new waypoint";
  wayp.x = 0.0f;
  wayp.y = 0.0f;

  mTag->waypointCnt++;
  mTag->waypoints.push_back(wayp);
  lstWaypoints->Items->Add("new waypoint");
}
//---------------------------------------------------------------------------

void __fastcall TfrmTMAP::lstWaypointsClick(TObject *Sender)
{
unsigned int idx = lstWaypoints->ItemIndex;

  // Update the property fields of the selected tile type.
  edtWayName->Text = mTag->waypoints[idx].name.c_str();
  edtWayX->Text = mTag->waypoints[idx].x;
  edtWayY->Text = mTag->waypoints[idx].y;
}
//---------------------------------------------------------------------------

void __fastcall TfrmTMAP::edtWayNameChange(TObject *Sender)
{
unsigned long  tIdx = lstWaypoints->ItemIndex;

  mTag->waypoints[tIdx].name = edtWayName->Text.c_str();
  lstWaypoints->Items->Strings[tIdx] = edtWayName->Text;
}
//---------------------------------------------------------------------------

