/*! =========================================================================
      
      @file    CScriptMgrS.h
      @brief   Interface to script manager class.
      
    ========================================================================= */
    
/*                                                                      guard
----------------------------------------------------------------------------- */
                                                                  
#ifndef _C_SCRIPTMGR_S_H_
#define _C_SCRIPTMGR_S_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

extern "C"
{
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
class CScriptableBase
/*! @brief Base scriptable class.
    
    This class serves only to wrap the templated CScriptableM< T_ > class, for
    both ease of use and compatibility. It does nothing: no methods, no data.
    It is used as a base class of CScriptableM< T_ >.
*/
{
  public:
             CScriptableBase(void) { }
    virtual ~CScriptableBase(void) { }
};


/*  _________________________________________________________________________ */
class CScriptMgrS : public nsl::singleton< CScriptMgrS >
/*! @brief Script engine management singleton.

    The MSDN has some excellent articles on the PE format. Additionally, Scott
    Bilas's original paper (from which the theory behind this engine originates)
    has an excellent overview of what's going on here.
    
    Be sure to check out http://www.lua.org for the Lua language and C API
    documentation, as well.
*/
{
  // friends
  template< class T_ > friend class CScriptableM;

  // stereotypes
  nlCONTRACT_NOCOPY(CScriptMgrS);
  
  public:
    // enums
    enum EType
    {
      mkScriptVoid,       // void type.
      mkScriptSInt,       // int or signed int type.
      mkScriptUInt,       // unsigned int type.
      mkScriptSChar,      // char or signed char type.
      mkScriptUChar,      // unsigned char type.
      mkScriptSShort,     // short or signed short type.
      mkScriptUShort,     // unsigned short type.
      mkScriptSLong,      // long or signed long type.
      mkScriptULong,      // unsigned long type.
      mkScriptFloat,      // float type.
      mkScriptDouble,     // double type.
      mkScriptLDouble,    // long double type.
      mkScriptBool,       // bool type.
      mkScriptString,     // char* type.
      mkScriptPointer,    // void* type.
      mkScriptDotDotDot,  // ... (indeterminate arguments).
      mkScriptInvalid     // Invalid type.
    };

    enum EConv
    {
      mkCall_cdecl,       // Caller cleans up stack, push params right-to-left.
      mkCall_stdcall,     // Callee cleans up stack, push params right-to-left.
      mkCall_thiscall,    // Same as stdcall, "this" in ECX.
      mkCall_thiscallva,  // Same as cdecl, "this" in ECX, push ECX before call.
      mkCall_fastcall     // Same as stdcall, first two params in ECX and EDX. 
    };

    // structs
    struct StBinding
    {
      std::string           mangledSig;  // Mangled symbol signature.
      std::string           cleanedSig;  // Cleaned symbol signature.
      std::string           name;        // Function name (used as keyvalue).
      std::string           nspace;      // Namespaces (or owning classes).
      unsigned int          address;     // Function address.
      EType                 ret;         // Return type.
      EConv                 convention;  // Calling convention.
      std::vector< EType >  args;        // Argument type list.
      bool                  is_virtual;  // True if the function must be called through the class's vtable.
    };

    // typedefs
    typedef lua_State                            TState;
    typedef std::map< std::string,bool >         TVirtualMap;
    typedef std::map< std::string,StBinding >    TBindingMap;
    typedef std::map< std::string,TBindingMap >  TClassBindingMap;
    typedef std::map< unsigned int,StBinding >   TAddrBindingMap;
    typedef std::map< std::string,StBinding >    TMangleBindingMap;


    // ct and dt
            CScriptMgrS(void);
    virtual ~CScriptMgrS(void);

    // execution
    void ExecuteFile(const std::string &fn);
    void ExecuteTag(const std::string &tag);
    
    
  private:
    // importing
    void nParseFunctions(void);
    void nImportFunction(const char *mangledName,unsigned long address);

    // translation
    void  nTranslateFunctionName(const std::string &cleanSig,StBinding &binding);
    EType nTranslateVarType(const std::string &vt);

    // dispatchers
    static int nDispatchFunction(lua_State *l);
    static int nDispatchMethod(const std::string &mn,const std::string &cn,void *thisptr);
 
    // thunking routines
    static unsigned long nThunkCall_cdecl(void *argptr,unsigned long argsz,unsigned long addr);
    static unsigned long nThunkCall_stdcall(void *argptr,unsigned long argsz,unsigned long addr);
    static unsigned long nThunkCall_thiscall(void *thisptr,void *argptr,unsigned long argsz,unsigned long addr);
    static unsigned long nThunkCall_thiscallva(void *thisptr,void *argptr,unsigned long argsz,unsigned long addr);


    // data members
    lua_State        *mState;              // Lua engine state.
    
    TVirtualMap       mVirtualClasses;     // Maps if a class has virtuals or not.
    
    TBindingMap        mFreeBindingTable;    // Table of known free functions.
    TClassBindingMap   mClassBindingTable;   // Table of known class functions.
    TAddrBindingMap    mAddrBindingTable;    // Table mapping addresses to binding information.
    TMangleBindingMap  mMangleBindingTable;  // Table mapping mangled names to binding information.
};


/*                                                                     macros
----------------------------------------------------------------------------- */

// singleton accessor
#define CScriptMgr  CScriptMgrS::instance()

// export tag
#define EXPORT  __declspec(dllexport)


#endif  /* _C_SCRIPTMGR_S_H_ */