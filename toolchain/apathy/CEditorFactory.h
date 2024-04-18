//---------------------------------------------------------------------------

#ifndef CEditorFactoryH
#define CEditorFactoryH
//---------------------------------------------------------------------------


#include "CTag.h"
#include "CEditor.h"

class CEditorFactory
{
  public:
    CEditorFactory(CTag::ID id);
    virtual ~CEditorFactory(void);

    static CEditor* Launch(CTag::ID id,const std::string &fn);


  protected:
    virtual CEditor* DoLaunch(const std::string &fn) = 0;

    static std::map< CTag::ID,CEditorFactory* >  smFactories;
};


std::map< CTag::ID,CEditorFactory* >  CEditorFactory::smFactories;




#endif
