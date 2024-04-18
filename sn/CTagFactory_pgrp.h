/*!
	@file		CTagFactory_pgrp.h
	@author	Scott Smith
	@date		December 1, 2003

	@brief	projectile group tag
______________________________________________________________________________*/

#ifndef	_C_TAGFACTORY_PGRP_H_
#define	_C_TAGFACTORY_PGRP_H_

/*----------------------------------------------------------------------------*/

#include "NSL.h"
//#include "NLBytestream.h"

#include "CTagFactory.h"
#include "CTag_pgrp.h"

/*----------------------------------------------------------------------------*/

/*!
______________________________________________________________________________*/
class CTagFactory_pgrp : public CTagFactory
{
  public:
    // ct and dt
             CTagFactory_pgrp(void) : CTagFactory(kTag_pgrp,kTag_pgrp_TypeStr,kTag_pgrp_KindStr) { }
    virtual ~CTagFactory_pgrp(void)                          { }
   
   
  protected:
    // specific construction
    virtual CTag* DoCreate(void) { return new CTag_pgrp; };
    
    // specific archival
    virtual void  DoUnarchive(CTag *tag,nsl::bstream &bytes);
    virtual void  DoArchive(CTag *tag,nsl::bstream &bytes);
    
        
  private:
    // data members
    static CTagFactory_pgrp  smRegistrar;
};

#endif

