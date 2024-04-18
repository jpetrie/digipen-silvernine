/*! =========================================================================
      
      @file    CSessionMgrS.cpp
      @brief   Implementation of event session manager.
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CTagMgrS.h"


/*                                                         internal constants
----------------------------------------------------------------------------- */

namespace
{
  const std::string  ikDefaultPatchPath = "data/patch";
  const std::string  ikDefaultPackagePath = "data/package";
};


/*                                                             static members
----------------------------------------------------------------------------- */

CTagMgrS::TFactoryMap        CTagMgrS::mFactories;  
CTagMgrS::TTypeToFactoryMap  CTagMgrS::mTypeMapping;
CTagMgrS::TKindToFactoryMap  CTagMgrS::mKindMapping;


/*                                                           member functions
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CTagMgrS::CTagMgrS(void)
/*! @brief Default constructor.
*/
: mPatchPath(ikDefaultPatchPath),
  mPackagePath(ikDefaultPackagePath)
{

}


/*  _________________________________________________________________________ */
CTagMgrS::~CTagMgrS(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
std::string CTagMgrS::GetTypeFromID(CTag::ID id)
/*! @brief Retrieve the type string for a given ID.

    @param id  The tag ID.
    
    @return
    The type string for the given ID.
*/
{
CTagFactory *tFactory = nFindFactory(id);

  if(0 != tFactory)
    return (tFactory->TypeString());
  return (kTag_Unknown_TypeStr);
}


/*  _________________________________________________________________________ */
std::string CTagMgrS::GetKindFromID(CTag::ID id)
/*! @brief Retrieve the kind string for a given ID.

    @param id  The tag ID.
    
    @return
    The kind string for the given ID.
*/
{
CTagFactory *tFactory = nFindFactory(id);

  if(0 != tFactory)
    return (tFactory->KindString());
  return (kTag_Unknown_KindStr);
}


/*  _________________________________________________________________________ */
CTag::ID CTagMgrS::GetIDFromType(const std::string &type)
/*! @brief Retrieve the ID for a given type string.

    @param type  The type string.
    
    @return
    The tag ID that maps to the given type string.
*/
{
TTypeToFactoryMap::iterator  tIter = mTypeMapping.find(type);

  if(tIter != mTypeMapping.end())
    return (tIter->second->Ident());
  return (kTag_Unknown);
}


/*  _________________________________________________________________________ */
CTag::ID CTagMgrS::GetIDFromKind(const std::string &type)
/*! @brief Retrieve the ID for a given kind string.

    @param type  The kind string.
    
    @return
    The tag ID that maps to the given kind string.
*/
{
TKindToFactoryMap::iterator  tIter = mKindMapping.find(type);

  if(tIter != mKindMapping.end())
    return (tIter->second->Ident());
  return (kTag_Unknown);
}


/*  _________________________________________________________________________ */
CTag* CTagMgrS::Create(CTag::ID id)
/*! @brief Create a new tag.

    @param id  The ID of the tag.
    
    @return
    A pointer to the new tag.
*/
{
CTagFactory *tFactory = nFindFactory(id);

  if(0 != tFactory)
    return (tFactory->DoCreate());
  return (0);
}


/*  _________________________________________________________________________ */
CTag* CTagMgrS::Unarchive(CTag::ID id,const std::string &tag)
/*! @brief Unarchive tag data from a tagfile.

    @param id   The ID of the tag.
    @param tag  The name of the tag.
    
    @return
    A pointer to the unarchived tag.
*/
{
  return (UnarchiveFrom(id,mPatchPath,tag));
}


/*  _________________________________________________________________________ */
CTag* CTagMgrS::UnarchiveFrom(CTag::ID id,const std::string &path,const std::string &tag)
/*! @brief Unarchive tag data from a tagfile.

    UnarchiveFrom() searches for the tag in the specified path. If the tagfile
    is not found, the function fails.

    @param id    The ID of the tag.
    @param path  The pathname to search.
    @param tag   The name of the tag.
    
    @return
    A pointer to the unarchived tag.
*/
{
CTagFactory  *tFactory = nFindFactory(id);
CTag         *tTag;
CTag::ID      tTagID;
std::string   tTagDesc;
std::string   tPath = path;
nsl::bstream  tBytes;

  // If the tag is in the cache...
  tTag = nFindInCache(id,tag);
  if(0 != tTag)
    return (tTag);

  // Build the full pathname.
  nsl::stpunslash(tPath);
  tPath = nsl::stformat("%s/%s/%s",tPath.c_str(),tFactory->KindString().c_str(),tag.c_str());

  if(!nsl::fdexists(tPath))
    nlTHROWV(XTagNotFound,nsl::stformat("Tag \"%s\" (%s) not found.",tag.c_str(),tFactory->KindString().c_str()));
  tBytes.insert_file(tPath);
  
  // Build tag.
  tBytes >> tTagID >> tTagDesc;
  tTag = tFactory->DoCreate();
  tTag->Name(tag);
  tTag->Desc(tTagDesc);
  
  tFactory->DoUnarchive(tTag,tBytes);
 
  return (tTag);
}


/*  _________________________________________________________________________ */
CTag* CTagMgrS::UnarchiveStream(CTag::ID id,nsl::bstream &stream)
/*! @brief Unarchive tag data from a stream.

    UnarchiveStream() expects the stream to begin with raw tag data, as opposed
    to the tag header that files on disk have.

    @param id      The ID of the tag.
    @param stream  The stream.
    
    @return
    A pointer to the unarchived tag.
*/
{
CTagFactory  *tFactory = nFindFactory(id);
CTag         *tTag;

  //FIXME error check factory stuff in all functions
  tTag = tFactory->DoCreate();
  tFactory->DoUnarchive(tTag,stream);
  return (tTag);
}


/*  _________________________________________________________________________ */
void CTagMgrS::Archive(CTag::ID id,CTag *tag)
/*! @brief Archive tag data to a tagfile.

    @param id   The ID of the tag.
    @param tag  The name of the tag.
    
    @return
    A pointer to the unarchived tag.
*/
{
  ArchiveTo(id,mPatchPath,tag);
}


/*  _________________________________________________________________________ */
void CTagMgrS::ArchiveTo(CTag::ID id,const std::string &path,CTag *tag)
/*! @brief Archive tag data from a tagfile.

    UnarchiveFrom() searches for the tag in the specified path. If the tagfile
    is not found, the function fails.

    @param id    The ID of the tag.
    @param path  The pathname to search.
    @param tag   The name of the tag.
    
    @return
    A pointer to the unarchived tag.
*/
{
CTagFactory  *tFactory = nFindFactory(id);
//CTag         *tTag;
//CTag::ID      tTagID;
std::string   tTagDesc;
std::string   tPath = path;
nsl::bstream  tBytes;

  // Build the full pathname.
  nsl::stpunslash(tPath);
  tPath = nsl::stformat("%s/%s/%s",tPath.c_str(),tFactory->KindString().c_str(),tag->Name().c_str());
  
  // Build tag.
  tBytes << id << tag->Desc();
  
  tFactory->DoArchive(tag,tBytes);

std::ofstream  tOut(tPath.c_str());

  tOut.write((const char*)tBytes.data(),tBytes.size());

  tOut.close();
 
//  return (tTag);
}


/*  _________________________________________________________________________ */
void CTagMgrS::Release(CTag *tag)
/*! @brief Release a tag.

    @param tag  The tag.
*/
{
std::string         tCacheKey = nsl::stformat("%s-%s",GetTypeFromID(tag->Ident()).c_str(),tag->Name().c_str());
TCacheMap::iterator tCacheItr = mCache.find(tCacheKey);

  // If the tag is cached, we don't free its memory.
  if(tCacheItr == mCache.end())
    delete tag;
}


/*  _________________________________________________________________________ */
void CTagMgrS::Cache(CTag::ID id,const std::string &tag)
/*! @brief Cache a tag.
*/
{
  CacheFrom(id,mPatchPath,tag);
}


/*  _________________________________________________________________________ */
void CTagMgrS::CacheFrom(CTag::ID id,const std::string &path,const std::string &tag)
/*! @brief Cache a tag.
*/
{
CTag *tTag;

  // If the specified tag is not in the cache.
  if(0 == nFindInCache(id,tag))
  {
  std::string  tCacheKey = nsl::stformat("%s-%s",GetTypeFromID(id).c_str(),tag.c_str());
  
    tTag = UnarchiveFrom(id,path,tag);
    mCache.insert(std::make_pair(tCacheKey,tTag));
  }
}


/*  _________________________________________________________________________ */
void CTagMgrS::CacheClear(CTag::ID id,const std::string &tag)
/*! @brief Uncache a tag.

*/
{
std::string         tCacheKey = nsl::stformat("%s-%s",GetTypeFromID(id).c_str(),tag.c_str());
TCacheMap::iterator tCacheItr = mCache.find(tCacheKey);

  if(tCacheItr != mCache.end())
  {
    delete tCacheItr->second;
    mCache.erase(tCacheItr);
  }
}


/*  _________________________________________________________________________ */
CTag* CTagMgrS::nFindInCache(CTag::ID id,const std::string &tag)
/*! @brief Search the cache for a tag.
*/
{
std::string         tCacheKey = nsl::stformat("%s-%s",GetTypeFromID(id).c_str(),tag.c_str());
TCacheMap::iterator tCacheItr = mCache.find(tCacheKey);

  if(tCacheItr != mCache.end())
    return (tCacheItr->second);
  return (0);
}


/*  _________________________________________________________________________ */
void CTagMgrS::nRegisterFactory(CTagFactory *factory)
/*! @brief Register a factory.

    This function has no effect if the factory has already been registered or
    if the factory pointer is null.

    @param id  The factory.
*/
{
  if(0 == factory || 0 != nFindFactory(factory->Ident()))
    return;
  
  // Insert the factory.
  mFactories.insert(std::make_pair(factory->Ident(),factory));
  mTypeMapping.insert(std::make_pair(factory->TypeString(),factory));
  mKindMapping.insert(std::make_pair(factory->KindString(),factory));
}


/*  _________________________________________________________________________ */
void CTagMgrS::nUnregisterFactory(CTag::ID id)
/*! @brief Unregister a factory.

    This function has no effect if the factory for the specified type is not
    already registered.

    @param id  The tag type.
*/
{
TFactoryMap::iterator  tIter = mFactories.find(id);

  if(tIter != mFactories.end())
  {
  TTypeToFactoryMap::iterator  tTypeIter = mTypeMapping.find(tIter->second->TypeString());
  TKindToFactoryMap::iterator  tKindIter = mKindMapping.find(tIter->second->KindString());
  
    mFactories.erase(tIter);
    mTypeMapping.erase(tTypeIter);
    mKindMapping.erase(tKindIter);
  }
}


/*  _________________________________________________________________________ */
CTagFactory* CTagMgrS::nFindFactory(CTag::ID id)
/*! @brief Find a factory for the specified tag type.

    @param id  The tag type.
    
    @return
    The tag factory responsible for the construction of tags of the specified
    type, or 0 if no such factory is registered.
*/
{
TFactoryMap::iterator  tIter = mFactories.find(id);

  if(tIter != mFactories.end())
    return (tIter->second);
  return (0);
}

//FIXME the cache should make copies of tags
//FIXME stformat() should use %S or sth as a std::string specifier