//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CConfigMgrS.h"
#include "CGraphicsMgrS.h"
#include "CTagMgrS.h"
//---------------------------------------------------------------------------
USEFORM("ApathyMain.cpp", frmMain);
USEFORM("ApathyNewTag.cpp", frmNewTag);
USEFORM("ApathyNewPackage.cpp", frmNewPackage);
USEFORM("ApathyTagProps.cpp", frmTagProps);
USEFORM("CEditor_tmap.cpp", frmTMAP);
USEFORM("CEditor_tmapResize.cpp", frmTMAP_Resize);
USEFORM("CEditor_unit.cpp", frmUNIT);
USEFORM("CEditor_sprc.cpp", frmSPRC);
USEFORM("CEditor_sprcSCT.cpp", frmSPRCCollectionTitle);
USEFORM("CEditor_mech.cpp", frmMECH);
USEFORM("CEditor_proj.cpp", frmPROJ);
USEFORM("CEditor_obje.cpp", frmOBJE);
USEFORM("CEditor_strc.cpp", frmSTRC);
USEFORM("CEditor_pgrp.cpp", frmPGRP);
//---------------------------------------------------------------------------
void LoadConfigDefaults(void)
/*! @brief Sets up config value defaults.
*/
{
  CConfigMgr->SetValueAsBool("gfx_fullscreen",false);
  CConfigMgr->SetValueAsInt("gfx_resx",800);
  CConfigMgr->SetValueAsInt("gfx_resy",600);

  CConfigMgr->SetValueAsString("tag_patches","data/patch");
  CConfigMgr->SetValueAsString("tag_packages","data/pack");
}



WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
  CConfigMgrS     tCM;

        LoadConfigDefaults();

  CGraphicsMgrS  tGM(0);
  CTagMgrS       tTM;

    Application->Initialize();
    Application->CreateForm(__classid(TfrmMain), &frmMain);
         Application->CreateForm(__classid(TfrmTMAP_Resize), &frmTMAP_Resize);
         Application->CreateForm(__classid(TfrmTagProps), &frmTagProps);
         Application->CreateForm(__classid(TfrmNewTag), &frmNewTag);
         Application->CreateForm(__classid(TfrmSPRCCollectionTitle), &frmSPRCCollectionTitle);
         Application->CreateForm(__classid(TfrmNewPackage), &frmNewPackage);
         Application->Run();
  }
  catch (Exception &exception)
  {
    Application->ShowException(&exception);
  }
  catch(...)
  {
    try
    {
      throw Exception("");
    }
    catch (Exception &exception)
    {
      Application->ShowException(&exception);
    }
  }
  return 0;
}
//---------------------------------------------------------------------------





