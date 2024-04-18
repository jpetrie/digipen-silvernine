//---------------------------------------------------------------------------
#ifndef CEditor_tmapH
#define CEditor_tmapH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

#include "CTagFactory.h"
#include "CTag_tmap.h"
#include "CTag_sprc.h"
//#include "CTag_scri.h"
#include "CTag_unit.h"

#include "CEditorFactory.h"
#include "CEditor_tmap.h"
#include "CEditor_tmapResize.h"

#include "CSprite.h"
#include "CRect.h"
//---------------------------------------------------------------------------
class TfrmTMAP : public CEditor
{
__published:
  TPanel *panMapView;
  TImageList *ImageList1;
  TToolBar *ToolBar1;
  TToolButton *btnTileTool;
  TToolButton *btnUnitTool;
  TToolButton *ToolButton3;
  TPageControl *pagToolOpts;
  TTabSheet *tabPropertyTool;
  TToolButton *ToolButton4;
  TToolButton *btnPropertyTool;
  TTabSheet *tabTileTool;
  TButton *btnSave;
  TButton *btnRevert;
  TComboBox *cmbCollection;
  TGroupBox *GroupBox1;
  TButton *btnResize;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  TStaticText *txtHeight;
  TStaticText *txtWidth;
  TToolButton *ToolButton1;
  TGroupBox *GroupBox2;
  TListBox *lstTileList;
  TBitBtn *btnNewTile;
  TBitBtn *btnCloneTile;
  TBitBtn *btnDeleteTile;
  TEdit *edtTileName;
  TLabel *Label4;
  TLabel *Label5;
  TEdit *edtSeqNormal;
  TEdit *edtSeqBurnt;
  TLabel *Label6;
  TGroupBox *GroupBox3;
  TLabel *Label7;
  TComboBox *cmbStartScript;
  TLabel *Label8;
  TComboBox *cmbEndScript;
  TTabSheet *tabUnitTool;
  TGroupBox *GroupBox4;
  TListBox *lstUnitList;
  TToolBar *ToolBar2;
  TToolButton *btnPaintUnit;
  TToolButton *btnPaintProxy;
  TToolButton *ToolButton2;
  TToolButton *btnUnitSelect;
  TGroupBox *GroupBox5;
  TPanel *panInspectNothing;
  TToolButton *btnClearUnit;
  TToolButton *btnGroupTool;
  TLabel *Label9;
  TComboBox *cmbTerrain;
  TTabSheet *tabGroupTool;
  TGroupBox *GroupBox6;
  TListBox *lstUnitGroups;
  TGroupBox *GroupBox7;
  TListBox *lstUnitsInGroup;
  TToolBar *ToolBar3;
  TToolButton *ToolButton5;
  TToolButton *ToolButton6;
  TEdit *edtGroupName;
  TBitBtn *btnCloneGroup;
  TBitBtn *btnAddGroup;
  TBitBtn *btnDeleteGroup;
  TToolButton *btnAddToGroup;
  TToolButton *btnRemoveFromGroup;
  TPanel *panInspectSomething;
  TEdit *edtUnitTeam;
  TLabel *Label10;
  TCheckBox *chkUnitIsProxy;
  TGroupBox *GroupBox8;
  TLabel *Label11;
  TLabel *Label12;
  TComboBox *ComboBox1;
  TComboBox *ComboBox2;
  TGroupBox *GroupBox9;
  TLabel *Label15;
  TComboBox *ComboBox5;
  TEdit *edtMaxTeams;
  TLabel *Label13;
  TTabSheet *tabWaypoints;
  TToolButton *btnWayTool;
  TListBox *lstWaypoints;
  TBitBtn *btnDelWay;
  TBitBtn *btnCloneWay;
  TBitBtn *btnAddWay;
  TEdit *edtWayName;
  TEdit *edtWayX;
  TEdit *edtWayY;
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall btnPropertyToolClick(TObject *Sender);
  void __fastcall btnTileToolClick(TObject *Sender);
  void __fastcall btnSaveClick(TObject *Sender);
  void __fastcall btnResizeClick(TObject *Sender);
  void __fastcall btnCancelClick(TObject *Sender);
  void __fastcall panMapViewMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall btnNewTileClick(TObject *Sender);
  void __fastcall edtTileNameChange(TObject *Sender);
  void __fastcall lstTileListClick(TObject *Sender);
  void __fastcall edtSeqNormalChange(TObject *Sender);
  void __fastcall btnDeleteTileClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall btnUnitToolClick(TObject *Sender);
  void __fastcall btnPaintUnitClick(TObject *Sender);
  void __fastcall btnPaintProxyClick(TObject *Sender);
  void __fastcall btnUnitSelectClick(TObject *Sender);
  void __fastcall panMapViewMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
  void __fastcall edtSeqBurntChange(TObject *Sender);
  void __fastcall cmbTerrainChange(TObject *Sender);
  void __fastcall btnClearUnitClick(TObject *Sender);
  void __fastcall btnGroupToolClick(TObject *Sender);
  void __fastcall btnAddGroupClick(TObject *Sender);
  void __fastcall lstUnitGroupsClick(TObject *Sender);
  void __fastcall edtGroupNameChange(TObject *Sender);
  void __fastcall btnAddToGroupClick(TObject *Sender);
  void __fastcall chkUnitIsProxyClick(TObject *Sender);
  void __fastcall edtUnitTeamChange(TObject *Sender);
  void __fastcall edtMaxTeamsChange(TObject *Sender);
  void __fastcall btnRemoveFromGroupClick(TObject *Sender);
  void __fastcall btnDeleteGroupClick(TObject *Sender);
  void __fastcall btnWayToolClick(TObject *Sender);
  void __fastcall btnAddWayClick(TObject *Sender);
  void __fastcall lstWaypointsClick(TObject *Sender);
  void __fastcall edtWayNameChange(TObject *Sender);
private:
  // data members
  HDC    mDC;        // Device context.
  HGLRC  mRC;        // Render context.
  int    mPF;        // Pixel format.
  int    mContextW;  // Render area width.
  int    mContextH;  // Render area height.

