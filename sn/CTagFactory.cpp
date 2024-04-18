/*! =========================================================================
      
      @file    CTagFactory.cpp
      @brief   Implementation of tag factory base class.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagMgrS.h"
#include "CTagFactory.h"


/*                                                           member functions
----------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */
CTagFactory::CTagFactory(CTag::ID id,const std::string &typestr,const std::string &kindstr)
/*! @brief Constructor.

    @param id       The ID (four character code) of the tag this factory builds.
    @param typestr  The type string of the factory.
    @param kindstr  The kind string of the factory.
*/
: mID(id),mTypeStr(typestr),mKindStr(kindstr)
{
  // It is possible for the factories to be constructed before the manager
  // singleton (in fact, it is highly likely). To get around this, we make
  // the registrar, along with the appropriate data, static.
  CTagMgrS::nRegisterFactory(this);
}


/*  _________________________________________________________________________ */
CTagFactory::~CTagFactory(void)
/*! @brief Destructor.
*/
{
  CTagMgrS::nUnregisterFactory(mID);
}
