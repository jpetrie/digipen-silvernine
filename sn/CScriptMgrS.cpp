/*! =========================================================================
 
      @file    CScriptMgrS.cpp
      @brief   Implementation of script manager class.
    
    ========================================================================= */
   
/*                                                                   includes
----------------------------------------------------------------------------- */
                                                                    
#include "precompiled.h"
#include "CScriptMgrS.h"

#include "CTagMgrS.h"
#include "CTag_scri.h"

                                                                    
/*                                                         internal constants 
----------------------------------------------------------------------------- */

namespace
{
  const ikUnmangledNameLimit = 256;

  // access specifiers
  const char  ikSig_PublicAccessSpec[] = "public:";
  const char  ikSig_PrivateAccessSpec[] = "private:";
  const char  ikSig_ProtectedAccessSpec[] = "protected:";
  const char  ikSig_StaticSpec[] = "static";
  const char  ikSig_ConstSpec[] = "const";
  
  // virtual specifier
  const char  ikSig_VirtualSpec[] = "virtual";

  // calling conventions
  const char  ikSig_cdeclConv[] = "__cdecl";
  const char  ikSig_stdcallConv[] = "__stdcall";
  const char  ikSig_thiscallConv[] = "__thiscall";
  const char  ikSig_fastcallConv[] = "__fastcall";

  // tokens
  const char  ikSig_PointerToken[] = "*";
  const char  ikSig_ReferenceToken[] = "&";
  const char  ikSig_NamespaceToken[] = "::";

  // qualifiers
  const char  ikSig_SignedQualifier[] = "signed";
  const char  ikSig_UnsignedQualifier[] = "unsigned";

  // prefixes
  const char  ikSig_StructPrefix[] = "struct";
  const char  ikSig_ClassPrefix[] = "class";

  // vararg specifier
  const char  ikSig_DotDotDot[] = "...";

  // types
  const char  ikType_Void[] = "void";
  const char  ikType_Int[] = "int";
  const char  ikType_SInt[] = "signed int";
  const char  ikType_UInt[] = "unsigned int";
  const char  ikType_Char[] = "char";
  const char  ikType_SChar[] = "signed char";
  const char  ikType_UChar[] = "unsigned char";
  const char  ikType_Short[] = "short";
  const char  ikType_SShort[] = "signed short";
  const char  ikType_UShort[] = "unsigned short";
  const char  ikType_Long[] = "long";
  const char  ikType_SLong[] = "signed long";
  const char  ikType_ULong[] = "unsigned long";
  const char  ikType_Float[] = "float";
  const char  ikType_Double[] = "double";
  const char  ikType_LDouble[] = "long double";
  const char  ikType_Bool[] = "bool";
  const char  ikType_String[] = "char *";
};


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
CScriptMgrS::CScriptMgrS(void)
/*! @brief Default constructor.
*/
{
  // Prep Lua and its libraries.
  std::cout << "Loading Lua....\n";
  mState = lua_open();
  if(NULL == mState)
    nlTHROW("Could not initialize Lua scripting engine.");


  std::cout << "Loading Lua libraries....\n";
  luaopen_base(mState);
  luaopen_io(mState);
  luaopen_string(mState);
  luaopen_math(mState);
  luaopen_debug(mState);

  // Load exports.
  std::cout << "Parsing exports table....\n";
  nParseFunctions();
}


/*  _________________________________________________________________________ */
CScriptMgrS::~CScriptMgrS(void)
/*! @brief Destructor.
*/
{
  // Release Lua.
  std::cout << "Shutting down Lua....\n";
  lua_close(mState);
}


/* __________________________________________________________________________ */
void CScriptMgrS::ExecuteFile(const std::string &fn)
/*! @brief Executes the script contained in the specified file.

    If the file does not exist, an error message is printed to the journal.

    @param fn  Specifies the name of the file.
*/
{
 // if(!fexists(fn))
 //   mConsole << "  ERROR: " << "Script file \"" << fn.c_str() << "\" not found.\n";
 // else
  {
   // std::cout << "Executing \"" << fn.c_str() << "\":\n";
    luaL_loadfile(mState,fn.c_str());

    if(lua_pcall(mState,0,0,0))
    {
      std::cout << "  ERROR: " << lua_tostring(mState,-1) << " (" << fn.c_str() << ") \n";
      lua_pop(mState,1);
    }
  }
}