  CTag_tmap *mTag;  // The tag.

  std::vector< CSprite* >  mTileSprites;         // Sprites used for drawing the tiles.
  std::vector< int >       mTileLayoutSprites;   // Indices into above list.
  std::vector< CRect* >    mUnitSprites;         // Sprites used for drawing the units.
  std::vector< CRect* >    mProxySprites;        // Sprites used to draw unit proxies.

  std::vector< int >  mSelectedUnits;  // References selected units.

  float  mCamX;  // Map camera X pan.
  float  mCamY;  // Map camera Y pan.
  float  mCamZ;  // Map camera zoom.


public:
  __fastcall TfrmTMAP(TComponent* Owner,const std::string &fn);

  void __fastcall UpdateTileMap(void);
  void __fastcall RenderTileMap(void);

  void __fastcall IdleLoop(TObject*, bool& done);

  void __fastcall ScreenToWorld(int x,int y,float &ox,float &oy);
  void __fastcall WorldToTile(float x,float y,int &tx,int &ty);
  
  void __fastcall DeselectAllUnits(void);

  void __fastcall PopulateControls(void);
  void __fastcall PopulateTag(void);
};
//---------------------------------------------------------------------------
class CEditorFactory_tmap : public CEditorFactory
{
public:
  CEditorFactory_tmap(void) : CEditorFactory(kTag_tmap) { }

protected:
  CEditor* DoLaunch(const std::string &fn) { return new TfrmTMAP(0,fn); }

  private:
    static CEditorFactory_tmap  smRegistrar;
};
CEditorFactory_tmap  CEditorFactory_tmap::smRegistrar;
//---------------------------------------------------------------------------
extern PACKAGE TfrmTMAP *frmTMAP;
//---------------------------------------------------------------------------
#endif
