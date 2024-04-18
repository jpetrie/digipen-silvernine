//---------------------------------------------------------------------------


#pragma hdrstop

#include "CEditorFactory.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


CEditorFactory::CEditorFactory(CTag::ID id)
{
  smFactories.insert(std::make_pair(id,this));
}

CEditorFactory::~CEditorFactory(void)
{
}


CEditor* CEditorFactory::Launch(CTag::ID id,const std::string &fn)
{
CEditorFactory *tFactory = (*smFactories.find(id)).second;

  return tFactory->DoLaunch(fn);
}