/* __________________________________________________________________________ */
void CScriptMgrS::ExecuteTag(const std::string &tag)
/*! @brief Executes the script contained in the specified tag.

    If the file does not exist, an error message is printed to the journal.

    @param tag  Specifies the name of the tag.
*/
{
  {
  CTag_scri *tTag = dynamic_cast< CTag_scri* >(CTagMgr->Unarchive(kTag_scri,tag));
  
   // std::cout << "Executing tag \"" << tag.c_str() << "\":\n";
    luaL_loadbuffer(mState,tTag->uncompiled.c_str(),tTag->uncompiled.size(),0);

    if(lua_pcall(mState,0,0,0))
    {
      std::cout << "  ERROR: " << lua_tostring(mState,-1) << "\n";
      lua_pop(mState,1);
    }
    
    CTagMgr->Release(tTag);
  }
}


/*  _________________________________________________________________________ */
void CScriptMgrS::nParseFunctions(void)
/*! @brief Reads exported functions from the application's export table.

    The EXPORT macro places the mangled symbol names of exposed functions into
    the application's export table the same as if it were a library.
    nParseFunctions() reads that export table and, for each export it finds,
    calls a method to unmangle and parse the signature of the export.
*/
{
HMODULE                       tThisApp;         // Handle to the application.
const unsigned char          *tImageBase;       // Base address of the app image.
const IMAGE_DOS_HEADER       *tImageDOSHead;    // DOS header base.
const IMAGE_NT_HEADERS       *tImageNTHead;     // NT header base.
IMAGE_DATA_DIRECTORY          tExports;         // RVA of exports table.
const IMAGE_EXPORT_DIRECTORY *tExportsTable;    // Actual exports table.
const unsigned long          *tNamesTable;      // Actual function names table.
const unsigned long          *tAddressesTable;  // Actual function addresses table.
StBinding                     tBinding;         // The binding.
int                           tIgnored = 0;     // Count of ignored exports.

  // Extract Portable Executable headers. The HMODULE of an application
  // is actually an in-memory version of its PE data.
  tThisApp = GetModuleHandle(NULL);
  tImageBase = reinterpret_cast< const unsigned char* >(tThisApp);  
  tImageDOSHead = reinterpret_cast< const IMAGE_DOS_HEADER* >(tThisApp);
  tImageNTHead = reinterpret_cast< const IMAGE_NT_HEADERS* >(tImageBase + tImageDOSHead->e_lfanew);

  // Extract export table.
  tExports = tImageNTHead->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];

  // The export table address is an RVA (relative address), we must add the image base 
  // address to it to get a valid pointer.
  tExportsTable = reinterpret_cast< const IMAGE_EXPORT_DIRECTORY* >(tImageBase + tExports.VirtualAddress);
  tNamesTable = reinterpret_cast< const unsigned long* >(tImageBase + tExportsTable->AddressOfNames);
  tAddressesTable = reinterpret_cast< const unsigned long* >(tImageBase + tExportsTable->AddressOfFunctions);

  // Grab all the exports.
  //std::cout << "  Found " << tExportsTable->NumberOfFunctions << " export(s):\n";
  for(unsigned int i = 0; i < tExportsTable->NumberOfFunctions; ++i)
  {
    // If the first two characters of the mangled name are `??`, the
    // name is actually part of the data generated by a static function -- I think.
    // We don't want to attempt import of those.
    if(0 != memcmp("??",reinterpret_cast< const char* >(tImageBase + *tNamesTable),2))
    {
      // The offsets in the names table are also RVAs....

#pragma warning(disable: 4311)
		nImportFunction(reinterpret_cast< const char* >(tImageBase + *tNamesTable),
                      reinterpret_cast< unsigned long >(tImageBase + *tAddressesTable));
#pragma warning(default: 4311)
    }
    else
      ++tIgnored;

    ++tNamesTable;
    ++tAddressesTable;
  }

  // If any exports were ignored, make a note.
//  if(tIgnored > 0)
  //  std::cout << "  NOTE: Ignored " << tIgnored << " export(s).\n";
}


