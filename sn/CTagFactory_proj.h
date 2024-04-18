/*!
	@file		CTagFactory_proj.h
	@author	Scott Smith
	@date		November 17, 2003

	@brief	projectile tag
______________________________________________________________________________*/

#ifndef	_C_TAGFACTORY_PROJ_H_
#define	_C_TAGFACTORY_PROJ_H_

/*----------------------------------------------------------------------------*/

#include "precompiled.h"

#include "CTagFactory.h"
#include "CTag_proj.h"

/*----------------------------------------------------------------------------*/

/*!
______________________________________________________________________________*/
class CTagFactory_proj : public CTagFactory
{
  public:
    // ct and dt
             CTagFactory_proj(void) : CTagFactory(kTag_proj,kTag_proj_TypeStr,kTag_proj_KindStr) { }
    virtual ~CTagFactory_proj(void)                                                              { }
   
   
  protected:
    // specific construction
    virtual CTag* DoCreate(void) { return new CTag_proj; };
    
    // specific archival
    virtual void  DoUnarchive(CTag *tag,nsl::bstream &bytes);
    virtual void  DoArchive(CTag *tag,nsl::bstream &bytes);
    
        
  private:
    // data members
    static CTagFactory_proj  smRegistrar;
};

#endif
