/*!
	@file	
______________________________________________________________________________*/
#ifndef _C_TAGFACTORY_SPRC_H_
#define _C_TAGFACTORY_SPRC_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagFactory.h"
#include "CTag_sprc.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTagFactory_sprc : public CTagFactory
/*! @brief sprc tag factory.
*/
{
  public:
    // ct and dt
    CTagFactory_sprc(void) : CTagFactory(kTag_sprc, "sprc", "sprite collections") { }
    virtual ~CTagFactory_sprc(void)                          { }
	static int LoadGLTextures(CTag_sprc* sTag);

  protected:
    // factory workers
    virtual CTag* DoCreate(void) { return new CTag_sprc; };
    virtual void  DoUnarchive(CTag *tag,nsl::bstream &bytes);
    virtual void  DoArchive(CTag *tag,nsl::bstream &bytes);
    
        
  private:
    // data members
    static CTagFactory_sprc  smRegistrar;
	
};


#endif  