/* __________________________________________________________________________ */
void CScriptMgrS::nImportFunction(const char *mangledName,unsigned long address)
/*! @brief Imports a binding for a function.

    nImportFunction() constructs a StBinding struct describing the function
    specified by mangledName that resides at address within the application.
    If the function is a free function, it is both imported and bound to the
    script engine at this time. If the function is a method of a class, it is
    imported but not bound until the class's registration method is invoked.

    @param mangledName  The mangled name of the function.
    @param address      The address of the function.
*/
{
StBinding        tBinding;
char             tUnmangledName[ikUnmangledNameLimit];
nsl::stringlist  tParts;

  // Thankfully, we don't have to manually unmangle the name....
  UnDecorateSymbolName(mangledName,tUnmangledName,ikUnmangledNameLimit,0);
  tBinding.address = address;
  tBinding.mangledSig = mangledName;
  tBinding.cleanedSig = tUnmangledName;
 // std::cout << "\t" << tUnmangledName << "\n";

  // Parse the undecorated name.
  nTranslateFunctionName(tBinding.cleanedSig,tBinding);

  // Insert the binding.
  if(tBinding.nspace.empty())
  {
    mFreeBindingTable[tBinding.mangledSig] = tBinding;

    // Do actual Lua binding; the function name is exposed
    // to Lua in a closure containing the mangled name as 
    // a key. The key is used by the glue function that
    // does actual dispatching of function calls.
    lua_pushstring(mState,tBinding.name.c_str());
    lua_pushstring(mState,tBinding.mangledSig.c_str());
    lua_pushcclosure(mState,nDispatchFunction,1);
    lua_settable(mState,LUA_GLOBALSINDEX);
  }
  else
  {
    // Class methods are bound later by the call to RegisterScriptableClass().
    mClassBindingTable[tBinding.nspace][tBinding.mangledSig] = tBinding;
    
    // We will need to know if a class has virtuals, so we don't try and read
    // the vtable of a class that doesn't actually have one. Upon first seeing
    // a class, we assume it has no virtuals. First time we see a virtual, we
    // note that it does in fact have them.
    if(mVirtualClasses.find(tBinding.nspace) == mVirtualClasses.end())
      mVirtualClasses[tBinding.nspace] = false;
    if(tBinding.is_virtual)
      mVirtualClasses[tBinding.nspace] = true;
  }
  
  // All bindings are mapped through their address. We do this so that 
  // the vtable of scriptable classes can be correctly emulated when
  // calls to the class are made.
  mAddrBindingTable[tBinding.address] = tBinding;
  mMangleBindingTable[tBinding.mangledSig] = tBinding;
}


