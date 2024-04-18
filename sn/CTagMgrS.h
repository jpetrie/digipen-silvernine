/*! =========================================================================
      
      @file    CTagMgrS.h
      @brief   Interface to tag manager.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_TAGMGR_S_H_
#define _C_TAGMGR_S_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTag.h"
#include "CTagFactory.h"


/*                                                                   typedefs
----------------------------------------------------------------------------- */

// exception tags
nlVE_TAG(XTagNotFound);


/*                                                                  constants
----------------------------------------------------------------------------- */

// unknown type
const CTag::ID  kTag_Unknown = nlFOURCODE('*','*','*','*');

// unknown strings
const std::string  kTag_Unknown_TypeStr = "****";
const std::string  kTag_Unknown_KindStr = "unknown tag type";


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CTagMgrS : public nsl::singleton< CTagMgrS >
/*! @brief Tag manager singleton.
*/
{
  // contracts
  nlCONTRACT_NOCOPY(CTagMgrS);


  // friends
  friend class CTagFactory;
  
  
  public:
    // ct and dt
             CTagMgrS(void);
    virtual ~CTagMgrS(void);
    
    // paths
    std::string  PatchPath(void) const                { return (mPatchPath); }
    void         PatchPath(const std::string &path)   { mPatchPath = path; }
    std::string  PackagePath(void) const              { return (mPackagePath); }
    void         PackagePath(const std::string &path) { mPackagePath = path; }
    
    // mapping
    std::string GetTypeFromID(CTag::ID id);
    std::string GetKindFromID(CTag::ID id);
    CTag::ID    GetIDFromType(const std::string &type);
    CTag::ID    GetIDFromKind(const std::string &type);
     
    // creation
    CTag* Create(CTag::ID id);
    
    // unarchival
    CTag* Unarchive(CTag::ID id,const std::string &tag);
    CTag* UnarchiveFrom(CTag::ID id,const std::string &path,const std::string &tag);
    CTag* UnarchiveStream(CTag::ID id,nsl::bstream &stream);
    
    // archival
    void  Archive(CTag::ID id,CTag *tag);
    void  ArchiveTo(CTag::ID id,const std::string &path,CTag *tag);

    // release
    void Release(CTag *tag);
    
    // cache
    void Cache(CTag::ID id,const std::string &tag);
    void CacheFrom(CTag::ID id,const std::string &path,const std::string &tag);
    void CacheClear(CTag::ID,const std::string &tag);
    
  
  private:
    // typedefs
    typedef std::map< CTag::ID,CTagFactory* >     TFactoryMap;
    typedef std::map< std::string,CTagFactory* >  TTypeToFactoryMap;
    typedef std::map< std::string,CTagFactory* >  TKindToFactoryMap;
    typedef std::map< std::string,CTag* >         TCacheMap;
    
    // cache search
    CTag* nFindInCache(CTag::ID,const std::string &tag);
    
    // registration
    static void nRegisterFactory(CTagFactory *factory);
    static void nUnregisterFactory(CTag::ID id);
    
    // factory search
    static CTagFactory* nFindFactory(CTag::ID id);
    
    
    // data members
    static TFactoryMap        mFactories;    // Holds factories.
    static TTypeToFactoryMap  mTypeMapping;  // Maps from type strings to factories.
    static TKindToFactoryMap  mKindMapping;  // Maps from kind strings to factories.
    
    std::string  mPatchPath;    // Directory to look for patch tags.
    std::string  mPackagePath;  // Directory to look for packaged tags.
    
    TCacheMap  mCache;  // Tag cache.
};


/*                                                                     macros
----------------------------------------------------------------------------- */

// singleton accessor
#define CTagMgr  CTagMgrS::instance()


#endif  /* _C_TAGMGR_S_H_ */