/* __________________________________________________________________________ */
void CScriptMgrS::nTranslateFunctionName(const std::string &cleanSig,StBinding &binding)
/*! @brief Translates the cleaned name of a function into an StBinding object.

    Note that this, and all other translation functions for the manager, are
    highly dependant on the format of the string returned by the Windows API
    UnDecorateSymbolName() function. They will need to be rewritten, at least
    in part, if the format ever changes.

    @param  cleanSig  The cleaned name of the function.
    @param  binding   The binding structure that will be filled out based on
                      the contents of the cleaned signature.
*/
{
std::vector< std::string >  tTokens;
unsigned int                tToken = 0;
unsigned int                tNamespaceIndex;
std::string                 tParamStr;

  // Assume a regular function.
  binding.is_virtual = false;

  // Explode the string into space-delimited tokens.
  // Interpret each one until we find one that contains a '('.
  tTokens = nsl::stsplit_chr(cleanSig," ");
  while(std::string::npos == tTokens[tToken].find("("))
  {
    // The first few clauses check for warning cases.
    if(ikSig_PrivateAccessSpec == tTokens[tToken] ||
       ikSig_ProtectedAccessSpec == tTokens[tToken])
    {
      std::cout << "      WARNING: Export of private or protected method violates access rights.\n";
    }
    else if(ikSig_VirtualSpec == tTokens[tToken])
    {
      // This function is virtual.
      binding.is_virtual = true;
    }
    else if(ikSig_ConstSpec == tTokens[tToken])
    {
      std::cout << "      WARNING: \'const\' specifier for return type cannot be guaranteed.\n";
    }
    else if(ikSig_PublicAccessSpec == tTokens[tToken] || 
            ikSig_StaticSpec == tTokens[tToken]       ||
            ikSig_StructPrefix == tTokens[tToken]     ||
            ikSig_ClassPrefix == tTokens[tToken])
    {
      // Do nothing. 
    }
    
    // The next four tokens control the calling convention
    // if we find one. We'll only get one of these.
    else if(ikSig_cdeclConv == tTokens[tToken])
      binding.convention = mkCall_cdecl;
    else if(ikSig_stdcallConv == tTokens[tToken])
      binding.convention = mkCall_stdcall;
    else if(ikSig_thiscallConv == tTokens[tToken])
      binding.convention = mkCall_thiscall;
      
    // See if we're returning a pointer/reference type.
    // The pointer/reference specifier must come after
    // the type specifier, so it's okay to assume we 
    // know the type by now.
    else if(ikSig_PointerToken == tTokens[tToken] ||
            ikSig_ReferenceToken == tTokens[tToken])
    {
      if(mkScriptUChar == binding.ret ||
         mkScriptSChar == binding.ret)
      // We return a string.
        binding.ret = mkScriptString;
      else
      // We return a generic pointer.
        binding.ret = mkScriptPointer;
    }
    
    // See if we're returning something that is
    // explicitly signed or unsigned. The qualifier
    // will appear as an individual token.
    else if(ikSig_SignedQualifier == tTokens[tToken] || 
            ikSig_UnsignedQualifier == tTokens[tToken])
    {
      tParamStr += tTokens[tToken];
      tParamStr += " ";
    }
    
    // Our fall-through case simply assumes the token is a
    // variable type, and we translate it. 
    else
    {
      tParamStr += tTokens[tToken];
      binding.ret = nTranslateVarType(tParamStr);
    }

    // Next token.
    ++tToken;
  }

  // Once we've found a '(', we know the token its attached
  // to is the name of the function, and optionally has a
  // namespace attached. First, we look for the namespace.
  tTokens = nsl::stsplit_chr(tTokens[tToken],"(,)");
  tNamespaceIndex = scast<unsigned int>(tTokens[0].find(ikSig_NamespaceToken));
  if(std::string::npos != tNamespaceIndex)
  {
    binding.nspace = tTokens[0].substr(0,tNamespaceIndex);
    binding.name = tTokens[0].substr(tNamespaceIndex + 2);
  }
  else
    binding.name = tTokens[0];

  // Then we just look for the arguments.
int          tParenIdx = scast<int>(cleanSig.find("("));
std::string  tTempStr = cleanSig.substr(tParenIdx);

  tTokens = nsl::stsplit_chr(tTempStr,"(,)");
  for(unsigned int i = 0; i < tTokens.size(); ++i)
    binding.args.push_back(nTranslateVarType(tTokens[i]));
}


/* __________________________________________________________________________ */
CScriptMgrS::EType CScriptMgrS::nTranslateVarType(const std::string &vt)
/*! @brief Translates a string into a EType entity.

    @param vt  The string to translate.

    @return
    The EType entity coorisponding to the string `vt`. If `vt` does not
    represent a valid type, mkScriptInvalid is returned.
*/
{
std::string  tVT = vt;  // Variable type string.

  // See if the type is qualified by const; if it is, we chop it off.
  if(tVT.find(ikSig_ConstSpec) != std::string::npos)
    tVT.erase(tVT.find(ikSig_ConstSpec),strlen(ikSig_ConstSpec));

  if(ikType_Void == tVT)
    return (mkScriptVoid);
  else if(ikType_Int == tVT || ikType_SInt == tVT)
    return (mkScriptSInt);
  else if(ikType_UInt == tVT)
    return (mkScriptUInt);
  else if(ikType_Short == tVT || ikType_SShort == tVT)
    return (mkScriptSShort);
  else if(ikType_Char == tVT || ikType_SChar == tVT)
    return (mkScriptSChar);
  else if(ikType_UChar == tVT)
    return (mkScriptUChar);
  else if(ikType_UShort == tVT)
    return (mkScriptUShort);
  else if(ikType_Long == tVT || ikType_SLong == tVT)
    return (mkScriptSLong);
  else if(ikType_ULong == tVT)
    return (mkScriptULong);
  else if(ikType_Float == tVT)
    return (mkScriptFloat);
  else if(ikType_Double == tVT)
    return (mkScriptDouble);
  else if(ikType_LDouble == tVT)
    return (mkScriptLDouble);
  else if(ikType_String == tVT)
    return (mkScriptString);

  // The ellipsis (dot dot dot!) character is a "special" type
  // that the dispatcher will replace with the actual types passed
  // from the Lua stack.
  else if(ikSig_DotDotDot == tVT)
    return (mkScriptDotDotDot);
  
  // See if the type contains a pointer or reference token, if so
  // its an arbitrary pointer. Otherwise, its invalid.
  else
  {
    if(tVT.find(ikSig_PointerToken) != std::string::npos ||
       tVT.find(ikSig_ReferenceToken) != std::string::npos)
      return (mkScriptPointer);
    else
    {
      //std::cout << "      WARNING: Function makes use of unsupported type: " << tVT.c_str() << "\n";
      return (mkScriptInvalid);
    }
  }
}


/* __________________________________________________________________________ */
int CScriptMgrS::nDispatchFunction(lua_State *l)
/*! @brief Dispathes and thunks a function call from within Lua.

    nDispatchFunction() is the glue method between the Lua engine and the C++
    methods that comprise the exposed scripting functionality suite. When the
    exposed functions were bound at construction time, they were done so in a
    closure containing the mangled name bundled with the address of this
    function. We can now access that name and use it to recover the information
    we need to dispatch a function.
    
    Actual dispatch is done from the nDispatchMethod() function, which is more
    general (it handles the dispatch of class methods, as well).
    
    @param l  The Lua state variable of the Lua system invoking the function.
    
    @return
    An integer describing the number of variables that were returned by this
    function onto the Lua stack. Always one or zero since C++ does not support
    multiple returns.
*/
{
std::string  tFunc;

  // Pop the method key from the Lua stack, use it to get
  // binding table entry.
  tFunc = luaL_checkstring(l,lua_upvalueindex(1));
  
  // The method dispatcher does the actual gruntwork; simply
  // pass 0 for the this pointer and the empty string for the
  // bound class.
  return (nDispatchMethod(tFunc,"",0));
}


/* __________________________________________________________________________ */
int CScriptMgrS::nDispatchMethod(const std::string &mn,const std::string &cn,void *thisptr)
/*! @brief Dispatches and thunks a method call from within Lua.

    nDispatchMethod() is a more generalized form of nDispatchFunction() (and is
    actually called by nDispatchFunction()); it supports class methods as well
    as free functions.
    
    nDispatchMethod() looks up the binding information, and uses it to
    construct the "stack" of a C++ function call on the heap. Then, based on the
    calling convention of the exported method, the appropriate thunking method
    is invoked to copy the heap-stack to the actual stack and call the function.
    
    @param mn       The name of the method (mangled).
    @param cn       The name of the class; "" indicates a free function.
    @param thisptr  The this pointer of the class; 0 indicates a free function.
*/
{
TState        *tState = CScriptMgr->mState;
StBinding      tBinding;   // The function binding.
unsigned long  tArgSize;   // The heap-stack size, in bytes.
unsigned char *tArgBuf;    // The heap-stack buffer.
unsigned char *tArgPtr;    // Position within the heap-stack.
unsigned long  tRetValue;  // Return value of the thunked call.

  // Get the right binding. If cn is the empty string,
  // its a free function. Otherwise it is a class method.
  if(cn.empty())
    tBinding = CScriptMgr->mFreeBindingTable[mn];
  else
    tBinding = CScriptMgr->mClassBindingTable[cn][mn];
                          
  tBinding = CScriptMgr->mMangleBindingTable[mn];

  if(mkScriptDotDotDot == tBinding.args.back())
  // Remove it and replace it with the types of the variables actually
  // passed on the Lua stack.
  {
    tBinding.args.pop_back();
    for(int i = scast<int>(tBinding.args.size() + 1); i <= lua_gettop(tState); ++i)
    {
      if(lua_isnumber(tState,i))
        tBinding.args.push_back(mkScriptDouble);
      else if(lua_isboolean(tState,i))
        tBinding.args.push_back(mkScriptBool);
      else if(lua_isstring(tState,i))
        tBinding.args.push_back(mkScriptString);
      else
        tBinding.args.push_back(mkScriptInvalid);
    }
  }

  // Build argument buffer. First we need to figure out the
  // size of the buffer, in bytes.
  tArgSize = 0;
  for(unsigned int i = 0; i < tBinding.args.size(); ++i)
  {
    switch(tBinding.args[i])
    {
      case mkScriptSInt:
      case mkScriptUInt:
      case mkScriptSShort:
      case mkScriptUShort:
      case mkScriptSLong:
      case mkScriptULong:
        tArgSize += sizeof(int);
        break;
      case mkScriptFloat:
        tArgSize += sizeof(float);
        break;
      case mkScriptDouble:
        tArgSize += sizeof(double);
        break;
      case mkScriptLDouble:
        tArgSize += sizeof(long double);
      break;
      case mkScriptString:
        tArgSize += sizeof(char*);
        break;
      case mkScriptPointer:
        tArgSize += sizeof(void*);
        break;
      case mkScriptVoid:
      default:
      {
        // Do nothing....
      }
    }
  }

  // Now we can create the buffer and dump the arguments into it.
  tArgBuf = new unsigned char[tArgSize];
  memset(tArgBuf,0,tArgSize);
  tArgPtr = tArgBuf;
  for(unsigned int j = 0; j < tBinding.args.size(); ++j)
  {
    // Remember that the stack memory must be aligned on 32-bit
    // boundaries when pushing things; or more generally, the
    // boundaries of the native word size (e.g., an int).
    switch(tBinding.args[j])
    {
      case mkScriptSInt:
      case mkScriptUInt:
      {
      int tVal = (int)luaL_checknumber(tState,(j + 1));

        memcpy(reinterpret_cast< void* >(tArgPtr),&tVal,sizeof(int));
        tArgPtr += sizeof(int);
      }
      break;
      case mkScriptSShort:
      case mkScriptUShort:
      {
      short tVal = static_cast< short >(luaL_checknumber(tState,(j + 1)));

        memcpy(reinterpret_cast< void* >(tArgPtr),&tVal,sizeof(short));
        tArgPtr += sizeof(int);
      }
      break;
      case mkScriptSLong:
      case mkScriptULong:
      {
      long tVal = static_cast< long >(luaL_checknumber(tState,(j + 1)));

        memcpy(reinterpret_cast< void* >(tArgPtr),&tVal,sizeof(long));
        tArgPtr += sizeof(int);
      }
      break;
      case mkScriptFloat:
      {
      float tVal = static_cast< float >(luaL_checknumber(tState,(j + 1)));

        memcpy(reinterpret_cast< void* >(tArgPtr),&tVal,sizeof(float));
        tArgPtr += sizeof(float);
      }
      break;
      case mkScriptDouble:
      {
      double tVal = static_cast< double >(luaL_checknumber(tState,(j + 1)));

        memcpy(reinterpret_cast< void* >(tArgPtr),&tVal,sizeof(double));
        tArgPtr += sizeof(double);
        break;
      }
      case mkScriptLDouble:
      {
      long double tVal = static_cast< long double >(luaL_checknumber(tState,(j + 1)));

        memcpy(reinterpret_cast< void* >(tArgPtr),&tVal,sizeof(long double));
        tArgPtr += sizeof(long double);
      }
      break;
      case mkScriptString:
      {
      const char *tVal = luaL_checkstring(tState,(j + 1));

        memcpy(reinterpret_cast< void* >(tArgPtr),&tVal,sizeof(char*));
        tArgPtr += sizeof(char*);
      }
      break;
      case mkScriptPointer:
      {
      void *tVal = lua_unboxpointer(tState,(j + 1));

        memcpy(reinterpret_cast< void* >(tArgPtr),&tVal,sizeof(void*));
        tArgPtr += sizeof(void*);
      }
      break;
      case mkScriptVoid:
      default:
      {
        // Do nothing....
      }
    }
  }

  // Thunk the call.
  switch(tBinding.convention)
  {
    case mkCall_cdecl:
      // Could be a regular __cdecl or a vararg __thiscall.
      if(!tBinding.nspace.empty() && 0 != thisptr)
        tRetValue = nThunkCall_thiscallva(thisptr,tArgBuf,tArgSize,tBinding.address);
      else
        tRetValue = nThunkCall_cdecl(tArgBuf,tArgSize,tBinding.address);
    break;
    case mkCall_stdcall:
      tRetValue = nThunkCall_stdcall(tArgBuf,tArgSize,tBinding.address);
    break;
    case mkCall_thiscall:
      // Could go through a vtable.
      if(tBinding.is_virtual)
      {
        tRetValue = nThunkCall_thiscall(thisptr,tArgBuf,tArgSize,tBinding.address);
      }
      else
        tRetValue = nThunkCall_thiscall(thisptr,tArgBuf,tArgSize,tBinding.address);
    break;
    // __fastcall is not supported; it is thunked as a __cdecl.
    case mkCall_fastcall:
    default:
      tRetValue = nThunkCall_cdecl(tArgBuf,tArgSize,tBinding.address);
  }

  // We're done with this now.
  delete[] tArgBuf;

  // Push the return value onto Lua's stack (if there
  // was a return value).
  if(tBinding.ret == mkScriptVoid)
    return (0);

  switch(tBinding.ret)
  {
    // For integer types, we simply push the result, after
    // masking bits to ensure it's the right size.
    case mkScriptSInt:
    case mkScriptUInt:
      lua_pushnumber(tState,tRetValue);
    break;

    case mkScriptSShort:
    case mkScriptUShort:
    {
      tRetValue &= 0x0000FFFF;
      lua_pushnumber(tState,tRetValue);
    }
    break;

    case mkScriptSLong:
    case mkScriptULong:
    {
      lua_pushnumber(tState,tRetValue);
      break;
    }

    // For real types, we'll need to get the result from
    // the FPU's ST0 register to push it.
    case mkScriptFloat:
    case mkScriptDouble:
    case mkScriptLDouble:
    {
    long double tRealValue;

      __asm fstp tRealValue
      lua_pushnumber(tState,static_cast< lua_Number >(tRealValue));
    }
    break;

    // For strings, we cast the result and push.
    case mkScriptString:
    {
#pragma warning(disable: 4312)
		const char *tStringAddr = reinterpret_cast< char* >(tRetValue);
#pragma warning(default: 4312)

      lua_pushstring(tState,tStringAddr);
    }
    break;

    // For pointers to arbitrary types,
    // assume they are scripted types.
    case mkScriptPointer:
    {
#pragma warning(disable: 4312)
		void            *tArbitraryAddr = reinterpret_cast< void* >(tRetValue);
    CScriptableBase *tBaseType = reinterpret_cast< CScriptableBase* >(tRetValue);
#pragma warning(disable: 4312)
    std::string      tTypeName;
    std::string      tWeakName = "refto__";
    int              tBoxedPtr;
    
      // Make the name of a weak type.
      tTypeName += typeid(*tBaseType).name();
      tTypeName = tTypeName.substr(6);
      tWeakName += tTypeName;
      
      // Box the pointer, then associate the metatable with the
      // userdata object so that it can be indexed, etc.
      lua_boxpointer(tState,tArbitraryAddr);
      tBoxedPtr = lua_gettop(tState);
      luaL_getmetatable(tState,tWeakName.c_str());
      lua_setmetatable(tState,tBoxedPtr);
    }
    break;
    
    // Invalid return types get pushed as numbers.
    // No guarantees are made as to what, actually, is going
    // to happen here.
    default:
    {
      lua_pushnumber(tState,tRetValue);
    }
  }

  // C++ functions can only return one value.
  return (1);
}


/* __________________________________________________________________________ */
unsigned long CScriptMgrS::nThunkCall_cdecl(void *argptr,unsigned long argsz,unsigned long addr)
/*! @brief Thunks a call to a __cdecl function.

    __cdecl requires the function arguments to be pushed right-to-left. The
    caller must clean up the stack.

    @param argptr   Address of argument buffer.
    @param argsz    Size, in bytes, of argument buffer.
    @param addr     Address of function to thunk.

    @return
    The return value of the thunked function.
    Integer types are returned directly, compound types or types that are
    larger than 32 bits are returned by address. float and double types are
    returned via the floating point stack registers and are dealt with
    elsewhere. In this case, the return value of the function is undefined.
*/
{
unsigned long  tRetValue;

  __asm
  {
    mov   ecx,argsz      // Store byte count in ECX.  
    mov   esi,argptr     // Store argument pointer in ESI.
    sub   esp,ecx        // Make room on the stack.
    mov   edi,esp        // Store stack pointer in EDI.
    shr   ecx,2          // Copy longwords.
    rep   movsd          // Copy parameters into the stack.
    call  addr           // Call the function.
    mov   tRetValue,eax  // Store return value.
    add   esp,argsz      // Clean up stack.
  }


  return (tRetValue);
}


/* __________________________________________________________________________ */
unsigned long CScriptMgrS::nThunkCall_stdcall(void *argptr,unsigned long argsz,unsigned long addr)
/*! @brief Thunks a call to a __stdcall function.

    __stdcall requires the function arguments to be pushed right-to-left. The
    called function will clean up the stack.

    @param argptr   Address of argument buffer.
    @param argsz    Size, in bytes, of argument buffer.
    @param addr     Address of function to thunk.

    @return
    The return value of the thunked function.
    Integer types are returned directly, compound types or types that are
    larger than 32 bits are returned by address. float and double types are
    returned via the floating point stack registers and are dealt with
    elsewhere. In this case, the return value of the function is undefined.
*/
{
unsigned long  tRetValue;

  __asm
  {
    mov   ecx,argsz      // Store byte count in ECX.  
    mov   esi,argptr     // Store argument pointer in ESI.
    sub   esp,ecx        // Make room on the stack.
    mov   edi,esp        // Store stack pointer in EDI.
    shr   ecx,2          // Copy longwords.
    rep   movsd          // Copy parameters into the stack.
    call  addr           // Call the function.
    mov   tRetValue,eax  // Store return value.
  }

  return (tRetValue);
}


/* __________________________________________________________________________ */
unsigned long CScriptMgrS::nThunkCall_thiscall(void *thisptr,void *argptr,unsigned long argsz,unsigned long addr)
/*! @brief Thunks a call to a __thiscall method.

    __thiscall requires the function arguments to be pushed right-to-left, and
    the 'this' pointer passed via the ECX register. The called function will
    clean up the stack.

    @param thisptr  Address of the invoking object. 
    @param argptr   Address of argument buffer.
    @param argsz    Size, in bytes, of argument buffer.
    @param addr     Address of function to thunk.

    @return
    The return value of the thunked function.
    Integer types are returned directly, compound types or types that are
    larger than 32 bits are returned by address. float and double types are
    returned via the floating point stack registers and are dealt with
    elsewhere. In this case, the return value of the function is undefined.
*/
{
unsigned long  tRetValue;

  __asm
  {
    mov   ecx,argsz      // Store byte count in ECX.  
    mov   esi,argptr     // Store argument pointer in ESI.
    sub   esp,ecx        // Make room on the stack.
    mov   edi,esp        // Store stack pointer in EDI.
    shr   ecx,2          // Copy longwords.
    rep   movsd          // Copy parameters into the stack.
    mov   ecx,thisptr    // Pass the `this` pointer in ECX.
    call  addr           // Call the function.
    mov   tRetValue,eax  // Store return value.
  }

  return (tRetValue); 
}


/* __________________________________________________________________________ */
unsigned long CScriptMgrS::nThunkCall_thiscallva(void *thisptr,void *argptr,unsigned long argsz,unsigned long addr)
/*! @brief Thunks a call to a __cdecl class method that accepts a variable
           number of arguments.

    __thiscallva is not a proper calling convention; it is a special case of
    the __cdecl convention. __thiscallva requires that the its arguments be
    pushed right-to-left such that the object's 'this' pointer is pushed last.
    The caller is responsible for cleaning up the stack.

    @param thisptr  Address of the invoking object. 
    @param argptr   Address of argument buffer.
    @param argsz    Size, in bytes, of argument buffer.
    @param addr     Address of function to thunk.

    @return
    The return value of the thunked function.
    Integer types are returned directly, compound types or types that are
    larger than 32 bits are returned by address. float and double types are
    returned via the floating point stack registers and are dealt with
    elsewhere. In this case, the return value of the function is undefined.
*/
{
unsigned long  tRetValue;

  __asm
  {
    mov   ecx,argsz      // Store byte count in ECX.  
    mov   esi,argptr     // Store argument pointer in ESI.
    sub   esp,ecx        // Make room on the stack.
    mov   edi,esp        // Store stack pointer in EDI.
    shr   ecx,2          // Copy longwords.
    rep   movsd          // Copy parameters into the stack.
    mov   eax,thisptr    // Push 'this' last.
    push  eax;
    call  addr           // Call the function.
    mov   tRetValue,eax  // Store return value.
    add   esp,argsz      // Clean up stack.
    add   esp,4          // Clean up after 'this' pointer.
  }

  return (tRetValue);
}

